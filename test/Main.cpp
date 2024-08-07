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
   System::init("de.jameo.testsuite");
   System::log("Test Suite for VertexFusion ", jm::kLogInformation);

   TestVector* vec = new TestVector(argc, argv);

   //CORE
   vec->addTest(new StringTest());
   vec->addTest(new StringTokenizerTest());
   vec->addTest(new HashtableTest());
   vec->addTest(new LinkedListTest());
   vec->addTest(new MathTest());
   vec->addTest(new VertexTest());
   vec->addTest(new MatrixTest());
   vec->addTest(new GeometryTest());
   vec->addTest(new DeflateTest());
   vec->addTest(new UndoManagerTest());
   vec->addTest(new DateTest());
   vec->addTest(new DateTest());
   vec->addTest(new EditableObjectTest());

   Integer result = vec->execute();

   delete vec;

   System::quit();
   return result.Int32();
}
