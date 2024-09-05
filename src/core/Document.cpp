////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Document.cpp
// Library:     Jameo Core Library
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

#include "Precompiled.hpp"

using namespace jm;

Document::Document(): Object()
{
   mUndoManager = nullptr;
   mChanged = false;
   mRegenerate = false;
   setUndoManager(true);
}

Document::~Document()
{
   if(mFile.isOpen())mFile.close();


   // We own the undo manage. We delete it.
   if(mUndoManager != nullptr)
   {
      delete mUndoManager;
      mUndoManager = nullptr;
   }
}

void Document::closeUndoStep()
{
   if(mUndoManager != nullptr)mUndoManager->close();
}

UndoManager* Document::undoManager()
{
   return mUndoManager;
}

void Document::setUndoManager(bool status)
{
   if(status)
   {
      if(mUndoManager == nullptr)
      {
         mUndoManager = new UndoManager();
         mUndoManager->setDocument(this);
         mUndoManager->setActive(true);
      }
   }
   else
   {
      if(mUndoManager != nullptr)
      {
         mUndoManager->release();
         mUndoManager = nullptr;
      }
   }
}

bool Document::hasUndoManager() const
{
   return mUndoManager != nullptr;
}

bool Document::isDocumentChanged() const
{
   return mChanged;
}

void Document::setDocumentChanged(bool status)
{
   mChanged = status;
}

void Document::setFile(const File& file)
{
   mFile = file;
}

const File& Document::file() const
{
   return mFile;
}

File* Document::fileRef()
{
   return &mFile;
}

void Document::regenerate()
{
   mRegenerate = true;
}

void Document::regenerationDone()
{
   mRegenerate = false;
}

bool Document::shouldRegenerate() const
{
   return mRegenerate;
}
