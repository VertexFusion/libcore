////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Stack.h
// Library:     Jameo Core Library
// Purpose:     Collecting objects on a stack "First in - Last Out"
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
    \brief This class provides a stack container that processes data elements based on the "Last in - First out" principle.
    \details The Stack class allows elements to be added and removed from the top of the stack, maintaining the order in which they were added.
    \tparam T The type of data elements stored in the stack.
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
               prev = nullptr;
            }
         };

          //The top element on the stack
         StackElement* mTop;

          // The number of elements on the stack
         uint32 mCount;

      public:

          /*!
           \brief Constructor for the stack. Initializes all variables.
           */
         Stack()
         {
            mTop = nullptr;
            mCount = 0;
         };

          /*!
           \brief Destructor for the stack. Here all variables are deleted.
           */
         ~Stack()
         {
            clear();
         }

          /*!
           \brief This method returns true if the stack is not empty.
           */
         inline bool hasElements() const
         {
            return mTop != nullptr;
         };

          /*!
           \brief Removes and returns the top element from the stack.
           \return The top element of the stack.
           */
         inline T pop()
         {
            StackElement* pop = mTop;
            T ret = pop->data;
            mTop = pop->prev;
            delete pop;
            mCount--;
            return ret;
         };

          /*!
           \brief Returns the top element of the stack without removing it.
           \return The top element of the stack.
           */
         inline T& top() const
         {
            return mTop->data;
         };

          /*!
           \brief Returns the top element of the stack without removing it.
           \return The top element of the stack.
           */
         inline T* topRef()
         {
            return &mTop->data;
         };

          /*!
           \brief Returns the second top element of the stack without removing it.
           \return The second top element of the stack.
           */
          inline T top2()
          {
            if (mTop != nullptr && mTop->prev != nullptr) {
               return mTop->prev->data;
            }

            // Handle the case when there are not enough elements on the stack
            throw jm::Exception(Tr("Not enough elements on the stack"));
          };

          /*!
           \brief Returns the third element from the top of the stack without removing it.
           \return The third element from the top of the stack.
           */
          inline T top3()
          {
            if (mTop != nullptr && mTop->prev != nullptr && mTop->prev->prev != nullptr) {
               return mTop->prev->prev->data;
            }

            // Handle the case when there are not enough elements on the stack
            throw jm::Exception(Tr("Not enough elements on the stack"));
          };

          /*!
           \brief Adds an element to the stack.
           \param data The data to be added to the stack.
           */
         inline void push(T data)
         {
            StackElement* item = new StackElement();
            item->data = data;
            item->prev = mTop;
            mTop = item;
            mCount++;
         }

          /*!
           \brief Deletes all elements on the stack.
           */
         inline void clear()
         {
            while(hasElements())pop();
         };

          /*!
           \brief Returns the number of elements on the stack.
           \return The number of elements on the stack.
           */
         inline uint32 size() const
         {
            return mCount;
         }

          /*!
           \brief Reverses the order of the stack. The bottom element becomes the top.
           */
         inline void reverse()
         {
            StackElement* pop = nullptr;
            StackElement* push = nullptr;

            while(mTop != nullptr)
            {
               //Pop
               pop = mTop;
               mTop = pop->prev;

               //Push
               pop->prev = push;
               push = pop;
            }

            mTop = push;
         }
   };

}


#endif
