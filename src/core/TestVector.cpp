////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        TestVector.cpp
// Library:     Jameo Core Library
// Purpose:     Test Helper
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     03.11.2012
//
// Copyright:   (c) 2012 Jameo Software, Germany. https://jameo.de
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

TestVector::TestVector(int argc, const char * argv[])
{
   if(argc >= 2)
   {
      arg = argv[1];
   }
   tests = new std::vector<Test*>();
}

TestVector::~TestVector()
{
   for(uint32 a = 0; a < tests->size(); a++)delete tests->at(a);
   delete tests;
}

void TestVector::AddTest(Test* test)
{
   tests->push_back(test);
}

Integer TestVector::Execute()
{
   jm::gTotalTestCount = 0;
   jm::gTotalErrorCount = 0;

   clock_t bt = clock();

   Integer single = -1;

   if(arg.Length() > 0)
   {
      try
      {
         single = Integer::ValueOf(arg);
      }
      catch(jm::Exception* e)
      {
         delete e;
      }
   }

   for(Integer a = 0; a < tests->size(); a++)
   {
      if(single < 0 || single == a)Testrun(tests->at(a));
   }

   clock_t et = clock();

   std::cout << std::endl << Tr("Cycle finished! In total:") << std::endl;
   std::cout << jm::String::Format(Tr("Tests:    %i"), jm::gTotalTestCount) << std::endl;

   std::cout <<
             ((jm::gTotalErrorCount > 0) ? kTxtRed : kTxtGreen)
             << jm::String::Format(Tr("Errors:   %i"), jm::gTotalErrorCount)
             << kTxtReset << std::endl;

   std::cout <<
             jm::String::Format(Tr("Duration: %1.3f sec"), (double)(et - bt) / CLOCKS_PER_SEC)
             << std::endl;

   return gTotalErrorCount;
}

void TestVector::Testrun(Test* test)
{
   if(test == NULL)return;

   System::Log(jm::String::Format(Tr("Execute %s..."), String::Ref(test->GetName())), kLogInformation);

   try
   {
      test->DoTest();
   }
   catch(jm::Exception* e)
   {
      e->PrintStackTrace();

      test->TestUnexpectedException(e->GetErrorMessage());

      delete e;
   }

   System::Log(jm::String::Format(Tr("Test finished! %i Tests, %i Errors."),
                                  gTestCount,
                                  gErrorCount), kLogInformation);

   gErrorCount = 0;
   gTestCount = 0;
}
