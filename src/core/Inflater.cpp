////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Inflater.cpp
// Library:     Jameo Core Library
// Purpose:     Inflate Algorithm
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     06.09.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
//
// Licence:     The MIT License
//              Permission is hereby granted, free of charge, to any person obtaining a copy of this
//              software and associated documentation files (the "Software"), to deal in the
//              Software without restriction, including without limitation the rights to use, copy,
//              modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//              and to permit persons to whom the Software is furnished to do so, subject to the
//              following conditions:
//
//              The above copyright notice and this permission notice shall be included in all
//              copies or substantial portions of the Software.
//
//              THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//              INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//              PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//              HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
//              CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
//              OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"

using std::max;

using namespace jm;

//Konstante Huffman-Werte
const uint8 LENGTH_EXTRA[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
const uint16 LENGTH_OFFSET[29] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258};
const uint8 DIST_EXTRA[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
const uint16 DIST_OFFSET[30] = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577};

Inflater::Inflater(): Object()
{
   mWrap = false;
   mCompBytes = NULL;
   mCompLength = 0;
   mCompIndex = 0;
   mUncompBytes = NULL;
   mUncompLength = 1024;
   mUncompIndex = 0;
   mTotalIn = 0;
   mTotalOut = 0;
   mBit = 0;
   mLastBlock = false;
   mEof = false;
}

Inflater::Inflater(bool wrap): Object()
{
   mUncompBytes = NULL;
   Reset();
   mWrap = wrap;
}

Inflater::~Inflater()
{
}

void Inflater::SetInput(uint8* buffer, Integer length)
{
   mCompBytes = buffer;
   mCompLength = length;
   mCompIndex = 0;
}

bool Inflater::NeedsInput()
{
   return !mEof;
}

bool Inflater::Finished()
{
   return mEof;
}

void Inflater::Inflate(uint8*& buffer, Integer& length)
{
   mUncompIndex = 0;

   // You are at the beginning of the stream. Read in ZLIB header (RFC1950)
   if(mTotalIn == 0 && mWrap == false)
   {
      // Check compression header
      if(mCompLength < 2)throw new Exception("No compressed data found!");

      //cmf: Compression Method and flag
      //flg: Flags
      uint8 cmf = mCompBytes[0];
      uint8 flg = mCompBytes[1];

      int8 compressionMethod = cmf & 0x0F;
      int8 compressionInfo = (cmf >> 4) & 0x0F;
      if(compressionMethod != 8)throw new
         Exception("Compression method must be deflate with 32k window. (" + String::valueOf(
                      compressionMethod) + ")");
      if(compressionInfo > 7)throw new Exception("png window size is only for 32k implemented.");

      //int8 fcheck = flg & 0x1F; Does not have to be calculated explicitly for decompression, as fcheck must be set so that the following check is successful.
      int8 fdict = (flg >> 5) & 0x01;
      // int8 flevel = ( flg >> 6 ) & 0x03; Not needed for decompression. For information purposes only
      if(fdict != 0)throw new Exception("Inflater need Dictionary. Currently not implemented.");

      // Check Fcheck
      uint16 check1 = cmf * 256 + flg;
      uint16 check2 = check1 % 31;
      if(check2 != 0)throw new Exception("Wrong checksum for compressed zlib data stream");

      // Prepare the read-in
      mCompIndex = 2;
      mTotalIn = 2;
      mBit = 0;
   }


   Inflate();

   buffer = mUncompBytes;
   length = mUncompIndex;
}

void Inflater::Reset()
{
   mCompBytes = NULL;
   mCompLength = 0;
   mCompIndex = 0;
   mUncompBytes = NULL;
   mUncompBytes = new uint8[1024];
   mUncompLength = 1024;
   mUncompIndex = 0;
   mTotalIn = 0;
   mTotalOut = 0;
   mBit = 0;
   mLastBlock = false;
   mEof = false;
}

Integer Inflater::GetRemaining()
{
   return mCompLength - mCompIndex;
}

Integer Inflater::GetTotalIn()
{
   return mTotalIn;
}

Integer Inflater::GetTotalOut()
{
   return mTotalOut;
}


uint8 Inflater::NextBit()
{
   uint8 ret = ((0x01 << mBit) & mCompBytes[mCompIndex]) >> mBit;

   mBit++;
   if((mBit % 8) == 0)
   {
      mBit = 0;
      mCompIndex++;
      mTotalIn++;
   }
   return ret;
}

void Inflater::SkipByteBits()
{
   if(mBit == 0)return;
   mBit = 0;
   mCompIndex++;
   mTotalIn++;
}

