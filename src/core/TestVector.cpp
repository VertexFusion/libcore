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

#include "PrecompiledCore.hpp"

using namespace jm;

TestVector::TestVector(int argc, const char* argv[])
{
   if(argc >= 2)
   {
      mArg = argv[1];
   }
   mTests = new std::vector<Test*>();
}

TestVector::~TestVector()
{
   for(jm::Test* test: *mTests)
   {
      delete test;
   }
   delete mTests;
}

void TestVector::addTest(Test* test)
{
   mTests->push_back(test);
}

size_t TestVector::execute()
{
   jm::gTotalTestCount = 0;
   jm::gTotalErrorCount = 0;

   clock_t bt = clock();

   size_t single = npos;

   if(mArg.size() > 0)
   {
      try
      {
         single = mArg.toSize();
      }
      catch(const jm::Exception& e)
      {}
   }

   for(size_t a = 0; a < mTests->size(); a++)
   {
      if(single == npos || single == a)testrun(mTests->at(a));
   }

   clock_t et = clock();

   std::cout << std::endl << Tr("Cycle finished! In total:") << std::endl;
   std::cout << Tr("Tests:    %1").arg(jm::gTotalTestCount) << std::endl;

   std::cout <<
             ((jm::gTotalErrorCount > 0) ? kTxtRed : kTxtGreen)
             << Tr("Errors:   %1").arg(jm::gTotalErrorCount)
             << kTxtReset << std::endl;

   std::cout <<
             Tr("Duration: %1 sec").arg(((double)(et - bt) / CLOCKS_PER_SEC), 1, 3)
             << std::endl;

   return gTotalErrorCount;
}

void TestVector::testrun(Test* test) const
{
   if(test == nullptr)return;

   System::log(Tr("Execute %1...").arg(test->name()), LogLevel::kInformation);

   try
   {
      test->doTest();
   }
   catch(jm::Exception& e)
   {
      e.printStackTrace();
      test->testUnexpectedException(e.errorMessage());
   }

   System::log(Tr("Test finished! %1 Tests, %2 Errors.")
               .arg(gTestCount)
               .arg(gErrorCount),
               LogLevel::kInformation);

   gErrorCount = 0;
   gTestCount = 0;
}
