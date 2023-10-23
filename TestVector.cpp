//
//  testvector.cpp
//  jameo
//
//  Created by Uwe Runtemund on 03.11.12.
//  Copyright 2012 Jameo Software. All rights reserved.
//

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

	int32 single = -1;

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

	for(uint32 a = 0; a < tests.size(); a++)
	{
		if(single < 0 || single == (int32)a)Testrun(tests[a]);
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
