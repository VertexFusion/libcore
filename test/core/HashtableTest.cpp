//
//  HashtableTest.cpp
//  tornado
//
//  Created by Uwe Runtemund on 11.09.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "core/Hashtable.h"
#include "HashtableTest.h"

using namespace jm;

HashtableTest::HashtableTest(): Test()
{
   setName("Test Hashtable");
}

void HashtableTest::doTest()
{

   //Hashtable
   Hashtable* ht = new Hashtable();
   ht->put("test1", (void*) 1);
   ht->put("test2", (void*) 2);
   ht->put("test3", (void*) 3);
   ht->put("test4", (void*) 4);
   ht->put("test5", (void*) 5);
   testEquals((uint64)ht->get("test1"), 1, "Hashtable fails");
   testEquals((uint64)ht->get("test2"), 2, "Hashtable fails");
   testEquals((uint64)ht->get("test3"), 3, "Hashtable fails");
   testEquals((uint64)ht->get("test4"), 4, "Hashtable fails");
   testEquals((uint64)ht->get("test5"), 5, "Hashtable fails");
   ht->put("test6", (void*) 6);
   ht->put("test7", (void*) 7);
   ht->put("test8", (void*) 8);
   ht->put("test9", (void*) 9);
   ht->put("testA", (void*) 10);
   testEquals((uint64)ht->get("test1"), 1, "Hashtable fails");
   testEquals((uint64)ht->get("test2"), 2, "Hashtable fails");
   testEquals((uint64)ht->get("test3"), 3, "Hashtable fails");
   testEquals((uint64)ht->get("test4"), 4, "Hashtable fails");
   testEquals((uint64)ht->get("test5"), 5, "Hashtable fails");
   testEquals((uint64)ht->get("test6"), 6, "Hashtable fails");
   testEquals((uint64)ht->get("test7"), 7, "Hashtable fails");
   testEquals((uint64)ht->get("test8"), 8, "Hashtable fails");
   testEquals((uint64)ht->get("test9"), 9, "Hashtable fails");
   testEquals((uint64)ht->get("testA"), 10, "Hashtable fails");
   delete ht;

   //Neuer Test
   ht = new Hashtable();
   ht->put("value2", (void*) 1);
   ht->put("value3", (void*) 2);
   ht->put("value5", (void*) 3);
   ht->put("value6", (void*) 4);
   ht->put("value11", (void*) 5);
   ht->put("value15", (void*) 6);
   testEquals((uint64)ht->get("value2"), 1, "Hashtable fails");
   testEquals((uint64)ht->get("value3"), 2, "Hashtable fails");
   testEquals((uint64)ht->get("value5"), 3, "Hashtable fails");
   testEquals((uint64)ht->get("value6"), 4, "Hashtable fails");
   testEquals((uint64)ht->get("value11"), 5, "Hashtable fails");
   testEquals((uint64)ht->get("value15"), 6, "Hashtable fails");

   //Clear
   ht->clear();
   delete ht;


   ht = new Hashtable();
   ht->put("value2", (void*) 1);
   ht->put("value3", (void*) 2);
   ht->put("value5", (void*) 3);
   ht->remove("value5");
   testEquals((uint64)ht->get("value2"), 1, "Hashtable fails");
   testEquals((uint64)ht->get("value3"), 2, "Hashtable fails");
   testEquals((uint64)ht->get("value5"), 0, "Hashtable fails");
   delete ht;

}