uint8 Inflater::NextAlignedUInt8()
{
   if(mBit != 0)throw new Exception("Incorrect bit order for uint8!");
   uint8 ret = mCompBytes[mCompIndex++];
   mTotalIn++;
   return ret;
}

uint16 Inflater::NextAlignedUInt16()
{
   uint8 sub[2];
   sub[0] = NextAlignedUInt8();
   sub[1] = NextAlignedUInt8();

   uint16 ret = DeserializeLEUInt16(sub, 0);
   return ret;
}

uint16 Inflater::NextUIntX(uint8 bits)
{
   uint16 ret = 0;
   for(uint8 a = 0; a < bits; a++)
   {
      ret <<= 1;
      ret |= NextBit();
   }
   return ret;
}

uint16 Inflater::NextUIntXR(uint8 bits)
{
   uint16 ret = 0;
   for(uint8 a = 0; a < bits; a++)
   {
      ret |= (NextBit() << a);
   }
   return ret;
}

void Inflater::CheckCapacity()
{
   if(mUncompIndex < mUncompLength)return;

   // Increase
   double ratio = mCompIndex.Int64() / (double)mCompLength.Int64();
   Integer newLength = mUncompLength + max(4096, (int32)(mUncompLength.Int64() / ratio));
   uint8* tmp = new uint8[newLength];
   if(tmp == NULL)throw new Exception("Cannot allocate memory!");
   memcpy(tmp, mUncompBytes, mUncompIndex);
   delete[] mUncompBytes;
   mUncompBytes = tmp;
   mUncompLength = newLength;
}

void Inflater::WriteUncompressed(uint8 byte)
{
   CheckCapacity();
   mUncompBytes[mUncompIndex++] = byte;
   mTotalOut++;
}


void Inflater::HandleUncompressedBlock()
{
   //	std::cout << "UNCOMPRESSED BLOCK\n";

   //read LEN and NLEN (see next section)
   //copy LEN bytes of data to output
   SkipByteBits();
   uint16 len = NextAlignedUInt16();
   uint16 nlen = NextAlignedUInt16();//Komplement von len

   if((nlen & len) != 0)throw new Exception("Length of uncompressed block is corrupted.");

   for(int32 a = 0; a < len; a++)
   {
      uint8 b = NextAlignedUInt8();
      WriteUncompressed(b);
   }
}


void Inflater::HandleCompressedFixHuffman()
{
   //std::cout << "COMPRESSED BLOCK FIX HUFFMAN\n";
   bool endOfBlock = false;

   while(!endOfBlock)
   {
      uint16 value = NextFixedHuffmanCode();

      if(value < 256)
      {
         WriteUncompressed((uint8) value);
      }
      else if(value == 256)
      {
         endOfBlock = true;
      }
      else if(value >= 257 && value <= 285)
      {
         //Length
         uint8 extrabits = LENGTH_EXTRA[value - 257];
         uint16 length = NextUIntXR((uint8) extrabits);
         length += LENGTH_OFFSET[value - 257];


         //Distance

         //Distance codes 0-31 are represented by (fixed-length) 5-bit
         //codes, with possible additional bits as shown in the table
         //shown in Paragraph 3.2.5, above.

         uint16 code = NextUIntX(5);

         extrabits = DIST_EXTRA[code];
         uint16 distance = NextUIntXR(extrabits);
         distance += DIST_OFFSET[code];

         //move backwards distance bytes in the output
         //stream, and copy length bytes from this
         //position to the output stream.

         Integer src = (mUncompIndex - distance) & 32767;
         if(src < 0)throw new Exception("Distance in fix hufmann refer before output stream beginning.");
         for(Integer a = 0; a < length; a++)
         {
            WriteUncompressed(mUncompBytes[src + a]);
         }
      }
      else throw Exception("Code has unexpected value: " + String::valueOf(value));


   }
}

