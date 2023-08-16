////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Stack.h
// Library:     VertexFusion Library
// Purpose:     Collecting ojects on a stack "First in - Last Out"
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     09.07.2015
//
// Copyright:   (c) 2015 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Stack_h
#define jm_Stack_h

#include "Types.h"

namespace jm
{

	/*!
	 \brief Diese Klasse stellt einen Stack-Container zur Verfügung,
	 der Datenelemente nach dem Prinzip "Last in - First out" verarbeitet
	 */
	template <class T>
	class Stack
	{
		private:
			struct StackElement
			{
				StackElement* prev;
				T data;

				StackElement()
				{
					prev = NULL;
				}
			};

			//Das oberste Element auf dem Stack
			StackElement* top;

			//Die Anzahl der Elemente auf dem Stack
			uint32 count;

		public:

			/*!
			 \brief Konstruktor für den Haufen. Hier werden alle Variablen initialisiert
			 */
			Stack()
			{
				top = NULL;
				count = 0;
			};

			/*!
			 \brief Destructor für den Haufen. Hier werden alle Variabeln gelöscht
			 */
			~Stack()
			{
				Clear();
			}

			/*!
			 \brief Diese Methode gibt wahr zurück, wenn der Stack nicht leer ist.
			 */
			inline bool HasElements()
			{
				return top != NULL;
			};

			/*!
			 \brief Holt das oberste Element vom Stack und gibt es zurück
			 */
			inline T Pop()
			{
				StackElement* pop = top;
				T ret = pop->data;
				top = pop->prev;
				delete pop;
				count--;
				return ret;
			};

			/*!
			 \brief Gibt das oberste Element vom Stack zurück, ohne es vom Stack zu löschen
			 */
			inline T Top()
			{
				return top->data;
			};

			/*!
			 \brief Gibt das oberste Element vom Stack zurück, ohne es vom Stack zu löschen
			 */
			inline T* TopRef()
			{
				return &top->data;
			};

			/*!
			 \brief Gibt das zweitoberste Element vom Stack zurück, ohne es vom Stack zu löschen
			 */
			inline T Top2()
			{
				return top->prev->data;
			};

			/*!
			 \brief Gibt das drittoberste Element vom Stack zurück, ohne es vom Stack zu löschen
			 */
			inline T Top3()
			{
				return top->prev->prev->data;
			};

			/*!
			 \brief Fügt ein Element auf dem Stack hinzu.
			 */
			inline void Push(T data)
			{
				StackElement* item = new StackElement();
				item->data = data;
				item->prev = top;
				top = item;
				count++;
			}

			/*!
			 \brief Löscht alle Elemente auf dem Stack
			 */
			inline void Clear()
			{
				while(HasElements())Pop();
			};

			/*!
			 \brief Gibt die Anzahl der Elemente auf dem Stack zurück
			 */
			inline uint32 Size()
			{
				return count;
			}

			/*!
			 \brief Kehr die Reihenfolge des Stacks um. Das unterste Element ist nun das oberste
			 */
			inline void Reverse()
			{
				StackElement* pop = NULL;
				StackElement* push = NULL;

				while(top != NULL)
				{
					//Pop
					pop = top;
					top = pop->prev;

					//Push
					pop->prev = push;
					push = pop;
				}

				top = push;
			}
	};

}


#endif
