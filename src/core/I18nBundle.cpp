////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        I18NBundle.cpp
// Library:     Jameo Core Library
// Purpose:     Helper Class for Internationalization
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     03.06.2013
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

using namespace jm;

I18nBundle* gDefaultTranslation = NULL;


I18nBundle::I18nBundle(const String &appID, const String &name, const String &language, String subfolder): Properties()
{
	mLanguage = language;

	//Suche nach Propertyfile
	File resourceDir = ResourceDir(appID);
	File* f;

	if(subfolder.Length() > 0)
	{
		resourceDir = File(resourceDir, subfolder);
	}

	if(resourceDir.Exists() == false)System::Log("Translation directory does not exist", kLogError);
	System::Log("Translation directoy: " + resourceDir.GetAbsolutePath(), kLogDebug);

	//Suche nach dem Paket in gewünschter Sprache
	f = new File(resourceDir, name + "_" + language + ".properties");
	if(!f->Exists())
	{
		delete f;
		f = NULL;
	}

	if(f == NULL)
	{
		//Nicht gefunden, suche nach dem Paket auf Englisch
		f = new File(resourceDir, name + "_en.properties");
		if(!f->Exists())
		{
			delete f;
			f = NULL;
		}
	}

	if(f == NULL)
	{
		//Nicht gefunden, suche nach dem Paket auf Deutsch
		f = new File(resourceDir, name + "_de.properties");
		if(!f->Exists())
		{
			delete f;
			f = NULL;
		}
	}

	if(f == NULL)
	{
		//Nicht gefunden, suche nach dem Paket ohne Sprachangabe
		f = new File(resourceDir, name + ".properties");
		if(!f->Exists())
		{
			delete f;
			f = NULL;
		}
	}

	if(f != NULL)
	{
		Load(*f);
		delete f;
	}
	else
	{
		System::Log("Cannot find translation file for: " + appID + " " + name + " " + language, kLogError);
	}
}

I18nBundle::I18nBundle(const File &file, const String &language): Properties()
{
	mLanguage = language;

	if(!file.Exists())
	{
		System::Log("Bundle does not exist", kLogError);
		return;
	}
	File* f = new File(file);
	Load(*f);
	delete f;
}

String I18nBundle::Translate(const String& key) const
{
	return GetProperty(key, key);
}


I18nBundle* I18nBundle::GetDefault()
{
	return gDefaultTranslation;
}

void I18nBundle::SetDefault(I18nBundle* bundle)
{
	gDefaultTranslation = bundle;
}
