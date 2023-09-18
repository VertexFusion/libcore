////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Document.cpp
// Library:     VertexFusion Library
// Purpose:     Implementation of Document Interface
//
// Author:      Uwe Runtemund (2016-today)
// Modified by:
// Created:     20.05.2016
//
// Copyright:   (c) 2016 Jameo Software, Germany. https://jameo.de
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

Document::Document(): Object()
{
	mUndoManager = NULL;
	mChanged = false;
	mRegenerate = false;
	SetUndoManager(true);
}

Document::~Document()
{
	if(mFile.IsOpen())mFile.Close();


	// We own the undo manage. We delete it.
	if(mUndoManager != NULL)
	{
		delete mUndoManager;
		mUndoManager = NULL;
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

bool Document::HasUndoManager() const
{
	return mUndoManager != NULL;
}

bool Document::IsDocumentChanged() const
{
	return mChanged;
}

void Document::SetDocumentChanged(bool status)
{
	mChanged = status;
}

void Document::SetFile(const File &file)
{
	mFile = file;
}

File* Document::GetFile()
{
	return &mFile;
}

void Document::Regenerate()
{
	mRegenerate = true;
}

void Document::RegenerationDone()
{
	mRegenerate = false;
}

bool Document::ShouldRegenerate() const
{
	return mRegenerate;
}
