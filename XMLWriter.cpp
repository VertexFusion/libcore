//
//  XMLWriter.cpp
//  jameo
//
//  Created by Uwe Runtemund on 27.12.20.
//  Copyright © 2020 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

XMLWriter::XMLWriter(jm::Stream* output)
{
	mOutput = output;
}

bool XMLWriter::StartDocument()
{
	mIndent = 0;
	mLastIndent = false;
	if(mOutput->IsOpen() == false)mOutput->Open(kFmWrite);

	mOutput->Write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	return true;
}

bool XMLWriter::EndDocument()
{
	mOutput->Close();
	return true;
}

void XMLWriter::StartIndent()
{
	if(mOpenElements.Size() > 0 && mOpenElements.Top().hasContent == false)
	{
		mOpenElements.TopRef()->hasContent = true;
		mOutput->Write(">");
	}
	mIndent += 3;
	mLastIndent = true;
}

void XMLWriter::EndIndent()
{
	if(mOpenElements.Size() > 0 && mOpenElements.Top().hasContent == false)
	{
		mOpenElements.TopRef()->hasContent = true;
		mOutput->Write(">");
	}
	mLastIndent = false;
	mIndent -= 3;
}

void XMLWriter::StartElement(const jm::String &name)
{

	if(mOpenElements.Size() > 0 && mOpenElements.Top().hasContent == false)
	{
		mOpenElements.TopRef()->hasContent = true;
		mOutput->Write(">");
	}

	if(mLastIndent)
	{
		WriteIndent();
	}


	mOutput->Write("<");
	mOutput->Write(name);

	ElementInfo info;
	info.name = name;
	info.indent = mLastIndent;
	mOpenElements.Push(info);
	mLastIndent = false;
}

void XMLWriter::EndElement()
{
	if(mOpenElements.Top().hasContent == false)
	{
		mOutput->Write("/>");
	}
	else
	{
		if(mOpenElements.Top().indent && mOpenElements.Top().hasCharacters == false)
		{
			WriteIndent();
		}

		mOutput->Write("</");
		mOutput->Write(mOpenElements.Top().name);
		mOutput->Write(">");
	}

	mOpenElements.Pop();
	mLastIndent = false;
}

void XMLWriter::WriteCDATA(const jm::String &cdata, bool xmlencode)
{
	if(mOpenElements.Size() > 0 && mOpenElements.Top().hasContent == false)
	{
		mOpenElements.TopRef()->hasContent = true;
		mOutput->Write(">");
	}

	if(mOpenElements.Size() > 0 && mOpenElements.Top().hasCharacters == false)
	{
		mOpenElements.TopRef()->hasCharacters = true;
	}

	//XML-Codieren
	if(xmlencode)
	{
		jm::String encoded = Encode(cdata);


		mOutput->Write(encoded);
	}
	else
	{
		mOutput->Write(cdata);
	}
	mLastIndent = false;
}

jm::String XMLWriter::Encode(const jm::String &input)
{
	jm::String encoded;
	jm::StringTokenizer st = jm::StringTokenizer(input, "&<>\"'", true);

	while(st.HasMoreTokens())
	{
		jm::String token = st.NextToken();

		if(token.Equals("&"))encoded.Append("&amp;");
		else if(token.Equals("<"))encoded.Append("&lt;");
		else if(token.Equals(">"))encoded.Append("&gt;");
		else if(token.Equals("\""))encoded.Append("&quot;");
		else if(token.Equals("'"))encoded.Append("&apos;");
		else encoded.Append(token);
	}
	return encoded;
}

void XMLWriter::WriteBase64(uint8* data, uint32 length)
{
	if(mOpenElements.Size() > 0 && mOpenElements.Top().hasContent == false)
	{
		mOpenElements.TopRef()->hasContent = true;
		mOpenElements.TopRef()->hasCharacters = true;
		mOutput->Write(">");
	}


	uint8* encoded = jm::Base64::Encode(data, length);
	mOutput->Write(encoded, length);
	delete[] encoded;
	mLastIndent = false;
}


void XMLWriter::WriteAttribute(const jm::String &name, const jm::String &content)
{
	if(mOpenElements.Size() == 0 || mOpenElements.Top().hasContent == true)
	{
		return;
	}

	mOutput->Write(" ");
	mOutput->Write(name);
	mOutput->Write("=\"");
	mOutput->Write(Encode(content));
	mOutput->Write("\"");
	mLastIndent = false;
}

void XMLWriter::WriteAttribute(const jm::String &name, int32 content)
{
	WriteAttribute(name, jm::String::ValueOf(content));
}

void XMLWriter::WriteAttribute(const jm::String &name, uint32 content)
{
	WriteAttribute(name, jm::String::ValueOf(content));
}

void XMLWriter::WriteAttribute(const jm::String &name, float content)
{
	WriteAttribute(name, jm::String::ValueOf(content));
}

void XMLWriter::WriteIndent()
{
	jm::String str;
	str << '\n';
	for(int32 a = 0; a < mIndent; a++)str.Append(' ');
	if(str.Length() == 0)return;
	mOutput->Write(str);
}