Inflater::HuffmanTree* Inflater::CreateTree(Array<uint16>* lengths, Array<uint16>* codes)
{
   // Algorithm:
   //1. Determine maximum number of bits
   //2. Take all elements with the highest number of bits
   //3. Sort the elements according to their size
   //4. Remove (in the intermediate value) the last bit
   //5. Combine the elements with the same intermediate value in a node
   //   The "new" node has the intermediate value as code and the length is reduced by 1.
   //6. Add the new element to the list
   //7. Start at 2 until there is only one element left.

   // Create array with all codes and lengths to generate the tree
   //1. Determine maxBits at the same time
   std::vector<Inflater::HuffmanTree*> nodes;
   int32 maxBits = 0;
   for(Integer a = 0; a < lengths->size(); a++)
   {
      // Only insert the elements that exist (i.e. length>0)
      if((*lengths)[a] != 0)
      {
         HuffmanTree* node = new HuffmanTree();
         node->length = (*lengths)[a];
         node->symbol = a.Int16();
         node->code = (*codes)[a];
         nodes.push_back(node);

         if(node->length > maxBits)maxBits = node->length;
      }
   }

   do
   {
      if(maxBits < 0)throw new Exception("Mööp");

      //2. Take all elements with the highest number of bits
      std::vector<Inflater::HuffmanTree*> focus;
      for(uint32 a = 0; a < nodes.size(); a++)
      {
         if(nodes[a]->length == maxBits)
         {
            focus.push_back(nodes[a]);
            nodes.erase(nodes.begin() + a);
            a--;
         }
      }


      //3. Sort these elements according to the code
      for(uint32 n = (uint32)focus.size(); n > 1; n--)
      {
         for(uint32 i = 0; i < n - 1; i++)
         {
            if(focus[i]->code > focus[i + 1]->code)
            {
               HuffmanTree* tmp = focus[i + 1];
               focus[i + 1] = focus[i];
               focus[i] = tmp;
            }
         }
      }

      // Check for duplicate entries
      for(uint32 a = 1; a < focus.size(); a++)
      {
         if(focus[a - 1]->code == focus[a]->code)throw  new Exception("Mööp");
      }

      //4. Remove bit in tmp
      for(uint32 a = 0; a < focus.size(); a++)
      {
         focus[a]->tmp = (focus[a]->code) >> 1;
      }

      while(focus.size() > 1)
      {
         HuffmanTree* n1 = focus[0];
         HuffmanTree* n2 = focus[1];
         if(n1->tmp == n2->tmp)
         {
            HuffmanTree* nn = new HuffmanTree();
            nn->length = n1->length - 1;
            nn->node0 = n1;
            nn->node1 = n2;
            nn->code = n1->tmp;
            nodes.push_back(nn);

            focus.erase(focus.begin());
            focus.erase(focus.begin());
         }
         else
         {
            HuffmanTree* nn = new HuffmanTree();
            nn->length = n1->length - 1;

            if((n1->tmp & 0x01) == 0)nn->node0 = n1;
            else nn->node1 = n1;
            nn->code = n1->tmp;
            nodes.push_back(nn);

            focus.erase(focus.begin());
         }
      }

      if(focus.size() == 1)
      {
         HuffmanTree* n1 = focus[0];

         HuffmanTree* nn = new HuffmanTree();
         nn->length = n1->length - 1;

         if((n1->tmp & 0x01) == 0)nn->node0 = n1;
         else nn->node1 = n1;

         nn->code = n1->tmp;
         nodes.push_back(nn);

         focus.erase(focus.begin());
      }

      if(focus.size() != 0)throw new Exception("Mööp");
      maxBits--;

   }
   while(nodes.size() > 1);

   return nodes[0];
}


// Reads the next Huffman value from the stream and returns the code
uint16 Inflater::DecodeHuffmanSymbol(Inflater::HuffmanTree* tree)
{
   int16 bits = 0;
   uint16  ret = 0;

   do
   {
      //Nächstes Bit einlesen
      ret <<= 1;
      ret |= NextBit();
      bits++;

      HuffmanTree* symbol = tree->Find(ret, bits);

      if(symbol != NULL)return symbol->symbol;

   }
   while(bits <= MAX_BITS);

   throw new Exception("No Huffman symbol found.");
}

