//
//  main.cpp
//  test
//
//  Created by Uwe Runtemund on 17.01.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

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

	bool debug = false;

	TestVector* vec = new TestVector(argc, argv);

	//CORE
	vec->AddTest( new StringTest( debug ) );
	vec->AddTest( new StringTokenizerTest( debug ) );
	vec->AddTest( new HashtableTest( debug ) );
	vec->AddTest( new LinkedListTest( debug ) );
	vec->AddTest( new MathTest( debug ) );
	vec->AddTest( new VertexTest( debug ) );
	vec->AddTest( new MatrixTest( debug ) );
	vec->AddTest( new GeometryTest( debug ) );
	vec->AddTest( new DeflateTest( debug ) );
	vec->AddTest( new UndoManagerTest( debug ) );
	vec->AddTest( new DateTest( debug ) );

	vec->Execute();

	delete vec;


	System::Quit();
	return 0;
}
