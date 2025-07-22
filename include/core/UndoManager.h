////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        UndoManager.h
// Library:     Jameo Core Library
// Purpose:     Undo/Redo Management
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     11.02.2014
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

#ifndef jm_UndoManager_h
#define jm_UndoManager_h

#include "UndoData.h"

/*!
 \defgroup datamgr Data Management

 \brief A collection of classes to provide data management (Undo, Redo, Transactions).

 Jameo Core library provides rich features for data management. In any modern software,
 error-tolerant input by the user is expected. In particular, it is expected that incorrect input
 can be undone or that data is checked for inconsistency when it is entered.

 All these possibilities are implemented here in a programmer-friendly way.

 Example for implementing undo management in data structure:
~~~~~{.cpp}
#include "core/Core.h"

// Example Person shows principle procedure to implement undo management.
class Person: public jm::EditableObject
{
	public:

      // Constructor
      Person(jm::Document* doc):jm::EditableObject(doc)
      {
      };

      // Example setter
      jm::Status setName(const jm::String& name)
      {
         return setMember(&mName,name);
      };

      // Example getter
      const jm::String& name() const
      {
         return mName;
      }

   private:

      // Name of the person
      jm::String mName;
};
~~~~~


Example of calling undo/redo:
~~~~~{.cpp}
...
   jm::Document* doc = ...; // Already initialized
   Person* p = ...;
   jm::UndoManager* um = doc->undoManager();

   p->setName("Uwe");

   // Close the undo step if changes are done.
   um->close();

   // Undo, if necessary
   um->undo();

   // Redo, if necessary
   um->redo();
...
~~~~~

When you want to ensure, that several changes will only be done at all, use transactions:
~~~~~{.cpp}
...
   jm::Document* doc = ...; // Already initialized
   Person* p = ...;
   jm::UndoManager* um = doc->undoManager();
   um->openTransaction();
   p->setName("Uwe");
   p->setGender("male");

   // Close the undo step if changes are done.
   um->closeTransaction();

...
~~~~~

 */

namespace jm
{
   class Document;

   /*!
    \brief This class represents the manager for undo operations.

    Editing steps on a document are registered here, and the undo manager belongs to the
    corresponding document, so that each document owns its own undo manager. This makes it possible
    to undo editing steps on the document independently of the editing procedure.

   However, it is necessary to consider by the developer the form in which processing steps are
   atomised.

    - In the case of manual editing, e.g. in a UI, each small editing step should be undoable.
    - With scripts (JS or C++), it may be useful for the entire script to be an undo step.

    Therefore, there is the following procedure:

    To complete the current editing step, the method Close() must be called.
    The developer must do this manually. Otherwise, all changes are saved in one step.

    \ingroup datamgr
    */
   class DllExport UndoManager: public Object
   {
      public:

         /*!
          \brief Constructor
          */
         UndoManager();

         /*!
          \brief Destructor
          */
         ~UndoManager() override;

         /*!
          \brief Sets the document associated with this manager.
          This enables automatic tracking of changes.
          \param document The document to be associated with this manager.
          */
         void setDocument(jm::Document* document);

         /*!
          \brief Sets whether changes should be tracked or not.
          \param status True if changes should be tracked.
          */
         void setActive(bool status);

         /*!
          \brief Returns the status of the manager, indicating whether changes are being tracked.
          \return True if changes are being tracked.
          */
         bool isActive() const;

         /*!
          \brief Returns true, if a undo step is open.
          */
         bool hasOpenUndoStep() const;

         /*!
          \brief Undoes the last editing step on the file and pushes the change to the RedoStack.
          \return Returns true if Undo was performed successfully, otherwise false.
          */
         bool undo();

         /*!
          \brief Repeats the last editing step, undoing previous "undos".
          \return True if redo was performed successfully, false otherwise.
          */
         bool redo();

         /*!
          \brief This method finalizes the current editing step.
          Programmers must explicitly mark the completion of an editing step that should be undone as a whole.
          - Only when a step is completed, undo or redo can be performed.
          - The step is only completed if there are changes.
          */
         void close();

         friend class Document;

         /*!
          \brief This method clears the Undo-Stack and the Redo-Stack manually.
          */
         void clearStacks();

         /*!
          \brief This method clears the Undo-Stack manually.
          */
         void clearUndoStack();

         /*!
          \brief This method clears the Redo-Stack manually.
          */
         void clearRedoStack();

         /*!
          \brief Returns the number of elements on the Undo-Stack.
          */
         unsigned int undoCount() const;

         /*!
          \brief Returns the number of elements on the Redo-Stack.
          */
         unsigned int redoCount() const;