//Erzeugt die Huffmancodes für eine gegebenes Array aus Codelängen
Array<uint16>* Inflater::GetHuffmanCodes(Array<uint16>* codelengths)
{
   //Größte Codelänge
   MAX_BITS = 0;
   for(uint32 a = 0; a < codelengths->size();
         a++)MAX_BITS = (*codelengths)[a] > MAX_BITS ? (*codelengths)[a] : MAX_BITS;

   uint16* blCount = new uint16[MAX_BITS + 1];
   uint16* nextCode = new uint16[MAX_BITS + 1];
   for(uint16 a = 0; a <= MAX_BITS; a++)
   {
      blCount[a] = 0;
      nextCode[a] = 0;
   }

   //1. Zähle die Codelängen
   // Count the number of codes for each code length.  Let
   //    bl_count[N] be the number of codes of length N, N >= 1.
   for(uint32 a = 0; a < codelengths->size(); a++)
   {
      uint16 l = (*codelengths)[a];
      blCount[l]++;
   }

   //2. Kleinsten Wert finden
   //  Find the numerical value of the smallest code for each
   //    code length:

   uint16 code = 0;
   blCount[0] = 0;
   for(uint16 bits = 1; bits <= MAX_BITS; bits++)
   {
      code = (code + blCount[bits - 1]) << 1;
      nextCode[bits] = code;
   }

   //3)  Assign numerical values to all codes, using consecutive
   //values for all codes of the same length with the base
   //    values determined at step 2. Codes that are never used
   //    (which have a bit length of zero) must not be assigned a
   //    value.

   Array<uint16>* codes = new Array<uint16>(codelengths->size());
   //for (int n = 0;  n <= codelengths->Length(); n++)
   for(uint32 n = 0;  n < codelengths->size(); n++)
   {
      int32 len = (*codelengths)[n];
      if(len != 0)
      {
         (*codes)[n] = nextCode[len];
         nextCode[len]++;
      }
      else(*codes)[n] = 0;
   }

   //Aufräumen
   delete [] blCount;
   delete [] nextCode;

   return codes;
}


void Inflater::ReadLengthDists(Array<uint16>* target, Inflater::HuffmanTree* tree, int32 count)
{
   int32 cnt = 0;

   uint16 length;
   uint16 repeat;

   while(cnt < count)
   {
      length = DecodeHuffmanSymbol(tree);


      switch(length)
      {
         //16: Copy the previous code length 3 - 6 times.
         case 16:
            repeat = NextUIntXR(2) + 3;
            for(uint16 a = 0; a < repeat; a++)
            {
               (*target)[cnt] = (*target)[cnt - 1];
               cnt++;
            }
            break;

         //17: Repeat a code length of 0 for 3 - 10 times.
         case 17:
            repeat = NextUIntXR(3) + 3;
            for(uint16 a = 0; a < repeat; a++)
            {
               (*target)[cnt] = 0;
               cnt++;
            }
            break;

         //18: Repeat a code length of 0 for 11 - 138 times
         case 18:
            repeat = NextUIntXR(7) + 11;
            for(uint16 a = 0; a < repeat; a++)
            {
               (*target)[cnt] = 0;
               cnt++;
            }
            break;

         default:
            (*target)[cnt] = length;
            cnt++;
            break;
      }
   }

}



void Inflater::HandleCompressedDynamicHuffman()
{
   //std::cout << "COMPRESSED BLOCK DYNAMIC HUFFMAN\n";

   //Lies die Längenangaben ein
   uint16 HLIT = NextUIntXR(5) + 257;
   uint16 HDIST = NextUIntXR(5) + 1;
   uint16 HCLEN = NextUIntXR(4) + 4;

   //Positionierhilfe für die Codelängen
   const uint16 CODELENTH_ALPHABET[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};

   //Codelängenarray erzeugen und Nullen
   Array<uint16>* codelengths = new Array<uint16>(19);
   for(uint32 a = 0; a < codelengths->size(); a++)(*codelengths)[a] = 0;

   //Einlesen der definierten Codelängen (3 Bit feste Breite)
   for(uint16 a = 0; a < HCLEN; a++)
   {
      uint16 codelength = NextUIntXR(3);
      (*codelengths)[CODELENTH_ALPHABET[a]] = codelength;
   }

   //Erzeuge aus den Codelängen die HuffmanCodes
   Array<uint16>* codes = GetHuffmanCodes(codelengths);

   HuffmanTree* intermediate = CreateTree(codelengths, codes);

   Array<uint16>* lengths2 = new Array<uint16>(HLIT);
   ReadLengthDists(lengths2, intermediate, HLIT);

   Array<uint16>* distances2 = new Array<uint16>(HDIST);
   ReadLengthDists(distances2, intermediate, HDIST);

   Array<uint16>* lengthcodes2 = GetHuffmanCodes(lengths2);

   Array<uint16>* distcodes2 = GetHuffmanCodes(distances2);

   //Workaround
   MAX_BITS = 15;

   HuffmanTree* htvallen = CreateTree(lengths2, lengthcodes2);
   HuffmanTree* htdist = CreateTree(distances2, distcodes2);

   bool endOfBlock = false;
   while(!endOfBlock)
   {
      uint16 value ;

      value = DecodeHuffmanSymbol(htvallen);

      if(value < 256)
      {
         WriteUncompressed((uint8) value);
      }
      else if(value == 256)
      {
         endOfBlock = true;
      }
      else if(value >= 257 && value <= 285)
      {
         //Length
         uint8 extrabits = LENGTH_EXTRA[value - 257];
         uint16 length = NextUIntXR(extrabits);
         length += LENGTH_OFFSET[value - 257];

         //Distance

         //Distance codes 0-31 are represented by (fixed-length) 5-bit
         //codes, with possible additional bits as shown in the table
         //shown in Paragraph 3.2.5, above.

         uint16 code = DecodeHuffmanSymbol(htdist);

         extrabits = DIST_EXTRA[code];
         uint16 distance = NextUIntXR(extrabits);
         distance += DIST_OFFSET[code];

         //move backwards distance bytes in the output
         //stream, and copy length bytes from this
         //position to the output stream.

         Integer src = mUncompIndex - distance;
         if(src < 0)throw new Exception("Distance in fix hufmann refer before output stream beginning.");
         for(int32 a = 0; a < length; a++)
         {
            WriteUncompressed(mUncompBytes[src + a]);
         }
      }
      else throw Exception("Code has unexpected value: " + String::valueOf(value));


   }

   delete codelengths;
   delete codes;
   delete lengths2;
   delete distances2;
   delete lengthcodes2;
   delete distcodes2;
   delete intermediate;
   delete htvallen;
   delete htdist;
}


