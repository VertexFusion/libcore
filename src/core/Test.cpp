////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Test.cpp
// Library:     Jameo Core Library
// Purpose:     Test Helper
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     07.10.2012
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

// Under macOS 10.9 namespaces added
Integer jm::gErrorCount;
Integer jm::gTestCount;
Integer jm::gTotalErrorCount;
Integer jm::gTotalTestCount;

Test::Test()
{}

Test::~Test()
{

}

void Test::SetErrorCode(const String& error)
{
   mError = error;
}

const String& Test::GetErrorCode() const
{
   return mError;
}

void Test::TestFail(const String& message)
{
   System::log(message, kLogError);
   jm::gTotalErrorCount++;
   jm::gTotalTestCount++;
   jm::gErrorCount++;
   jm::gTestCount++;
}

void Test::TestEquals(const double actual, const double expected, const String &failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(fabs(actual - expected) <= RESABS) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage + " '" + String::valueOf(actual) + "' '" + String::valueOf(expected) + "'", kLogError);
}

void Test::TestEquals(Integer actual, Integer expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == expected) return;

   String msg;
   msg << failmessage << " '" << actual << "' '" << expected << "'";
   System::log(msg, kLogError);

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
}

void Test::TestEquals(Integer actual, int32 expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == expected) return;

   String msg;
   msg << failmessage << " '" << actual << "' '" << expected << "'";
   System::log(msg, kLogError);

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
}

void Test::TestEquals(int64 actual, int64 expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == expected) return;
   System::log(failmessage + " '" + actual + "' '" + expected + "'", kLogError);

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
}

void Test::TestEquals(uint64 actual, uint64 expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == expected) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   String msg;
   msg << failmessage << " '" << actual << "' '" << expected << "'";
   System::log(msg, kLogError);
}

void Test::TestEquals(void* actual, void* expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == expected) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   String msg;
   msg << failmessage << " '" << (uint64)actual << "' '" << (uint64)expected << "'";
   System::log(msg, kLogError);
}

void Test::TestEquals(uint64 actual, int32 expected, const String& failmessage)
{
   TestEquals(actual, (uint64)expected, failmessage);
}

void Test::TestEquals(uint64 actual, uint32 expected, const String& failmessage)
{
   TestEquals(actual, (uint64)expected, failmessage);
}

void Test::TestEquals(int32 actual, int32 expected, const String& failmessage)
{
   TestEquals((int64)actual, (int64)expected, failmessage);
}

void Test::TestEquals(uint32 actual, uint32 expected, const String& failmessage)
{
   TestEquals((uint64)actual, (uint64)expected, failmessage);
}

void Test::TestEquals(uint32 actual, int32 expected, const String& failmessage)
{
   TestEquals((int64)actual, (int64)expected, failmessage);
}

void Test::TestEquals(int32 actual, uint32 expected, const String& failmessage)
{
   TestEquals((int64)actual, (int64)expected, failmessage);
}

void Test::TestEqualsIgnoreCase(const String& actual,
                                const String& expected,
                                const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(expected.equalsIgnoreCase(actual))return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage + " '" + actual + "' '" + expected + "'", kLogError);
}


void Test::TestEquals(const String& actual, const String& expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(expected.equals(actual)) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage + " '" + actual + "' '" + expected + "'", kLogError);
}

void Test::TestNull(void* actual, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == NULL) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage, kLogError);
}

void Test::TestNotNull(void* actual, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual != NULL) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage, kLogError);
}

void Test::TestTrue(bool actual, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == true) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage, kLogError);
}

void Test::TestFalse(bool actual, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == false) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage, kLogError);
}

void Test::TestUnexpectedException(const String& failmessage)
{
   TestFail(failmessage);
}

const String& Test::GetName() const
{
   return mName;
}

void Test::SetName(const String& name)
{
   mName = name;
}
