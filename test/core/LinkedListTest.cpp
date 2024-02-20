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

LinkedListTest::LinkedListTest(): Test()
{
   SetName("Test LinkedList");
}

void LinkedListTest::DoTest()
{
   DoTest1();
   DoTest2(false);
   DoTest2(true);
   DoTest3(false);
   DoTest3(true);
}

void LinkedListTest::DoTest1()
{
   // Test ohne Undo-Manager

   Object o1;
   Object o2;
   Object o3;
   Object o4;
   Object o5;
   Object o6;

   LinkedList* l = new LinkedList(this);
   l->Add(&o1, NULL);
   l->Add(&o2, NULL);
   l->Add(&o3, NULL);
   l->Add(&o4, NULL);
   l->Add(&o5, NULL);

   Object* i;

   l->Rewind();
   TestEquals(l->HasNext(), true, "LinkedList fails (1a)");
   i = l->Next();
   TestEquals(i, &o1, "LinkedList fails (1b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (2a)");
   i = l->Next();
   TestEquals(i, &o2, "LinkedList fails (2b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (3a)");
   i = l->Next();
   TestEquals(i, &o3, "LinkedList fails (3b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (4a)");
   i = l->Next();
   TestEquals(i, &o4, "LinkedList fails (4b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (5a)");
   i = l->Next();
   TestEquals(i, &o5, "LinkedList fails (5b) ");

   TestEquals(l->HasNext(), false, "LinkedList fails (6)");

   l->Rewind();
   TestEquals(l->HasNext(), true, "LinkedList fails (7a)");
   i = l->Next();
   TestEquals(i, &o1, "LinkedList fails (7b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (8a)");
   i = l->Next();
   TestEquals(i, &o2, "LinkedList fails (8b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (9a)");
   i = l->Next();
   TestEquals(i, &o3, "LinkedList fails (9b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (10a)");
   i = l->Next();
   TestEquals(i, &o4, "LinkedList fails (10b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (11a)");
   i = l->Next();
   TestEquals(i, &o5, "LinkedList fails (11b) ");

   TestEquals(l->HasNext(), false, "LinkedList fails (12)");

   //Addbefore
   l->AddBefore(&o3, &o6, NULL);

   l->Rewind();
   TestEquals(l->HasNext(), true, "LinkedList fails (13a)");
   i = l->Next();
   TestEquals(i, &o1, "LinkedList fails (13b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13c)");
   i = l->Next();
   TestEquals(i, &o2, "LinkedList fails (13d) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13e)");
   i = l->Next();
   TestEquals(i, &o6, "LinkedList fails (13f) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13g)");
   i = l->Next();
   TestEquals(i, &o3, "LinkedList fails (13h) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13i)");
   i = l->Next();
   TestEquals(i, &o4, "LinkedList fails (13j) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13k)");
   i = l->Next();
   TestEquals(i, &o5, "LinkedList fails (13l) ");

   TestEquals(l->HasNext(), false, "LinkedList fails (13m)");

   //Remove
   l->Remove(&o6, NULL);

   l->Rewind();
   TestEquals(l->HasNext(), true, "LinkedList fails (13a)");
   i = l->Next();
   TestEquals(i, &o1, "LinkedList fails (13b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13c)");
   i = l->Next();
   TestEquals(i, &o2, "LinkedList fails (13d) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13g)");
   i = l->Next();
   TestEquals(i, &o3, "LinkedList fails (13h) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13i)");
   i = l->Next();
   TestEquals(i, &o4, "LinkedList fails (13j) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13k)");
   i = l->Next();
   TestEquals(i, &o5, "LinkedList fails (13l) ");

   TestEquals(l->HasNext(), false, "LinkedList fails (13m)");

   delete l;
}


