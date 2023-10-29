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

// Unter macOS 10.9 Namespace ergänzt
int32 jm::gErrorCount;
int32 jm::gTestCount;
int32 jm::gTotalErrorCount;
int32 jm::gTotalTestCount;


void Test::SetErrorCode(String _error)
{
	error = _error;
}

String Test::GetErrorCode()
{
	return error;
}

void Test::TestFail(String message)
{
	LogMessage(message);
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
	LogMessage(failmessage + " '" + String::ValueOf(actual) + "' '" + String::ValueOf(expected) + "'");
}

void Test::TestEquals(Integer actual, Integer expected, String failmessage)
{
	jm::gTotalTestCount++;
	jm::gTestCount++;

	if (actual == expected) return;

	String msg = failmessage << " '" << actual << "' '" << expected << "'";
	LogMessage(msg);

	jm::gTotalErrorCount++;
	jm::gErrorCount++;
}

void Test::TestEquals(Integer actual, int32 expected, String failmessage)
{
	jm::gTotalTestCount++;
	jm::gTestCount++;

	if (actual == expected) return;

	String msg = failmessage << " '" << actual << "' '" << expected << "'";
	LogMessage(msg);

	jm::gTotalErrorCount++;
	jm::gErrorCount++;
}

void Test::TestEquals(int64 actual, int64 expected, String failmessage)
{
	jm::gTotalTestCount++;
	jm::gTestCount++;

	if(actual == expected) return;
	LogMessage(failmessage + " '" + actual + "' '" + expected + "'");

	jm::gTotalErrorCount++;
	jm::gErrorCount++;
}

void Test::TestEquals(uint64 actual, uint64 expected, String failmessage)
{
	jm::gTotalTestCount++;
	jm::gTestCount++;

	if(actual == expected) return;

	jm::gTotalErrorCount++;
	jm::gErrorCount++;
	String msg = failmessage << " '" << actual << "' '" << expected << "'";
	LogMessage(msg);
}

void Test::TestEquals(void* actual, void* expected, String failmessage)
{
	jm::gTotalTestCount++;
	jm::gTestCount++;

	if(actual == expected) return;

	jm::gTotalErrorCount++;
	jm::gErrorCount++;
	String msg = failmessage << " '" << (uint64)actual << "' '" << (uint64)expected << "'";
	LogMessage(msg);
}

void Test::TestEquals(uint64 actual, int32 expected, String failmessage)
{
	TestEquals(actual, (uint64)expected, failmessage);
}

void Test::TestEquals(uint64 actual, uint32 expected, String failmessage)
{
	TestEquals(actual, (uint64)expected, failmessage);
}

void Test::TestEquals(int32 actual, int32 expected, String failmessage)
{
	TestEquals((int64)actual, (int64)expected, failmessage);
}

void Test::TestEquals(uint32 actual, uint32 expected, String failmessage)
{
	TestEquals((uint64)actual, (uint64)expected, failmessage);
}

void Test::TestEquals(uint32 actual, int32 expected, String failmessage)
{
	TestEquals((int64)actual, (int64)expected, failmessage);
}

void Test::TestEquals(int32 actual, uint32 expected, String failmessage)
{
	TestEquals((int64)actual, (int64)expected, failmessage);
}

void Test::TestEqualsIgnoreCase(String actual, String expected, String failmessage)
{
	jm::gTotalTestCount++;
	jm::gTestCount++;

	if(expected.EqualsIgnoreCase(actual))return;

	jm::gTotalErrorCount++;
	jm::gErrorCount++;
	LogMessage(failmessage + " '" + actual + "' '" + expected + "'");
}


void Test::TestEquals(String actual, String expected, String failmessage)
{
	jm::gTotalTestCount++;
	jm::gTestCount++;

	if(expected.Equals(actual)) return;

	jm::gTotalErrorCount++;
	jm::gErrorCount++;
	LogMessage(failmessage + " '" + actual + "' '" + expected + "'");
}

void Test::TestNull(void* actual, String failmessage)
{
	jm::gTotalTestCount++;
	jm::gTestCount++;

	if(actual == NULL) return;

	jm::gTotalErrorCount++;
	jm::gErrorCount++;
	LogMessage(failmessage);
}

void Test::TestNotNull(void* actual, String failmessage)
{
	jm::gTotalTestCount++;
	jm::gTestCount++;

	if(actual != NULL) return;

	jm::gTotalErrorCount++;
	jm::gErrorCount++;
	LogMessage(failmessage);
}

void Test::TestTrue(bool actual, String failmessage)
{
	jm::gTotalTestCount++;
	jm::gTestCount++;

	if(actual == true) return;

	jm::gTotalErrorCount++;
	jm::gErrorCount++;
	LogMessage(failmessage);
}

void Test::TestFalse(bool actual, String failmessage)
{
	jm::gTotalTestCount++;
	jm::gTestCount++;

	if(actual == false) return;

	jm::gTotalErrorCount++;
	jm::gErrorCount++;
	LogMessage(failmessage);
}

void Test::TestUnexpectedException(String failmessage)
{
	TestFail(failmessage);
}

String Test::GetName()
{
	return name;
}

void Test::SetName(String name_)
{
	name = name_;
}

Test::Test(bool _debug)
{
	debug = _debug;
}

Test::~Test()
{

}


void jm::LogMessage(String message)
{
	std::cout << message << std::endl ;
}
