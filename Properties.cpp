//
//  Properties.cpp
//  Gems Mine
//
//  Created by Uwe Runtemund on 23.08.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

Properties::Properties(): Hashtable()
{
}


Properties::~Properties()
{
	Iterator* i = Keys();
	while(i->HasNext())
	{
		String* s = static_cast<String*>(i->Next());
		String* p = static_cast<String*>(Get(*s));
		delete p;
	}
	delete i;
}


void Properties::Load(File* file)
{
	uint32 l = (uint32) file->Length();
	uint8* buffer = new uint8[l];
	file->Open(kFmRead);
	uint32 check = file->ReadFully(buffer, l);
	file->Close();
	String data = String(buffer, l);
	delete[] buffer;

	if(check != l)throw new Exception("Property file uncomplete loaded.");

	StringTokenizer* st = new StringTokenizer(data, "\r\n", false);

	//Zeilenweise einlesen
	while(st->HasMoreTokens())
	{
		String line = st->NextToken();

		int32 pos = line.IndexOf('=');
		if(pos > 0)
		{
			String key = line.Substring(0, pos).Trim();
			String value = line.Substring(pos + 1).Trim();

			//Prüfe auf Zeilenumbruch
			while((pos = value.IndexOf("\\n")) > 0)
			{
				value = value.Substring(0, pos) + "\n" + value.Substring(pos + 2);
			}

			//Ersetze
			uint32 index = 0;
			while(index < value.Length())
			{
				int8 c = value.CharAt(index);

				if(c == '\\' && index + 1 < value.Length())
				{
					int8 d = value.CharAt(index + 1);
					if(d == 't')
					{
						value.SetCharAt(index, '\t');
						value.DeleteCharAt(index + 1);
					}
					if(d == '\\')
					{
						value.DeleteCharAt(index + 1);
					}
				}
				index++;
			}

			SetProperty(key, value);
		}
	}
	delete st;

}

void Properties::Store(File* file)
{
	try
	{
		file->Open(kFmWrite);

		Iterator* keys = Keys();

		while(keys->HasNext())
		{
			String key = *static_cast<String*>(keys->Next());
			String value = GetProperty(key);

			//Ersetzungen
			//Ersetze
			int32 index = 0;
			while(index < value.Length())
			{
				int8 c = value.CharAt(index);

				if(c == '\\')
				{
					value.Insert(index + 1, '\\');
					index++;
				}
				else if(c == '\t')
				{
					value.SetCharAt(index, '\\');
					value.Insert(index + 1, 't');
					index++;
				}
				index++;
			}

			//Zeile bilden
			key.Append('=');
			key.Append(value);
			key.Append(String::LineSeparator());
			int8* cstr = key.ToCString();
			int32 cl = 0;
			while(cstr[cl] != 0)cl++;
			file->Write((uint8*)cstr, cl);
			delete cstr;
		}

		file->Close();
	}
	catch(Exception* e)
	{
		e->PrintStackTrace();
		System::Log("Cannot save property file: " + file->GetAbsolutePath(), kLogError);
		delete e;
	}
}

void Properties::SetProperty(const String &key, const String &value)
{
	String tmp = value;
	tmp = tmp.ReplaceAll("\r\n", "\\n");
	tmp = tmp.ReplaceAll("\r", "\\n");
	tmp = tmp.ReplaceAll("\n", "\\n");
	String* actual = new String(tmp);
	String* old = static_cast<String*>(Put(key, actual));
	if(old != NULL)delete old;
}

void Properties::SetProperty(const String &key, int32 value)
{
	SetProperty(key, String::ValueOf(value));
}


void Properties::SetProperty(const String &key, bool value)
{
	SetProperty(key, static_cast<String>(value ? "true" : "false"));
}

String Properties::GetProperty(const String &key) const
{
	String* result = (String*)Get(key);
	if(result == NULL)return kEmptyString;
	return *result;
}

String Properties::GetProperty(const String &key, String const &defaultValue) const
{
	String* result = static_cast<String*>(Get(key));
	if(result == NULL)return defaultValue;
	return *result;
}

int32 Properties::GetPropertyInt(const String &key, int32 defaultValue) const
{
	String result = GetProperty(key);

	if(result.Length() == 0)return defaultValue;

	int32 value = defaultValue;
	try
	{
		value = static_cast<int32>(Integer::ValueOf(result));
	}
	catch(Exception* e)
	{
		delete e;
	}

	return value;
}

bool Properties::GetPropertyBool(const String &key, bool defaultValue) const
{
	String result = GetProperty(key);

	if(result.Length() == 0)return defaultValue;

	return result.Equals("true");
}
