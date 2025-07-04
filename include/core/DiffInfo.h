////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        DiffInfo.h
// Library:     Jameo Core Library
// Purpose:     Diff Algorithm
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     17.12.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_DiffInfo
#define jm_DiffInfo

#include "Object.h"
#include "Vertex2.h"
#include "Vertex3.h"
#include "DiffTypes.h"

namespace jm
{

   /*!
    \brief This class provides command line information about what changes have taken place and
    writes them to the console.
    \ingroup diff
    */
   class DllExport DiffInfo
   {
      public:

         /*!
          \brief Default constructor.
          */
         DiffInfo() = default;

         /*!
          \brief Copy constructor.
          \param another The DiffInfo object to be copied.
          */
         DiffInfo(const DiffInfo& another);

         /*!
          \brief This method writes the diff information of the two objects to the command line.
          \param operation The diff operation performed.
          \param obj1 Pointer to the first object.
          \param obj2 Pointer to the second object.
          */
         void print(DiffOperation operation, Object* obj1, Object* obj2);

         /*
         	void Print(int obj1, int obj2,vxf::String label);
         	void Print(unsigned int obj1,unsigned int obj2,vxf::String label);*/
         static void print(DiffOperation operation,
                           int32 obj1, int32 obj2, const String& label);
         static void print(DiffOperation operation,
                           int64 obj1, int64 obj2, const String& label);
         static void print(DiffOperation operation,
                           uint32 obj1, uint32 obj2, const String& label);
         static void print(DiffOperation operation,
                           uint64 obj1, uint64 obj2, const String& label);
         static void print(DiffOperation operation,
                           size_t obj1, size_t obj2, const String& label);

         static void print(DiffOperation operation,
                           double obj1, double obj2, const String& label);

         static void print(DiffOperation operation,
                           const String& obj1, const String& obj2, const String& label);

         static void printIgnoreCase(DiffOperation operation,
                                     const String& obj1, const String& obj2, const String& label);// Ignore Case

         //			static void Print(DiffOperation operation,
         //			                  const dwg::Color &obj1, const dwg::Color &obj2, const String &label);

         static void print(DiffOperation operation,
                           const Vertex2& obj1, const Vertex2& obj2, const String& label);

         static void print(DiffOperation operation,
                           const Vertex3& obj1, const Vertex3& obj2, const String& label);

         //			static void Print(DiffOperation operation,
         //			                  const dwg::Handle& obj1, const dwg::Handle& obj2, const String& label);
         /*
         				/ /Objekte
         				void Print(dxf::DwgAppId* obj1, dxf::DwgAppId* obj2);
         				void Print(dxf::Arc* obj1, dxf::Arc* obj2);
         				void Print(dxf::DwgBlock* obj1, dxf::DwgBlock* obj2);
         				void Print(dxf::DwgBlockRecord* obj1, dxf::DwgBlockRecord* obj2);
         				void Print(dxf::DwgCircle* obj1, dxf::DwgCircle* obj2);
         				void Print(dxf::Class* obj1, dxf::Class* obj2);
         				void Print(dxf::Dictionary* obj1, dxf::Dictionary* obj2);
         				void Print(dxf::DictionaryVar* obj1, dxf::DictionaryVar* obj2);
         				void Print(dxf::Dimension* obj1, dxf::Dimension* obj2);
         				void Print(dxf::DimStyle* obj1, dxf::DimStyle* obj2);
         				void Print(dxf::DwgEllipse* obj1, dxf::DwgEllipse* obj2);
         				void Print(dxf::DwgEntity* obj1, dxf::DwgEntity* obj2);
         				void Print(dxf::DwgFace3d* obj1, dxf::DwgFace3d* obj2);
         				void Print(dxf::Insert* obj1, dxf::Insert* obj2);
         				void Print(dxf::Layer* obj1, dxf::Layer* obj2);
         				void Print(dxf::Line* obj1, dxf::Line* obj2);
         				void Print(dxf::LineType* obj1,dxf::LineType* obj2);
         				void Print(dxf::Material* obj1, dxf::Material* obj2);
         				void Print(dxf::MultiText* obj1, dxf::MultiText* obj2);
         				void Print(dxf::Point* obj1, dxf::Point* obj2);
         				void Print(dxf::Polyline* obj1, dxf::Polyline* obj2);
         				void Print(dxf::Scale* obj1, dxf::Scale* obj2);*/
         //			void Print(dwg::Header* obj1, dwg::Header* obj2);
         /*				void Print(dxf::Style* obj1, dxf::Style* obj2);
         				void Print(dxf::Text* obj1, dxf::Text* obj2);
         				void Print(dxf::DwgTrace* obj1, dxf::DwgTrace* obj2);
         				void Print(dxf::DwgVertex* obj1, dxf::DwgVertex* obj2);
         				void Print(dxf::DwgViewport* obj1, dxf::DwgViewport* obj2);
         				void Print(dxf::DwgVPort* obj1, dxf::DwgVPort* obj2);
         				void Print(dxf::DwgXRecord* obj1, dxf::DwgXRecord* obj2);*/



      private:

         /*!
          \brief The current operation, as some Print methods require this to output the correct information.
          */
         DiffOperation mOperation;

   };

}
#endif
