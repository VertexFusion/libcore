////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        SAXParser.cpp
// Library:     Jameo Core Library
// Purpose:     SAX parser
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     04.03.2014
//
// Copyright:   (c) 2014 Jameo Software, Germany. https://jameo.de
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

using namespace jm;

SAXParser::SAXParser(): Object()
{

}

SAXParser::~SAXParser()
{

}

void SAXParser::Parse(File &file)
{
	if(!file.Exists())return;
	if(!file.CanRead())return;
	Integer length=file.Length();
	uint8* buffer = new uint8[length];
	file.Open(jm::kFmRead);
	file.ReadFully(buffer, length);
	file.Close();
	jm::String content = jm::String((int8*)buffer);
	delete[] buffer;
	Parse(content);
}

void SAXParser::Parse(const String &xml)
{
	String token;
	token.CheckCapacity(xml.Length());//Sorge dafür, dass Token groß genug ist und nicht bei Binärdaten dauernd vergrößert werden muss..

	StartDocument();

	Integer length = xml.Length(); //Länge dex XML-Codes
	Integer pos = 0; //Position des Zeigers

	Bool inTag = false; //Status, ob man in einem Tag ist
	Bool inValue = false; //Status, ob man in einem Value ist.
	uint16 opener = '\"'; //Zeichen, welches ein Tagwert begrenzt. entweder ' oder "
	uint16 c;

	while(pos < length)
	{
		c = xml.CharAt(pos);

		if(c == '<' && inTag == false && inValue == false) //Tag-Anfang gefunden.
		{
			inTag = true;
			//Gibt Characters aus: \todo IgnorableWhitespaces muss hier noch berücksichtigt werden.
			if(token.Length() > 0)
			{
				String beginWhitespaces;
				String endWhiteSpaces;

				//Whitespaces am Anfang abtrennen
				Integer sub = 0;
				while(sub < token.Length() && CharacterIsWhitespace(token.CharAt(sub)))
				{
					beginWhitespaces.Append(token.CharAt(sub));
					sub++;
				}
				if(beginWhitespaces.Length() > 0)
				{
					//Direkte Zuweisung würde Länge von Token ändern. Daher dieser Umweg
					String tmp = token.Substring(beginWhitespaces.Length());
					token.Zero();
					token.Append(tmp);
				}

				//Whitespaces am Ende abtrennen
				sub = token.Length() - 1;
				while(sub >= 0 && sub < token.Length() && CharacterIsWhitespace(token.CharAt(sub)))
				{
					endWhiteSpaces.Insert(0, token.CharAt(sub));
					sub--;
				}
				if(endWhiteSpaces.Length() > 0)
				{
					//Direkte Zuweisung würde Länge von Token ändern. Daher dieser Umweg
					String tmp = token.Substring(0, token.Length() - endWhiteSpaces.Length());
					token.Zero();
					token.Append(tmp);
				}

				if(beginWhitespaces.Length() > 0)
				{
					token.Insert(0, beginWhitespaces.CharAt(beginWhitespaces.Length() - 1));
					beginWhitespaces.DeleteCharAt(beginWhitespaces.Length() - 1);
				}

				if(endWhiteSpaces.Length() > 0)
				{
					token.Append(endWhiteSpaces.CharAt(0));
					endWhiteSpaces.DeleteCharAt(0);
				}

				//Parsing-Methoden aufrufen
				if(beginWhitespaces.Length() > 0)IgnorableWhiteSpaces(beginWhitespaces);
				if(token.Length() > 0)Characters(token);
				if(endWhiteSpaces.Length() > 0)IgnorableWhiteSpaces(endWhiteSpaces);
			}

			token.Zero();
		}
		else if(c == '&' && inTag == false)
		{
			String escape;
			do
			{
				pos++;
				c = xml.CharAt(pos);
				escape.Append(c);
			}
			while(c != ';' && pos < length);

			if(escape.Equals("lt;"))token.Append('<');
			else if(escape.Equals("gt;"))token.Append('>');
			else if(escape.Equals("amp;"))token.Append('&');
			else if(escape.Equals("quot;"))token.Append('"');
			else if(escape.Equals("le;"))token.Append(0x2264); //≤
			else if(escape.Equals("ge;"))token.Append(0x2265); //≥
			else if(escape.Equals("leq;"))token.Append(0x2264); //≤
			else if(escape.Equals("geq;"))token.Append(0x2265); //≥
		}
		else if(c == '>' && inTag == true && inValue == false)
		{
			ParseTagString(token);
			token.Zero();
			inTag = false;
		}
		else if((c == '\"' || c == '\'') && inTag == true)
		{
			if(inValue == false)
			{
				inValue = true;
				opener = c;
			}
			else if(inValue == true && opener == c)
			{
				inValue = false;
			}
			token.Append(c);
		}
		else token.Append(c);


		pos++;
	}

	EndDocument();
}