void Inflater::Inflate()
{

   do
   {
      //Blockheader lesen
      int8 bfinal = NextBit();
      int8 btype = NextBit() + NextBit() * 2;
      if(bfinal == 1)mLastBlock = true;

      //stored with no compression BTYPE = 00
      if(btype == 0)
      {
         HandleUncompressedBlock();
      }
      // Compression with fixed Huffman codes (BTYPE=01)
      else if(btype == 1)
      {
         HandleCompressedFixHuffman();
      }
      else if(btype == 2)
      {
         HandleCompressedDynamicHuffman();
      }
      else throw new Exception("Error in decompression process. Corrupt Block header");

   }
   while(!mLastBlock);

   mEof = true;
}

uint16 Inflater::NextFixedHuffmanCode()
{
   // Siehe RFC 1951 3.2.6
   uint16 code = NextUIntX(7);

   //Mit 7 Bit wird der Bereich 256-279 kodiert:
   // (7 bit) 000 0000 - 001 0111 das entspricht (0 - 23 | 0x00 - 0x17 )
   // 256 addieren ergibt den tatsächlichen Bereich -> 256 - 279 : +256 = +0x100
   if(code <= 0x17)code += 0x100;
   else
   {
      code <<= 1;
      code |= NextBit();

      if(code >= 0xC0
            && code <= 0xC7)  // (8 bit) 1100 0000 - 1100 0111 ( 192 - 199 | 0xC0 - 0xC7 ) -> 280 - 287: +88 = +0x58
         code += 0x58;
      else if(code >= 0x30
              && code <= 0xBF)  // (8 bit) 0011 0000 - 1011 1111 ( 48 - 191 | 0x30 - 0BF ) -> 0 - 143: -48 =-0x30
         code -= 0x30;
      else
      {
         code <<= 1;
         code |= NextBit();
         if(code >= 0x190
               && code <= 0x1FF)  // (9 bit) 1 1001 0000 - 1 1111 1111 ( 400 - 511 | 0x190 - 0x1FF ) -> 144 - 255: -256 =-0x100
            code -= 0x100;
         else throw new Exception("Wrong code");
      }
   }
   return code;
}


Inflater::HuffmanTree::HuffmanTree()
{
   node0 = NULL; // If there is a sub-node and this bit is 0, the system branches to it
   node1 = NULL; // If there is a sub-node and this bit is 1, the system branches to it
   symbol = 0;   // If there is no sub-node, then it is this node and the symbol must match
   length = 0;   // Number of bits that are
   code = 0;     // The code that belongs to this
}

Inflater::HuffmanTree::~HuffmanTree()
{
   if(node0 != NULL)delete node0;
   if(node1 != NULL)delete node1;
}


Inflater::HuffmanTree* Inflater::HuffmanTree::Find(uint16 _code, uint16 bits)
{
   // If it is this node, then give it back
   if(length == bits && code == _code && node0 == NULL && node1 == NULL)return this;

   if(bits > this->length)
   {
      uint16 msk = 0x0001 << (bits - this->length - 1);
      uint16 target = msk & _code;
      if(target == 0 && this->node0 != NULL)return this->node0->Find(_code, bits);
      else if(target != 0 && this->node1 != NULL)return this->node1->Find(_code, bits);
      else throw new Exception("Huffman Tree Error");
   }

   return NULL;
}


