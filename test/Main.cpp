//
//  main.cpp
//  test
//
//  Created by Uwe Runtemund on 17.01.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//
/*
#include "core/Core.h"

#include "core/GeometryTest.h"
#include "core/HashtableTest.h"
#include "core/LinkedListTest.h"
#include "core/MathTest.h"
#include "core/StringTest.h"
#include "core/VertexTest.h"
#include "core/StringTokenizerTest.h"
#include "core/MatrixTest.h"
#include "core/DeflateTest.h"
#include "core/UndoManagerTest.h"
#include "core/DateTest.h"

using namespace jm;

int main( int argc, const char* argv[] )
{
	System::Init();
	System::Log( "Test Suite for VertexFusion " , jm::kLogInformation );

	TestVector* vec = new TestVector(argc, argv);

	//CORE
	vec->AddTest( new StringTest() );
	vec->AddTest( new StringTokenizerTest() );
	vec->AddTest( new HashtableTest() );
	vec->AddTest( new LinkedListTest() );
	vec->AddTest( new MathTest() );
	vec->AddTest( new VertexTest() );
	vec->AddTest( new MatrixTest() );
	vec->AddTest( new GeometryTest() );
	vec->AddTest( new DeflateTest() );
	vec->AddTest( new UndoManagerTest() );
	vec->AddTest( new DateTest() );

	Integer result = vec->Execute();

	delete vec;

	System::Quit();
	return result.Int32();
}
*/

#include "core/Core.h"

// Example test class to show simple test anatomy.
class ExampleTest : public jm::Test
{
public:

	// Constructor
	ExampleTest() :Test()
	{
		SetName("Example Test");
	};

	// Mandatory overriden test method. The heart of the test!
	void DoTest() override
	{
		int32 a = 2;
		int32 b = 5;
		TestEquals(a, b, "a is not b");
		a = 5;
		TestEquals(a, b, "a is not b");
	};
};

// Entry methof of test application
int main(int argc, const char* argv[])
{
	// Init Jameo System
	jm::System::Init();
	jm::System::Log("Example Test Suite", jm::kLogInformation);

	// Init test vector
	jm::TestVector* vec = new jm::TestVector(argc, argv);
	vec->AddTest(new ExampleTest());

	// Execute test vector
	int32 result = vec->Execute().Int32();

	// Clean up
	delete vec;
	jm::System::Quit();

	// Return the number of errors to help calling scripts
	return result;
}