void SAXParser::ParseTagString(const String &xmlline)
{
	String line = xmlline;

	line.Append(' ');//Whitespace am Ende erleichtert das Parsen, weil Code gespart wird.

	Integer pos = 0; //Position des Zeigers
	Integer length = line.Length(); //Länge
	bool inValue = false; //Status, ob man in einem Value ist.
	uint16 c;
	uint16 opener = 0;
	Integer tagType = 0; //0: Open, 1: Close 2: Open/Close
	Integer step = 0; // 0:Tagname, 1: Attributname, 2:Attributwert

	//Prüfe auf / am Ende
	pos = line.Length() - 1;
	while(CharacterIsWhitespace(line.CharAt(pos)))pos--;
	if(line.CharAt(pos) == '/')
	{
		tagType = 2;
	}


	//Überspringe Whitespaces am Anfang
	pos = 0;
	while(CharacterIsWhitespace(line.CharAt(pos)))pos++;

	//Prüfe auf / am Anfang
	if(line.CharAt(pos) == '/')
	{
		tagType = 1;
		pos++;
	}


	String token;//Aktuelles Token
	String tname;//Name des Tags
	String aname;//Name des Attributs
	String avalue;//Wert des Attributs

	SAXAttributes attribs;

	while(pos < length)
	{
		c = line.CharAt(pos);

		if(c == '\"' || c == '\'')
		{
			if(inValue == false)
			{
				inValue = true;
				opener = c;
			}
			else if(inValue == true && opener == c)
			{
				inValue = false;

				if(step == 2)
				{
					avalue = token;
					step--;
					attribs.AddAttribute("", aname, aname, avalue);
					token.Clear();
				}
			}
			else token.Append(c);
		}
		else if(c == '&' && inValue == true)
		{
			String escape;
			do
			{
				pos++;
				c = line.CharAt(pos);
				escape.Append(c);
			}
			while(c != ';' && pos < length);

			if(escape.Equals("lt;"))token.Append('<');
			else if(escape.Equals("gt;"))token.Append('>');
			else if(escape.Equals("amp;"))token.Append('&');
			else if(escape.Equals("quot;"))token.Append('"');
		}
		else if((CharacterIsWhitespace(c) || c == '=' || c == '/') && !inValue)
		{
			//Verarbeite Token
			if(token.Length() > 0)
			{
				if(step == 0)
				{
					tname = token;
					step++;
				}
				else if(step == 1)
				{
					aname = token;
					step++;
				}
				token.Clear();
			}
		}
		else token.Append(c);

		pos++;
	}

	//Verarbeite im Parser
	String qualifiedName = tname;
	String localName = qualifiedName.Substring(qualifiedName.LastIndexOf(':') + 1);
	switch(tagType)
	{
		case 0:
			StartElement("", localName, qualifiedName, attribs);
			break;

		case 1:
			EndElement("", localName, qualifiedName);
			break;

		case 2:
			StartElement("", localName, qualifiedName, attribs);
			EndElement("", localName, qualifiedName);
			break;

	}

}

void SAXParser::Characters(const String& /*characters*/)
{
	// Dummy method
	//	std::cout << "SAX: Characters: " << std::endl;
}

void SAXParser::EndDocument()
{
	// Dummy method
	//	std::cout << "SAX: EndDocument" << std::endl;
}

void SAXParser::EndElement(const String& /*uri*/,
                           const String& /*localName*/,
                           const String& /*qName*/)
{
	// Dummy method
	//	std::cout << "SAX: EndElement " << localName << std::endl;
}

void SAXParser::EndPrefixMapping(const String& /*prefix*/)
{
	// Dummy method
	//	std::cout << "SAX: EndPrefixMapping" << std::endl;
}

void SAXParser::IgnorableWhiteSpaces(const String& /*characters*/)
{
	// Dummy method
	//	std::cout << "SAX: IgnorableWhitespaces" <<std::endl;
}

void SAXParser::ProcessingInstruction(const String& /*target*/,
                                      const String& /*data*/)
{
	// Dummy method
	//	std::cout << "SAX: ProcessingInstruxtion" << std::endl;
}

void SAXParser::SkippedEntity(const String& /*name*/)
{
	// Dummy method
	//	std::cout << "SAX: SkippedEntity" << std::endl;
}

void SAXParser::StartDocument()
{
	// Dummy method
	//	std::cout << "SAX: StartDocument" << std::endl;
}

void SAXParser::StartElement(const String& /*uri*/,
                             const String& /*localName*/,
                             const String& /*qName*/,
                             const SAXAttributes& /*attributes*/)
{
	// Dummy method
	//	std::cout << "SAX: StartElement " << localName  << " " << attributes.GetLength() << std::endl;
}
