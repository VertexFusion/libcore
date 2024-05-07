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
#include "core/EditableObjectTest.h"

using namespace jm;

int main(int argc, const char* argv[])
{
   System::Init("de.jameo.testsuite");
   System::Log("Test Suite for VertexFusion ", jm::kLogInformation);

   TestVector* vec = new TestVector(argc, argv);

   //CORE
   vec->AddTest(new StringTest());
   vec->AddTest(new StringTokenizerTest());
   vec->AddTest(new HashtableTest());
   vec->AddTest(new LinkedListTest());
   vec->AddTest(new MathTest());
   vec->AddTest(new VertexTest());
   vec->AddTest(new MatrixTest());
   vec->AddTest(new GeometryTest());
   vec->AddTest(new DeflateTest());
   vec->AddTest(new UndoManagerTest());
   vec->AddTest(new DateTest());
   vec->AddTest(new DateTest());
   vec->AddTest(new EditableObjectTest());

   Integer result = vec->Execute();

   delete vec;

   System::Quit();
   return result.Int32();
}
