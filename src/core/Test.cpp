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

#include "PrecompiledCore.hpp"

using namespace jm;

// Under macOS 10.9 namespaces added
int64 jm::gErrorCount;
int64 jm::gTestCount;
int64 jm::gTotalErrorCount;
int64 jm::gTotalTestCount;

Test::Test()
{}

Test::~Test()
{

}

void Test::setErrorCode(const String& error)
{
   mError = error;
}

const String& Test::errorCode() const
{
   return mError;
}

void Test::testFail(const String& message)
{
   System::log(message, LogLevel::kError);
   jm::gTotalErrorCount++;
   jm::gTotalTestCount++;
   jm::gErrorCount++;
   jm::gTestCount++;
}

void Test::testEquals(const double actual, const double expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(fabs(actual - expected) <= RESABS) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage + " '" + String::valueOf(actual) + "' '" + String::valueOf(expected) + "'",
               LogLevel::kError);
}

void Test::testEquals(int64 actual, int64 expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == expected) return;

   String msg;
   msg << failmessage << " '" << actual << "' '" << expected << "'";
   System::log(msg, LogLevel::kError);

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
}

void Test::testEquals(int64 actual, int32 expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == expected) return;

   String msg;
   msg << failmessage << " '" << actual << "' '" << expected << "'";
   System::log(msg, LogLevel::kError);

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
}

void Test::testEquals(uint64 actual, uint64 expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == expected) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   String msg;
   msg << failmessage << " '" << actual << "' '" << expected << "'";
   System::log(msg, LogLevel::kError);
}

void Test::testEquals(void* actual, void* expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == expected) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   String msg;
   msg << failmessage << " '" << (uint64)actual << "' '" << (uint64)expected << "'";
   System::log(msg, LogLevel::kError);
}

void Test::testEquals(uint64 actual, int32 expected, const String& failmessage)
{
   testEquals(actual, (uint64)expected, failmessage);
}

void Test::testEquals(uint64 actual, uint32 expected, const String& failmessage)
{
   testEquals(actual, (uint64)expected, failmessage);
}

void Test::testEquals(int32 actual, int32 expected, const String& failmessage)
{
   testEquals((int64)actual, (int64)expected, failmessage);
}

void Test::testEquals(uint32 actual, uint32 expected, const String& failmessage)
{
   testEquals((uint64)actual, (uint64)expected, failmessage);
}

void Test::testEquals(uint32 actual, int32 expected, const String& failmessage)
{
   testEquals((int64)actual, (int64)expected, failmessage);
}

void Test::testEquals(int32 actual, uint32 expected, const String& failmessage)
{
   testEquals((int64)actual, (int64)expected, failmessage);
}

void Test::testEqualsIgnoreCase(const String& actual,
                                const String& expected,
                                const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(expected.equalsIgnoreCase(actual))return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage + " '" + actual + "' '" + expected + "'", LogLevel::kError);
}


void Test::testEquals(const String& actual, const String& expected, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(expected.equals(actual)) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage + " '" + actual + "' '" + expected + "'", LogLevel::kError);
}

void Test::testNull(void* actual, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == nullptr) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage, LogLevel::kError);
}

void Test::testNotNull(void* actual, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual != nullptr) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage, LogLevel::kError);
}

void Test::testTrue(bool actual, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == true) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage, LogLevel::kError);
}

void Test::testFalse(bool actual, const String& failmessage)
{
   jm::gTotalTestCount++;
   jm::gTestCount++;

   if(actual == false) return;

   jm::gTotalErrorCount++;
   jm::gErrorCount++;
   System::log(failmessage, LogLevel::kError);
}

void Test::testUnexpectedException(const String& failmessage)
{
   testFail(failmessage);
}

const String& Test::name() const
{
   return mName;
}

void Test::setName(const String& name)
{
   mName = name;
}
