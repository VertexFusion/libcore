//
//  Document.cpp
//  jameo
//
//  Created by Uwe Runtemund on 20.05.16.
//  Copyright © 2016 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

Document::Document(): Object()
{
	mUndoManager = NULL;
	mFile = NULL;
	mChanged = false;
	SetUndoManager(true);
}

Document::~Document()
{
	if(mUndoManager != NULL)
	{
		mUndoManager->Release();
		mUndoManager = NULL;
	}

	if(mFile != NULL)
	{
		if (mFile->IsOpen())mFile->Close();
		mFile->Release();
		mFile = NULL;
	}
}


UndoManager* Document::GetUndoManager()
{
	return mUndoManager;
}

void Document::SetUndoManager(bool status)
{
	if(status)
	{
		if(mUndoManager == NULL)
		{
			mUndoManager = new UndoManager();
			mUndoManager->SetDocument(this);
			mUndoManager->SetActive(true);
		}
	}
	else
	{
		if(mUndoManager != NULL)
		{
			mUndoManager->Release();
			mUndoManager = NULL;
		}
	}
}

bool Document::HasUndoManager()
{
	return mUndoManager != NULL;
}

bool Document::IsDocumentChanged()
{
	return mChanged;
}

void Document::SetDocumentChanged(bool status)
{
	mChanged = status;
}

void Document::SetFile(File* file)
{
	if(file != NULL)file->Retain();
	if(mFile != NULL)mFile->Release();
	mFile = file;

}

File* Document::GetFile()
{
	return mFile;
}
