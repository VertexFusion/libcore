//
//  I18nBundle.cpp
//  jameo
//
//  Created by Uwe Runtemund on 03.06.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

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
		Load(f);
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
	Load(f);
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
