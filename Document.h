////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Document.h
// Library:     VertexFusion Library
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
#include "Properties.h"

namespace jm
{
	/*!
	 \brief This class represents the "model" in the MVC context. This class is also the ideal parent
	 class for all document-based applications, because basic functionalities that every user expects 
	 are already predefined here.In addition, development time is saved. These include:
	 - Undo and redo management
	 - File path, load and save
	 \ingroup core
	 */
	class DllExport Document: public Object
	{

		public:

			/*!
			 \brief Konstruktor
			 \discussion Im Konnstruktor hier wird bereits der UndoManager aktiviert. Dies hat zur Folge, dass z.B. der gesamte Einleseprozess
			 eines Dokumentes von der Festplatte als einzelner Undoschritt bereits "geloggt" ist. Dies ist aber zwingend notwendig, damit
			 beim Löschen von Objekten diese auf dem UndoStack erhalten bleiben sollen, weil z.B. die LinkedList die Pointer nicht
			 selbst, sondern nur über den UndoStack verwaltet.
			 */
			Document();

			/*!
			 \brief Destructor
			 */
			~Document();

			/*
			 *
			 * UNDO- UND REDO-MANAGEMENT
			 *
			 */

			/*!
			 \brief Gibt den Undomanager zurück, wenn er existiert.
			 */
			UndoManager* GetUndoManager();

			/*!
			 \brief Legt fest, ob ein Undomanager existiert oder nicht.
			 Wenn der Wert auf ja gesetzt wird und kein  Undomanager existiert, wird einer erzeugt.
			 Wenn bereits einer existiert, passiert nichts.
			 Wenn auf nein gesetzt wird, wird ein eventueller Undomanager freigegeben
			 */
			void SetUndoManager(bool status);

			/*!
			 \brief Gibt den Status zurück, ob ein UndoManager existiert
			 */
			bool HasUndoManager();

			/*!
			 \brief Gibt den Status zurück, ob das Dokument bearbeitet wurde.
			 \discussion Dieser Wert wird beim Speichert auf false gesetzt. Trotzdem kann der UndoManager Schritte zum
			 Rückggängig machen enthalten.
			 */
			bool IsDocumentChanged();

			/*!
			 \brief Legt den Status fest, ob die Datei verändert wurde. Das Setzen dieses Wertes hat Einfluss darauf, ob die Datei als geändert "markiert" ist.
			 Immer wenn die Datei gespeichert wird, wird dieser Wert auf false gesetzt.
			 In der Workbench wird dieser Wert automatisch gesetzt und muss nur manuell verändert werden, wenn man nicht die Workbench mit dem Undo-Mechanismus benuttz.
			 */
			void SetDocumentChanged(bool status);

			/*
			 *
			 * DATEIFPAD, LADEN UND SPEICHERN
			 *
			 */

			/*!
			 \brief Legt die Datei zu diesem Dokument fest
			 */
			void SetFile(File* file);

			/*!
			 \brief Gibt die Datei zu diesem Dokument zurück
			 */
			File* GetFile();

			/*!
			 \brief Speichert die Datei.
			 Diese Methode wird vom System aufgerufen, wenn die Datei gespeichert werden soll.
			 GetFile() liefert die Datei zurück.
			 Muss von abgeleiteten Klassen implementiert werden.
			 */
			virtual bool SaveDocument() = 0;

			/*!
			 \brief Lädt die Datei
			 */
			virtual bool LoadDocument() = 0;

			/*!
			 \brief Konstruktor erzeugt "leeres" Objekt.
			 Diese Methode wird alternativ zu LoadDocument aufgerufen,
			 wenn eine neue leere Datei erzeugt wird, anstatt eine zu laden.
			 \param props Einstellungen, welche ggf. Programmeinstellungen an die Datei übergeben.
			 */
			virtual bool InitNewDocument(Properties* props) = 0;

			/*!
			 \brief Liefert einen Iterator, der über Inhalte des Dokumentes iteriert. Übergeben wird
			 ein Referenzobjekt. Diese Methode ist typisch für die Schnellauswahl
			 */
			//virtual Iterator* GetIterator(EditableObject*) = 0;

		/*!
			\brief Legt fest, dass für dieses Objekt im nächsten Durchlauf die visuelle Repräsentation erneuert werden sollte.
			*/
		  virtual void Regenerate()
		  {
			  mRegenerate = true;
		  }

		  /*!
			\brief Diese Methode soll von der Regenerationsmethode aufgerufen werden nachdem die visuelle Repräsentation
			dieses Objektes aktualisiert wurde.
			*/
		  virtual void RegenerationDone()
		  {
			  mRegenerate = false;
		  }

		  /*!
			\brief Gibt den Regenerationsstatus zurück.
			*/
		  virtual bool ShouldRegenerate() const
		  {
			  return mRegenerate;
		  }

	  private:

		  /*!
			\brief Status, ob im nächten Durchlauf die visuelle Repräsentation erneuert werden sollte
			*/
		  bool mRegenerate;

			/*!
			 \brief Ein Undo-Manager, wenn er existiert. Ansonsten null. Standardwert ist NULL
			 */
			UndoManager* mUndoManager;

			/*!
			 \brief Der Dateipfad, an dem die Datei gespeichert ist. \todo URI???
			 */
			File* mFile;

			/*!
			 \brief Status, ob die Datei verändert wurde
			 */
			bool mChanged;


	};

}

#endif /* Document_h */
