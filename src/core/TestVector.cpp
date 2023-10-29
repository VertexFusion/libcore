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
}

TestVector::~TestVector()
{
	for(uint32 a = 0; a < tests.size(); a++)delete tests[a];
}

void TestVector::AddTest(Test* test)
{
	tests.push_back(test);
}

void TestVector::Execute()
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

	for(Integer a = 0; a < tests.size(); a++)
	{
		if(single < 0 || single == a)Testrun(tests[a]);
	}

	clock_t et = clock();

	std::cout<<jm::String::Format("Cycle finished! In total  %i tests, %i errors, duration %1.3f sec.",
	        jm::gTotalTestCount,
	        jm::gTotalErrorCount,
	        (double)(et - bt) / CLOCKS_PER_SEC)<<std::endl;
}

void TestVector::Testrun(Test* test)
{
	if(test == NULL)return;

	LogMessage(test->GetName());

	//	try
	//	{
	test->DoTest();
	/*	}
		catch(String e)
		{
			test->TestUnexpectedException(e);
		}
		catch(jm::Exception* e)
		{
			test->TestUnexpectedException(e->GetErrorMessage());
		}
		catch(char* e)
		{
			test->TestUnexpectedException(e);
		}
		catch(void* e)
		{
			test->TestUnexpectedException("Unbekannter Fehler");
		}*/

	std::cout<<jm::String::Format("Test finished! %i Tests, %i Errors.",
	        gTestCount,
	        gErrorCount)<<std::endl;

	gErrorCount = 0;
	gTestCount = 0;
}