void LinkedListTest::DoTest2(bool active)
{
   // Test mit Undo-Manager
   UndoManager* um = new UndoManager();
   um->SetActive(active);

   Object o1;
   Object o2;
   Object o3;
   Object o4;
   Object o5;
   Object o6;

   LinkedList* l = new LinkedList(this);
   l->Add(&o1, um);
   l->Add(&o2, um);
   l->Add(&o3, um);
   l->Add(&o4, um);
   l->Add(&o5, um);

   Object* i;

   l->Rewind();
   TestEquals(l->HasNext(), true, "LinkedList fails (1a)");
   i = l->Next();
   TestEquals(i, &o1, "LinkedList fails (1b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (2a)");
   i = l->Next();
   TestEquals(i, &o2, "LinkedList fails (2b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (3a)");
   i = l->Next();
   TestEquals(i, &o3, "LinkedList fails (3b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (4a)");
   i = l->Next();
   TestEquals(i, &o4, "LinkedList fails (4b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (5a)");
   i = l->Next();
   TestEquals(i, &o5, "LinkedList fails (5b) ");

   TestEquals(l->HasNext(), false, "LinkedList fails (6)");

   l->Rewind();
   TestEquals(l->HasNext(), true, "LinkedList fails (7a)");
   i = l->Next();
   TestEquals(i, &o1, "LinkedList fails (7b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (8a)");
   i = l->Next();
   TestEquals(i, &o2, "LinkedList fails (8b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (9a)");
   i = l->Next();
   TestEquals(i, &o3, "LinkedList fails (9b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (10a)");
   i = l->Next();
   TestEquals(i, &o4, "LinkedList fails (10b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (11a)");
   i = l->Next();
   TestEquals(i, &o5, "LinkedList fails (11b) ");

   TestEquals(l->HasNext(), false, "LinkedList fails (12)");

   //Addbefore
   l->AddBefore(&o3, &o6, um);

   l->Rewind();
   TestEquals(l->HasNext(), true, "LinkedList fails (13a)");
   i = l->Next();
   TestEquals(i, &o1, "LinkedList fails (13b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13c)");
   i = l->Next();
   TestEquals(i, &o2, "LinkedList fails (13d) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13e)");
   i = l->Next();
   TestEquals(i, &o6, "LinkedList fails (13f) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13g)");
   i = l->Next();
   TestEquals(i, &o3, "LinkedList fails (13h) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13i)");
   i = l->Next();
   TestEquals(i, &o4, "LinkedList fails (13j) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13k)");
   i = l->Next();
   TestEquals(i, &o5, "LinkedList fails (13l) ");

   TestEquals(l->HasNext(), false, "LinkedList fails (13m)");

   //Remove
   l->Remove(&o6, um);

   l->Rewind();
   TestEquals(l->HasNext(), true, "LinkedList fails (13a)");
   i = l->Next();
   TestEquals(i, &o1, "LinkedList fails (13b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13c)");
   i = l->Next();
   TestEquals(i, &o2, "LinkedList fails (13d) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13g)");
   i = l->Next();
   TestEquals(i, &o3, "LinkedList fails (13h) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13i)");
   i = l->Next();
   TestEquals(i, &o4, "LinkedList fails (13j) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (13k)");
   i = l->Next();
   TestEquals(i, &o5, "LinkedList fails (13l) ");

   TestEquals(l->HasNext(), false, "LinkedList fails (13m)");

   um->ClearStacks();
   l->Release();
   delete um;

}

void LinkedListTest::DoTest3(bool active)
{
   // Test mit Undo-Manager
   UndoManager* um = new UndoManager();
   um->SetActive(active);

   Object o1;
   Object o2;
   Object o3;
   Object o4;
   Object o5;
   Object o6;

   LinkedList* l = new LinkedList(this);

   l->Add(&o1, um);
   l->Add(&o2, um);
   l->Add(&o3, um);
   l->Add(&o4, um);
   l->Add(&o5, um);
   um->Close();
   Object* i;

   l->Rewind();
   TestEquals(l->HasNext(), true, "LinkedList fails (1a)");
   i = l->Next();
   TestEquals(i, &o1, "LinkedList fails (1b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (2a)");
   i = l->Next();
   TestEquals(i, &o2, "LinkedList fails (2b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (3a)");
   i = l->Next();
   TestEquals(i, &o3, "LinkedList fails (3b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (4a)");
   i = l->Next();
   TestEquals(i, &o4, "LinkedList fails (4b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (5a)");
   i = l->Next();
   TestEquals(i, &o5, "LinkedList fails (5b) ");

   TestEquals(l->HasNext(), false, "LinkedList fails (6)");

   l->Rewind();
   TestEquals(l->HasNext(), true, "LinkedList fails (7a)");
   i = l->Next();
   TestEquals(i, &o1, "LinkedList fails (7b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (8a)");
   i = l->Next();
   TestEquals(i, &o2, "LinkedList fails (8b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (9a)");
   i = l->Next();
   TestEquals(i, &o3, "LinkedList fails (9b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (10a)");
   i = l->Next();
   TestEquals(i, &o4, "LinkedList fails (10b) ");

   TestEquals(l->HasNext(), true, "LinkedList fails (11a)");
   i = l->Next();
   TestEquals(i, &o5, "LinkedList fails (11b) ");

   TestEquals(l->HasNext(), false, "LinkedList fails (12)");

   l->Clear(um);
   um->Close();
   TestEquals(l->Size(), 0, "LinkedList fails (13)");

   if(active)// Next test only works with enabled undo manager
   {
      um->Undo();
      TestEquals(l->Size(), 5, "LinkedList fails (14)");

      l->Rewind();
      TestEquals(l->HasNext(), true, "LinkedList fails (15a)");
      i = l->Next();
      TestEquals(i, &o1, "LinkedList fails (15b) ");

      TestEquals(l->HasNext(), true, "LinkedList fails (16a)");
      i = l->Next();
      TestEquals(i, &o2, "LinkedList fails (16b) ");

      TestEquals(l->HasNext(), true, "LinkedList fails (17a)");
      i = l->Next();
      TestEquals(i, &o3, "LinkedList fails (17b) ");

      TestEquals(l->HasNext(), true, "LinkedList fails (18a)");
      i = l->Next();
      TestEquals(i, &o4, "LinkedList fails (18b) ");

      TestEquals(l->HasNext(), true, "LinkedList fails (19a)");
      i = l->Next();
      TestEquals(i, &o5, "LinkedList fails (19b) ");

      TestEquals(l->HasNext(), false, "LinkedList fails (20)");

      l->Clear(um);
      um->Close();
   }
   TestEquals(l->Size(), 0, "LinkedList fails (21)");

   delete um;
   TestEquals(l->GetReferenceCount(), 1, "LinkList ref fails(22)");
   l->Release();
}
