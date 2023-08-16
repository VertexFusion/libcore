//
//  LinkedListTest.cpp
//  tornado
//
//  Created by Uwe Runtemund on 10.10.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "LinkedListTest.h"
#include "core/LinkedList.h"
#include "core/Exception.h"

using namespace jm;

LinkedListTest::LinkedListTest(bool debug):Test(debug)
{
	SetName("Test LinkedList");
}

void LinkedListTest::DoTest()
{
	// Test ohne Undo-Manager
	
	Object o1;
	Object o2;
	Object o3;
	Object o4;
	Object o5;
	Object o6;

	LinkedList* l = new LinkedList();
	l->Add(&o1,NULL);
	l->Add(&o2,NULL);
	l->Add(&o3,NULL);
	l->Add(&o4,NULL);
	l->Add(&o5,NULL);
	
	Object* i;
	
	l->Rewind();
	TestEquals(l->HasNext(),true, "LinkedList fails (1a)");
	i=l->Next();
	TestEquals(i,&o1, "LinkedList fails (1b) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (2a)");
	i=l->Next();
	TestEquals(i,&o2, "LinkedList fails (2b) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (3a)");
	i=l->Next();
	TestEquals(i,&o3, "LinkedList fails (3b) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (4a)");
	i=l->Next();
	TestEquals(i,&o4, "LinkedList fails (4b) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (5a)");
	i=l->Next();
	TestEquals(i,&o5, "LinkedList fails (5b) ");
	
	TestEquals(l->HasNext(),false, "LinkedList fails (6)");
	
	l->Rewind();
	TestEquals(l->HasNext(),true, "LinkedList fails (7a)");
	i=l->Next();
	TestEquals(i,&o1, "LinkedList fails (7b) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (8a)");
	i=l->Next();
	TestEquals(i,&o2, "LinkedList fails (8b) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (9a)");
	i=l->Next();
	TestEquals(i,&o3, "LinkedList fails (9b) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (10a)");
	i=l->Next();
	TestEquals(i,&o4, "LinkedList fails (10b) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (11a)");
	i=l->Next();
	TestEquals(i,&o5, "LinkedList fails (11b) ");
	
	TestEquals(l->HasNext(),false, "LinkedList fails (12)");
	
	//Addbefore
	l->AddBefore(&o3, &o6, NULL);

	l->Rewind();
	TestEquals(l->HasNext(),true, "LinkedList fails (13a)");
	i=l->Next();
	TestEquals(i,&o1, "LinkedList fails (13b) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (13c)");
	i=l->Next();
	TestEquals(i,&o2, "LinkedList fails (13d) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (13e)");
	i=l->Next();
	TestEquals(i,&o6, "LinkedList fails (13f) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (13g)");
	i=l->Next();
	TestEquals(i,&o3, "LinkedList fails (13h) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (13i)");
	i=l->Next();
	TestEquals(i,&o4, "LinkedList fails (13j) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (13k)");
	i=l->Next();
	TestEquals(i,&o5, "LinkedList fails (13l) ");

	TestEquals(l->HasNext(),false, "LinkedList fails (13m)");

	//Remove
	l->Remove(&o6, NULL);

	l->Rewind();
	TestEquals(l->HasNext(),true, "LinkedList fails (13a)");
	i=l->Next();
	TestEquals(i,&o1, "LinkedList fails (13b) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (13c)");
	i=l->Next();
	TestEquals(i,&o2, "LinkedList fails (13d) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (13g)");
	i=l->Next();
	TestEquals(i,&o3, "LinkedList fails (13h) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (13i)");
	i=l->Next();
	TestEquals(i,&o4, "LinkedList fails (13j) ");
	
	TestEquals(l->HasNext(),true, "LinkedList fails (13k)");
	i=l->Next();
	TestEquals(i,&o5, "LinkedList fails (13l) ");
	
	TestEquals(l->HasNext(),false, "LinkedList fails (13m)");

	
	delete l;

	
}
