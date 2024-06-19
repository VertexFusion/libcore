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
   l->add(&o1, NULL);
   l->add(&o2, NULL);
   l->add(&o3, NULL);
   l->add(&o4, NULL);
   l->add(&o5, NULL);

   Object* i;

   l->rewind();
   TestEquals(l->hasNext(), true, "LinkedList fails (1a)");
   i = l->next();
   TestEquals(i, &o1, "LinkedList fails (1b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (2a)");
   i = l->next();
   TestEquals(i, &o2, "LinkedList fails (2b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (3a)");
   i = l->next();
   TestEquals(i, &o3, "LinkedList fails (3b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (4a)");
   i = l->next();
   TestEquals(i, &o4, "LinkedList fails (4b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (5a)");
   i = l->next();
   TestEquals(i, &o5, "LinkedList fails (5b) ");

   TestEquals(l->hasNext(), false, "LinkedList fails (6)");

   l->rewind();
   TestEquals(l->hasNext(), true, "LinkedList fails (7a)");
   i = l->next();
   TestEquals(i, &o1, "LinkedList fails (7b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (8a)");
   i = l->next();
   TestEquals(i, &o2, "LinkedList fails (8b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (9a)");
   i = l->next();
   TestEquals(i, &o3, "LinkedList fails (9b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (10a)");
   i = l->next();
   TestEquals(i, &o4, "LinkedList fails (10b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (11a)");
   i = l->next();
   TestEquals(i, &o5, "LinkedList fails (11b) ");

   TestEquals(l->hasNext(), false, "LinkedList fails (12)");

   //Addbefore
   l->addBefore(&o3, &o6, NULL);

   l->rewind();
   TestEquals(l->hasNext(), true, "LinkedList fails (13a)");
   i = l->next();
   TestEquals(i, &o1, "LinkedList fails (13b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13c)");
   i = l->next();
   TestEquals(i, &o2, "LinkedList fails (13d) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13e)");
   i = l->next();
   TestEquals(i, &o6, "LinkedList fails (13f) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13g)");
   i = l->next();
   TestEquals(i, &o3, "LinkedList fails (13h) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13i)");
   i = l->next();
   TestEquals(i, &o4, "LinkedList fails (13j) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13k)");
   i = l->next();
   TestEquals(i, &o5, "LinkedList fails (13l) ");

   TestEquals(l->hasNext(), false, "LinkedList fails (13m)");

   //Remove
   l->remove(&o6, NULL);

   l->rewind();
   TestEquals(l->hasNext(), true, "LinkedList fails (13a)");
   i = l->next();
   TestEquals(i, &o1, "LinkedList fails (13b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13c)");
   i = l->next();
   TestEquals(i, &o2, "LinkedList fails (13d) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13g)");
   i = l->next();
   TestEquals(i, &o3, "LinkedList fails (13h) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13i)");
   i = l->next();
   TestEquals(i, &o4, "LinkedList fails (13j) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13k)");
   i = l->next();
   TestEquals(i, &o5, "LinkedList fails (13l) ");

   TestEquals(l->hasNext(), false, "LinkedList fails (13m)");

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
   l->add(&o1, um);
   l->add(&o2, um);
   l->add(&o3, um);
   l->add(&o4, um);
   l->add(&o5, um);

   Object* i;

   l->rewind();
   TestEquals(l->hasNext(), true, "LinkedList fails (1a)");
   i = l->next();
   TestEquals(i, &o1, "LinkedList fails (1b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (2a)");
   i = l->next();
   TestEquals(i, &o2, "LinkedList fails (2b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (3a)");
   i = l->next();
   TestEquals(i, &o3, "LinkedList fails (3b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (4a)");
   i = l->next();
   TestEquals(i, &o4, "LinkedList fails (4b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (5a)");
   i = l->next();
   TestEquals(i, &o5, "LinkedList fails (5b) ");

   TestEquals(l->hasNext(), false, "LinkedList fails (6)");

   l->rewind();
   TestEquals(l->hasNext(), true, "LinkedList fails (7a)");
   i = l->next();
   TestEquals(i, &o1, "LinkedList fails (7b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (8a)");
   i = l->next();
   TestEquals(i, &o2, "LinkedList fails (8b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (9a)");
   i = l->next();
   TestEquals(i, &o3, "LinkedList fails (9b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (10a)");
   i = l->next();
   TestEquals(i, &o4, "LinkedList fails (10b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (11a)");
   i = l->next();
   TestEquals(i, &o5, "LinkedList fails (11b) ");

   TestEquals(l->hasNext(), false, "LinkedList fails (12)");

   //Addbefore
   l->addBefore(&o3, &o6, um);

   l->rewind();
   TestEquals(l->hasNext(), true, "LinkedList fails (13a)");
   i = l->next();
   TestEquals(i, &o1, "LinkedList fails (13b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13c)");
   i = l->next();
   TestEquals(i, &o2, "LinkedList fails (13d) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13e)");
   i = l->next();
   TestEquals(i, &o6, "LinkedList fails (13f) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13g)");
   i = l->next();
   TestEquals(i, &o3, "LinkedList fails (13h) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13i)");
   i = l->next();
   TestEquals(i, &o4, "LinkedList fails (13j) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13k)");
   i = l->next();
   TestEquals(i, &o5, "LinkedList fails (13l) ");

   TestEquals(l->hasNext(), false, "LinkedList fails (13m)");

   //Remove
   l->remove(&o6, um);

   l->rewind();
   TestEquals(l->hasNext(), true, "LinkedList fails (13a)");
   i = l->next();
   TestEquals(i, &o1, "LinkedList fails (13b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13c)");
   i = l->next();
   TestEquals(i, &o2, "LinkedList fails (13d) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13g)");
   i = l->next();
   TestEquals(i, &o3, "LinkedList fails (13h) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13i)");
   i = l->next();
   TestEquals(i, &o4, "LinkedList fails (13j) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (13k)");
   i = l->next();
   TestEquals(i, &o5, "LinkedList fails (13l) ");

   TestEquals(l->hasNext(), false, "LinkedList fails (13m)");

   um->ClearStacks();
   l->release();
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

   l->add(&o1, um);
   l->add(&o2, um);
   l->add(&o3, um);
   l->add(&o4, um);
   l->add(&o5, um);
   um->Close();
   Object* i;

   l->rewind();
   TestEquals(l->hasNext(), true, "LinkedList fails (1a)");
   i = l->next();
   TestEquals(i, &o1, "LinkedList fails (1b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (2a)");
   i = l->next();
   TestEquals(i, &o2, "LinkedList fails (2b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (3a)");
   i = l->next();
   TestEquals(i, &o3, "LinkedList fails (3b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (4a)");
   i = l->next();
   TestEquals(i, &o4, "LinkedList fails (4b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (5a)");
   i = l->next();
   TestEquals(i, &o5, "LinkedList fails (5b) ");

   TestEquals(l->hasNext(), false, "LinkedList fails (6)");

   l->rewind();
   TestEquals(l->hasNext(), true, "LinkedList fails (7a)");
   i = l->next();
   TestEquals(i, &o1, "LinkedList fails (7b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (8a)");
   i = l->next();
   TestEquals(i, &o2, "LinkedList fails (8b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (9a)");
   i = l->next();
   TestEquals(i, &o3, "LinkedList fails (9b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (10a)");
   i = l->next();
   TestEquals(i, &o4, "LinkedList fails (10b) ");

   TestEquals(l->hasNext(), true, "LinkedList fails (11a)");
   i = l->next();
   TestEquals(i, &o5, "LinkedList fails (11b) ");

   TestEquals(l->hasNext(), false, "LinkedList fails (12)");

   l->clear(um);
   um->Close();
   TestEquals(l->size(), 0, "LinkedList fails (13)");

   if(active)// Next test only works with enabled undo manager
   {
      um->Undo();
      TestEquals(l->size(), 5, "LinkedList fails (14)");

      l->rewind();
      TestEquals(l->hasNext(), true, "LinkedList fails (15a)");
      i = l->next();
      TestEquals(i, &o1, "LinkedList fails (15b) ");

      TestEquals(l->hasNext(), true, "LinkedList fails (16a)");
      i = l->next();
      TestEquals(i, &o2, "LinkedList fails (16b) ");

      TestEquals(l->hasNext(), true, "LinkedList fails (17a)");
      i = l->next();
      TestEquals(i, &o3, "LinkedList fails (17b) ");

      TestEquals(l->hasNext(), true, "LinkedList fails (18a)");
      i = l->next();
      TestEquals(i, &o4, "LinkedList fails (18b) ");

      TestEquals(l->hasNext(), true, "LinkedList fails (19a)");
      i = l->next();
      TestEquals(i, &o5, "LinkedList fails (19b) ");

      TestEquals(l->hasNext(), false, "LinkedList fails (20)");

      l->clear(um);
      um->Close();
   }
   TestEquals(l->size(), 0, "LinkedList fails (21)");

   delete um;
   TestEquals(l->referenceCount(), 1, "LinkList ref fails(22)");
   l->release();
}
