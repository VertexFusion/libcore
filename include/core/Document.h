////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Document.h
// Library:     Jameo Core Library
// Purpose:     Document Interface
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

#ifndef jm_Document_h
#define jm_Document_h

#include "Property.h"
#include "UndoManager.h"
#include "File.h"
#include "Iterator.h"
#include "Preferences.h"

namespace jm
{
   /*!
    \brief This class represents the "model" in the MVC context. This class is also the ideal parent
    class for all document-based applications, because basic functionalities that every user expects
    are already predefined here. In addition, development time is saved. These include:
    - Undo and redo management
    - File path, load and save
    \ingroup core
    */
   class DllExport Document: public jm::Object
   {

      public:

         /*!
          \brief Constructor

          Shall create an empty not initialized document.

          In the constructor here, the UndoManager is already activated. This means that, for
          example, the entire process of reading a document from the hard disk is already "logged"
          as a single undo step. This is absolutely necessary, however, so that when objects are
          deleted, they are retained on the UndoStack, because the LinkedList, for example, does not
          manage the pointers itself, but only via the UndoStack.
          */
         Document();

         /*!
          \brief Destructor
          */
         ~Document() override;

         /*
          *
          * UNDO AND REDO MANAGEMENT
          *
          */

         /*!
          \brief Closes the undo step. This method should be called by applications
          */
         virtual void closeUndoStep();

         /*!
          \brief Returns the undo manager if it exists.
          */
         UndoManager* undoManager();

         /*!
          \brief Determines whether an undo manager exists or not.

          If the value is set to yes and no undomanager exists, one is created. If one already
          exists, nothing happens. If the value is set to no, a possible undo manager is released.

          \param status Turn undo manager on (\c true) or off (\c false).
          */
         void setUndoManager(bool status);

         /*!
          \brief Returns the status of whether an undo manager exists.
          */
         bool hasUndoManager() const;

         /*!
          \brief Returns the status of whether the document has been edited since last saving.

           This value is set to false when saving. Nevertheless, the undo manager can contain steps
           for undo.
          */
         bool isDocumentChanged() const;

         /*!
          \brief Sets the status of whether the file has been changed.

          This method is primary intended for internal use.
          Setting this value affects whether the file is "marked" as changed. Whenever the file is
          saved, this value is set to false. In the undo mechanism, this value is set automatically
          and only needs to be changed manually if you do not use the undo mechanism.

          \param status status if whether the file hase been changed (\c true) or not (\ false)
          */
         void setDocumentChanged(bool status);

         /*
          *
          * FILE PATH, LOAD AND SAVE
          *
          */

         /*!
          \brief Sets the file for this document
          */
         void setFile(const File& file);

         /*!
          \brief Returns the File object of this document.
          */
         const File& file() const;

         File* fileRef();

         /*!
          \brief Saves the file on the drive.

          This method shall called by your software when the file shall be saved.
          file() returns the file.

          Must be implemented by derived classes.
          */
         virtual bool saveDocument() = 0;

         /*!
          \brief Loads the file from the drive.

          This method shall called by your software when the file shall be loaded.
          file() returns the file.

          \warning If this method is to be called, initNewDocument() must not be called and vice
          versa.

          Must be implemented by derived classes.
          */
         virtual bool loadDocument() = 0;

         /*!
          \brief Initializes an "empty" document, ready for the user to work with it.

          The constructor creates an empty, uninitialised document. However, an "empty" and new
          document from the user's point of view may contain content that is mandatory or preset.
          However, this content must not be present when a document is loaded. Therefore, this
          content must be deliberately created here.

          \warning If this method is to be called, loadDocument() must not be called and vice versa.

          \param props Settings, which pass programme settings to the file, if applicable.
          */
         virtual Status initNewDocument(Preferences* props) = 0;

         /*!
          \brief Determines that the visual representation should be renewed for this document in
          the next run.
          */
         virtual void regenerate();

         /*!
         \brief This method should be called by the regeneration method after the visual
         representation of this object has been updated.
         */
         virtual void regenerationDone();

         /*!
         \brief Returns the regeneration status.
         */
         virtual bool shouldRegenerate() const;

      private:

         //! Status whether the visual representation should be renewed in the next run.
         bool mRegenerate;

         //! An undo manager, if it exists. Otherwise NULL.
         UndoManager* mUndoManager;

         //! The file path where the file is stored.
         //! TODO: Change to URI???
         File mFile;

         //! Status on whether the file is changed since last saving.
         bool mChanged;


   };

}

#endif
