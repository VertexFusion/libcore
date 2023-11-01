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
			 \brief Konstructor
			 */
			UndoManager();

			/*!
			 \brief Destructor
			 */
			~UndoManager();

			/*!
			 \brief Legt das Dokument fest, welches mit diesem Manager assoziiert wird.
			 Dadurch werden Änderungen automatisch verfolgt.
			 */
			void SetDocument(jm::Document* document);

			/*!
			 \brief Legt fest, ob Änderungen verfolgt werden sollen, oder nicht
			 \param status Wahr, wenn Änderungen verfolgt werden sollen.
			 */
			void SetActive(bool status);

			/*!
			 \brief Gibt den Statis zurück, ob der Manager aktiv ist.
			 \return wahr, wenn Änderungen verfolgt werden.
			 */
			bool IsActive() const;

			/*!
			 \brief Returns true, if a undo step is open.
			 */
			bool HasOpenUndoStep() const;

			/*!
			 \brief Diese Methode macht den letzten Bearbeitungsschritt an der Datei rückgängig. Und
			 schiebt die Änderung auf den RedoStack.
			 \return Gibt wahr zurück, wenn Undo durchgeführt wurde. Andernfalls falsch.
			 */
			bool Undo();

			/*!
			 \brief Diese Methode wiederholt den letzen Bearbeitungsschritt. Damit werden "Undos"
			 wieder rückgängig gemacht.
			 \return Gibt wahr zurück, wenn Redo durchgeführt wurde. Andernfalls falsch.
			 */
			bool Redo();

			/*!
			 \brief Diese Methode schließt den aktuellen Bearbeitungsschritt ab.
			 Programmierer müssen den Abschluss eines Bearbeitungsschrittes, der als ganzes Rückgängig
			 gemacht werden soll, selbst festlegen.
			 - Nur wenn ein Schritt abgeschlossen ist, kann Rückgängig oder Wiederherstellen ausgeführt
			   werden.
			 - Nur wenn Änderungen vorhanden sind, wird der Schritt abgeschlossen.
			 */
			void Close();

			/*!
			 \brief Diese Methode löscht den Undo-Stack und den Redo-Stack manuell
			 */
			void ClearStacks();

			/*!
			 \brief Diese Methode löscht den Undo-Stack manuell
			 */
			void ClearUndoStack();

			/*!
			 \brief Diese Methode löscht den Redo-Stack manuell
			 */
			void ClearRedoStack();

			/*!
			 \brief Gibt die Anzahl der Elemente auf dem Undo-Stack zurück
			 */
			unsigned int GetUndoCount();

			/*!
			 \brief Gibt die Anzahl der Elemente auf dem Undo-Stack zurück
			 */
			unsigned int GetRedoCount();

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein float-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, float* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein double-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, double* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein double-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, Double* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein bool-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, bool* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein unsigned
			 short-Wert eines Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist,
			 passiert gar nichts...
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, int8* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein unsigned
			 short-Wert eines Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist,
			 passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, uint8* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein unsigned
			 short-Wert eines Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist,
			 passiert gar nichts...
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, int16* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein unsigned
			 short-Wert eines Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist,
			 passiert gar nichts...
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, uint16* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein int-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, int32* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein int-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, uint32* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein long-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, Integer* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein long-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, int64* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein long-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, uint64* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein Vertex3-Wert
			 eines Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar
			 nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, Vertex2* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein Vertex3-Wert
			 eines Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar
			 nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, Vertex3* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein String-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, String* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein Date-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, Date* pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem ein Farb-Wert eines
			 Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, Colour* pointer);

			/*!
			 \brief Diese Methode registriert eine allgemeine Änderung an der Datei. Diese Methode
			 wird gebraucht, wenn der Anwender eigene Änderungsschritte ableitet.
			 */
			void RegisterChange(UndoChange* change);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem eine Objektreferenz
			 eines Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar
			 nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, Object** pointer);

			/*!
			 \brief Diese Methode registriert eine Änderung an der Datei, bei dem eine Objektreferenz
			 eines Objektes verändert wird. Wenn der Rückgängigmanager nicht aktiv ist, passiert gar
			 nichts.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 \param pointer Der Zeiger auf den Wert, der Verändert werden soll, bevor er verändert
			 wird. Diese Methode sichert automatisch den alten Wert.
			 */
			void RegisterChange(Object* object, uint8** pointer, uint64 length);

			/*!
			 \brief Diese Methode registriert einen Regenerations-Marker, der bei jedem
			 Undo/Redo-Schritt ausgelöst wird, damit Objekte in der Ansicht neu regenriert werden.
			 \discussion Diese Methode öffnen einen Rückgängigschritt und setzt ebenfalls den
			 Redo-Stack zurück.
			 */
			void RegisterRegenerationMarker(EditableObject* object);

			void RegisterRelease(Object* object);

			void RegisterRetain(Object* object);

			/*!
			 \brief Begin a transaction.

			 A transaction is used to change data on objects, which have a meaningfull relationship
			 and always shall be consistent. So after changing data, you have to decide of commiting
			 a transaction or rollback the data to previous state.

			 Each time this method is called, the transaction level increments.
			 */
			void OpenTransaction();

			/*!
			 \brief Commit the content of the transaction to the current undo step.

			 Each time this method is called, the transaction level decrements.

			 If the transaction level is still > 0, nothing happens. Only if the level is back to 0
			 the commit of changes happens, whether the transaction status value.
			 */
			void Commit();

			/*!
			 \brief Rollback all changes of the transaction.

			 Each time this method is called, the transaction level decrements.

			 If the transaction level is still > 0, nothing happens. Only if the level is back to 0
			 the rollback of changes happens, whether the transaction status value.
			 */
			void Rollback();

			/*!
			 \brief Closes the transaction.

			 Dependend on the value of the transaction status, this method decides to call Commit()
			 or Rollback();

			 If the transaction level is still > 0, nothing happens. Only if the level is back to 0
			 the closing actions happens.
			 */
			VxfErrorStatus CloseTransaction();

			/*!
			 \brief Returns true, if a transaction is open.

			 The transaction is open, if the transaction level is > 0.
			 */
			bool HasOpenTransaction() const;

			/*!
			 \brief This method registers the status of operations during a transaction. As long
			 as status is eOK, nothing happens. If status is not eOk, we register a transaction error.
			 */
			void RegisterTransactionStatus(VxfErrorStatus status);

			/*!
			 \brief Returns the transaction status.
			 */
			VxfErrorStatus GetTransactionStatus() const;


		private:

			//! \brief The document this manager belongs to.
			jm::Document* mDocument;

			//! \brief Status, if changes shall be registered and logged.
			bool mActive;

			/*!
			 \brief Status, ob der Undoprozess aktiv ist, damit durch den Manager durchgeführte
			 Änderungen nicht wiederholt registriert werden.
			 */
			bool mUndoing;

			/*!
			 \brief Status, ob ein Bearbeitungsschritt geöffnet ist, wenn dies der Fall ist, dann kann
			 kein Undo oder Redo erfolgen.
			 */
			bool mOpen;

			/*!
			 \brief Der Undostack an Undooperationen.
			 Letzter Undoschritt = Oben
			 */
			UndoStep* mUndoStack;

			/*!
			 \brief Der Aktuelle Bearbeitungsschritt
			 */
			UndoStep* mCurrent;

			/*!
			 \brief Der Redostack an Redooperationen
			 Letzter Redoschritt = Oben
			 */
			UndoStep* mRedoStack;

			/*!
			 \brief Anzahl der Elemente auf dem Undo-Stack
			 */
			uint32 mUndoCount;

			/*!
			 \brief Anzahl der Elemente auf dem Redo-Stack
			 */
			uint32 mRedoCount;

			//! If a transaction is used, this indicates the level of transaction
			Integer mTransactionLevel;

			//! If a transaction is active, this is the content of the transaction.
			UndoStep* mTransaction;

			//! The transaction status
			VxfErrorStatus mTransactionStatus;
	};

}


#endif
