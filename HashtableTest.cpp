//
//  HashtableTest.cpp
//  tornado
//
//  Created by Uwe Runtemund on 11.09.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "HashtableTest.h"
#include "core/Hashtable.h"
#include "core/Exception.h"

using namespace jm;

HashtableTest::HashtableTest(bool debug):Test(debug)
{
	SetName("Test Hashtable");
}

void HashtableTest::DoTest()
{

	//Hashtable
	Hashtable* ht = new Hashtable();
	ht->Put("test1",(void*) 1);
	ht->Put("test2",(void*) 2);
	ht->Put("test3",(void*) 3);
	ht->Put("test4",(void*) 4);
	ht->Put("test5",(void*) 5);
	TestEquals((int)(long)(ht->Get("test1")),1, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test2")),2, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test3")),3, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test4")),4, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test5")),5, "Hashtable fails");
	ht->Put("test6",(void*) 6);
	ht->Put("test7",(void*) 7);
	ht->Put("test8",(void*) 8);
	ht->Put("test9",(void*) 9);
	ht->Put("testA",(void*) 10);
	TestEquals((int)(long)(ht->Get("test1")),1, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test2")),2, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test3")),3, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test4")),4, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test5")),5, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test6")),6, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test7")),7, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test8")),8, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("test9")),9, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("testA")),10, "Hashtable fails");
	delete ht;
	
	//Neuer Test
	ht = new Hashtable();
	ht->Put("value2",(void*) 1);
	ht->Put("value3",(void*) 2);
	ht->Put("value5",(void*) 3);
	ht->Put("value6",(void*) 4);
	ht->Put("value11",(void*) 5);
	ht->Put("value15",(void*) 6);
	TestEquals((int)(long)(ht->Get("value2")),1, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("value3")),2, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("value5")),3, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("value6")),4, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("value11")),5, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("value15")),6, "Hashtable fails");
	
	//Clear
	ht->Clear();
	delete ht;

	
	ht = new Hashtable();
	ht->Put("value2",(void*) 1);
	ht->Put("value3",(void*) 2);
	ht->Put("value5",(void*) 3);
	ht->Remove("value5");
	TestEquals((int)(long)(ht->Get("value2")),1, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("value3")),2, "Hashtable fails");
	TestEquals((int)(long)(ht->Get("value5")),0, "Hashtable fails");
	delete ht;

}
