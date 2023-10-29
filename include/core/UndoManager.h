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

namespace jm
{
	class Document;
	
	/*!
	 \brief Diese Klasse repräsentiert den Manager für Rückgängig-Operationen.
	 Es werden Bearbeitungsschritte an einer Datei direkt in der Datei gespeichert.
	 Dies ermöglicht unabhängig vom Bearbeitungsverfahren Bearbeitungsschritte an der Datei
	 rückgängig zu machen.

	 Allerdings sind Überlegungen notwendig, in welcher Form Bearbeitungsschritte atomisiert werden.

	 - Bei manueller Bearbeitung sollte jeder kleinteilige Bearbeitungsschritt rückgängig machbar
	   sein.
	 - Bei Skripten (JS und C++) ist es sinnvoll, das das gesamte Skript ein Rückgängigschritt ist.

	 Daher gibt es folgendes Verfahren:

	 Um den aktuellen Bearbeitungsschritt abzuschließen muss die Methode Next() ausgeführt werden.
	 Der Programmierer muss das manuell machen. Ansonsten werden alle Änderungen in einem Schritt
	 gespeichert.

	 Der Undomanager ist standardmäßig deaktiviert.

	 */
	class DllExport UndoManager: public Object
	{
		public:

			/*!
			 \brief Konstruktor
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
			bool IsActive();

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

		private:

			/*!
			 \brief Das zugehörige Dokument
			 */
			jm::Document* mDocument;

			/*!
			 \brief Status, ob Änderungen an der Datei verfolgt werden sollen, oder nicht
			 */
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

	};

}


#endif
