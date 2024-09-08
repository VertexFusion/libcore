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

#include "Precompiled.hpp"

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
   for(uint32 a = 0; a < mTests->size(); a++)delete mTests->at(a);
   delete mTests;
}

void TestVector::addTest(Test* test)
{
   mTests->push_back(test);
}

int64 TestVector::execute()
{
   jm::gTotalTestCount = 0;
   jm::gTotalErrorCount = 0;

   clock_t bt = clock();

   int64 single = -1;

   if(mArg.size() > 0)
   {
      try
      {
         single = mArg.toInt();
      }
      catch(jm::Exception& e)
      {}
   }

   for(int64 a = 0; a < static_cast<int64>(mTests->size()); a++)
   {
      if(single < 0 || single == a)testrun(mTests->at(a));
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

void TestVector::testrun(Test* test)
{
   if(test == nullptr)return;

   System::log(Tr("Execute %1...").arg(test->name()), kLogInformation);

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
               kLogInformation);

   gErrorCount = 0;
   gTestCount = 0;
}
