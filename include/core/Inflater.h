////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Inflater.h
// Library:     Jameo Core Library
// Purpose:     Itrator Interface
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

#ifndef jm_Inflater_h
#define jm_Inflater_h

#include "Array.h"

namespace jm
{

   /*!
    \brief Decompression class for DEFLATE-compressed data.
    Basis are RFC 1950 and RFC 1951.
    \ingroup core
    */
   class DllExport Inflater: public Object
   {
      private:

         // The tree is constructed analogously to RFC 1951.
         struct HuffmanTree
         {
            HuffmanTree* node0;
            HuffmanTree* node1;
            uint16 symbol;
            uint16 length;
            uint16 code;
            uint16 tmp;
            HuffmanTree();
            ~HuffmanTree();
            HuffmanTree* Find(uint16 code, uint16 bits);
         };

         // Current Block
         uint8* mCompBytes;
         int64 mCompLength;
         int64 mCompIndex;

         // Current Block
         uint8* mUncompBytes;
         int64 mUncompLength;
         int64 mUncompIndex;

         // Counting variables for processed bytes.
         int64 mTotalIn;
         int64 mTotalOut;

         int32 mBit; // Index of the current bit in the current byte.

         // Status indicating whether the last block has been read
         bool mLastBlock;

         // Status indicating whether the end of the stream has been reached
         bool mEof;

         // Status, indicating whether the zlib header and CRC are omitted
         bool mWrap;

         // Maximum number of bits in the current Huffman tree
         uint16 MAX_BITS;

         /*!
          \brief Reads the next bit from the input stream.
          */
         uint8 nextBit();

         /*!
          \brief Skips all bits until the end of the current byte in the input stream and jumps to the beginning of the next byte.
          If already at the beginning of a byte, nothing happens.
          */
         void skipByteBits();

         /*!
          \brief Returns the next "aligned" byte. Must be at the beginning of a byte.
          \throws If not at the beginning of a byte, an error occurs.
          */
         uint8 nextAlignedUInt8();

         /*!
          \brief Reads a UINT16 in little-endian format. Must be at the beginning of a byte.
          \throws If not at the beginning of a byte, an error occurs.
          */
         uint16 nextAlignedUInt16();

         /*!
          \brief Reads the next X bits as a number. Byte boundaries are ignored.
          The MSB (Most Significant Bit) is read first.
          \param bits The number of bits
          */
         uint16 nextUIntX(uint8 bits);

         /*!
          \brief Reads the next X bits as a number. Byte boundaries are ignored.
          The LSB (Least Significant Bit) is read first.
          \param bits The number of bits
          */
         uint16 nextUIntXR(uint8 bits);

         HuffmanTree* createTree(Array<uint16>* lengths, Array<uint16>* codes);

         uint16 decodeHuffmanSymbol(Inflater::HuffmanTree* tree);

         Array<uint16>* huffmanCodes(Array<uint16>* codelengths);

         // Writes the byte to the output buffer.
         void writeUncompressed(uint8 byte);

         /*!
          \brief This method is used for the "BTYPE=01" encoding "Fixed Huffman Codes".
          It reads the next "Fixed Huffman Code" and decodes it to the desired numerical value.
          */
         uint16 nextFixedHuffmanCode();

         void handleUncompressedBlock();

         void handleCompressedFixHuffman();

         void handleCompressedDynamicHuffman();

         void readLengthDists(Array<uint16>* target, Inflater::HuffmanTree* tree, int32 count);

         void inflate();

         void checkCapacity();


      public:
         /*!
          \brief Constructor
          */
         Inflater();

         /*!
          \brief Constructor
          \param wrap Status, if zlib-Header and CRC is omitted.
          */
         explicit Inflater(bool wrap);

         /*!
          \brief Destructor
          */
         ~Inflater() override = default;

         /*!
          \brief Passes a block of bytes to this class for decompression.
          \param buffer The compressed data
          \param length The length of the data
          */
         void SetInput(uint8* buffer, int64 length);

         /*!
          \brief Returns true if the end of the input block has been reached, but the end of the input stream has not been reached yet.
          */
         bool NeedsInput();

         /*!
          \brief Returns true if the end of the input stream has been reached.
          */
         bool Finished();

         /*!
          \brief This method decompresses the data into the buffer.
          \discussion Both parameters are output values and will be initialized by this method. The caller must clean up the array afterwards.
          \param buffer The buffer to write the data into.
          \param length The length of the buffer.
          */
         void Inflate(uint8*& buffer, int64& length);

         /*!
          \brief Resets the decompressor, allowing a new object to be decompressed.
          */
         void Reset();

         /*!
          \brief Returns the number of remaining bytes in the input buffer.
          \return The number of remaining bytes.
          */
         int64 GetRemaining();

         /*!
          \brief Returns the total number of bytes in the compressed input.
          \return The total number of bytes.
          */
         int64 GetTotalIn();

         /*!
          \brief Returns the total number of bytes of the decompressed output.
          \return The total number of bytes.
          */
         int64 GetTotalOut();

   };

}
#endif