         /*!
          \brief This method registers a change in the file where a float value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, float* pointer);

         /*!
          \brief This method registers a change in the file where a double value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, double* pointer);

         /*!
          \brief This method registers a change in the file where a boolean value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, bool* pointer);

         /*!
          \brief This method registers a change in the file where an unsigned short value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, int8* pointer);

         /*!
          \brief This method registers a change in the file where an unsigned short value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, uint8* pointer);

         /*!
          \brief This method registers a change in the file where an unsigned short value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, int16* pointer);

         /*!
          \brief This method registers a change in the file where an unsigned short value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, uint16* pointer);

         /*!
          \brief This method registers a change in the file where an int32 value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, int32* pointer);

         /*!
          \brief This method registers a change in the file where an uint32 value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, uint32* pointer);

         /*!
          \brief This method registers a change in the file where a Integer value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, Integer* pointer);

         /*!
          \brief This method registers a change in the file where a int64 value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, int64* pointer);

         /*!
          \brief This method registers a change in the file where a long value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, uint64* pointer);

#if defined(JM_MACOS) || defined(JM_IOS)
         /*!
          \brief This method registers a change in the file where a long value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, size_t* pointer);
#endif

         /*!
          \brief This method registers a change in the file where a Vertex3 value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, Vertex2* pointer);

         /*!
          \brief This method registers a change in the file where a Vertex3 value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, Vertex3* pointer);

         /*!
          \brief This method registers a change in the file where a string value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, String* pointer);

         /*!
          \brief This method registers a change in the file where a Date value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, Date* pointer);

         /*!
          \brief This method registers a change in the file where a color value of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, Color* pointer);

         /*!
          \brief This method registers a general change in the file. This method is used when the user derives their own custom change steps.
          \param change The change to be registered.
          */
         void registerChange(UndoChange* change);

         /*!
          \brief This method registers a change in the file where an object reference of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, Object** pointer);

         /*!
          \brief This method registers a change in the file where an object reference of an object is modified.
          If the UndoManager is not active, nothing happens.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object whose value is being modified.
          \param pointer A pointer to the value that will be modified. This method automatically saves the old value.
          */
         void registerChange(Object* object, uint8** pointer, uint64 length);

         /*!
          \brief This method registers a regeneration marker that is triggered at every
          undo/redo step to regenerate objects in the view.
          \details This method opens an undo step and also resets the RedoStack.
          \param object The object that needs to be regenerated in the view.
          */
         void registerRegenerationMarker(EditableObject* object);

         void registerRelease(Object* object);

         void registerRetain(Object* object);

         /*!
          \brief Begin a transaction.

          A transaction is used to change data on objects, which have a meaningful relationship
          and always shall be consistent. So after changing data, you have to decide of committing
          a transaction or rollback the data to previous state.

          Each time this method is called, the transaction level increments.

          \see closeTransaction()
          \see EditableObject::openTransaction();
          */
         void openTransaction();

         /*!
          \brief Commit the content of the transaction to the current undo step.

          Each time this method is called, the transaction level decrements.

          If the transaction level is still > 0, nothing happens. Only if the level is back to 0
          the commit of changes happens, whether the transaction status value.

          \warning Usually you not need to call this method, because closeTransaction() is doing
          the necessary stuff. Probably we change this method to private in the future.
          */
         void commit();

         /*!
          \brief Rollback all changes of the transaction.

          Each time this method is called, the transaction level decrements.

          If the transaction level is still > 0, nothing happens. Only if the level is back to 0
          the rollback of changes happens, whether the transaction status value.

          \warning Usually you not need to call this method, because closeTransaction() is doing
          the necessary stuff. Probably we change this method to private in the future.
          */
         void rollback();

         /*!
          \brief Closes the transaction.

          Dependent on the value of the transaction status, this method decides to call Commit()
          or Rollback();

          If the transaction level is still > 0, nothing happens. Only if the level is back to 0
          the closing actions happens.

          \see openTransaction()
          \see EditableObject::closeTransaction();
          */
         Status closeTransaction();

         /*!
          \brief Returns true, if a transaction is open.

          The transaction is open, if the transaction level is > 0.
          */
         bool hasOpenTransaction() const;

         /*!
          \brief This method registers the status of operations during a transaction. As long
          as status is eOK, nothing happens. If status is not eOk, we register a transaction error.
          */
         void registerTransactionStatus(Status status);

         /*!
          \brief Returns the transaction status.
          */
         Status transactionStatus() const;

         UndoStep* openStep();

      private:

         //! \brief The document this manager belongs to.
         jm::Document* mDocument;

         //! \brief Status, if changes shall be registered and logged.
         bool mActive;

         /*!
          \brief Indicates whether the Undo process is active, preventing changes made by the manager from being re-registered.
          */
         bool mUndoing;

         /*!
          \brief Indicates whether a editing step is currently open. If an editing step is open, undo or redo operations cannot be performed.
          */
         bool mOpen;

         /*!
          \brief The Undo stack for storing Undo operations.
          The topmost Undo step is the most recent one.
          */
         UndoStep* mUndoStack;

         /*!
          \brief The current editing step.
          */
         UndoStep* mCurrent;

         /*!
          \brief The Redo stack for storing Redo operations.
          The topmost Redo step is the most recent one.
          */
         UndoStep* mRedoStack;

         /*!
          \brief The number of elements on the Undo stack.
          */
         uint32 mUndoCount;

         /*!
          \brief The number of elements on the Redo stack.
          */
         uint32 mRedoCount;

         //! If a transaction is used, this indicates the level of transaction
         int64 mTransactionLevel;

         //! If a transaction is active, this is the content of the transaction.
         UndoStep* mTransaction;

         //! The transaction status
         Status mTransactionStatus;
   };

}


#endif
