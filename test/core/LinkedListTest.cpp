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
   setName("Test LinkedList");
}

void LinkedListTest::doTest()
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
   l->add(&o1, nullptr);
   l->add(&o2, nullptr);
   l->add(&o3, nullptr);
   l->add(&o4, nullptr);
   l->add(&o5, nullptr);

   Object* i;

   l->rewind();
   testEquals(l->hasNext(), true, "LinkedList fails (1a)");
   i = l->next();
   testEquals(i, &o1, "LinkedList fails (1b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (2a)");
   i = l->next();
   testEquals(i, &o2, "LinkedList fails (2b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (3a)");
   i = l->next();
   testEquals(i, &o3, "LinkedList fails (3b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (4a)");
   i = l->next();
   testEquals(i, &o4, "LinkedList fails (4b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (5a)");
   i = l->next();
   testEquals(i, &o5, "LinkedList fails (5b) ");

   testEquals(l->hasNext(), false, "LinkedList fails (6)");

   l->rewind();
   testEquals(l->hasNext(), true, "LinkedList fails (7a)");
   i = l->next();
   testEquals(i, &o1, "LinkedList fails (7b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (8a)");
   i = l->next();
   testEquals(i, &o2, "LinkedList fails (8b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (9a)");
   i = l->next();
   testEquals(i, &o3, "LinkedList fails (9b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (10a)");
   i = l->next();
   testEquals(i, &o4, "LinkedList fails (10b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (11a)");
   i = l->next();
   testEquals(i, &o5, "LinkedList fails (11b) ");

   testEquals(l->hasNext(), false, "LinkedList fails (12)");

   //Addbefore
   l->addBefore(&o3, &o6, nullptr);

   l->rewind();
   testEquals(l->hasNext(), true, "LinkedList fails (13a)");
   i = l->next();
   testEquals(i, &o1, "LinkedList fails (13b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13c)");
   i = l->next();
   testEquals(i, &o2, "LinkedList fails (13d) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13e)");
   i = l->next();
   testEquals(i, &o6, "LinkedList fails (13f) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13g)");
   i = l->next();
   testEquals(i, &o3, "LinkedList fails (13h) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13i)");
   i = l->next();
   testEquals(i, &o4, "LinkedList fails (13j) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13k)");
   i = l->next();
   testEquals(i, &o5, "LinkedList fails (13l) ");

   testEquals(l->hasNext(), false, "LinkedList fails (13m)");

   //Remove
   l->remove(&o6, nullptr);

   l->rewind();
   testEquals(l->hasNext(), true, "LinkedList fails (13a)");
   i = l->next();
   testEquals(i, &o1, "LinkedList fails (13b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13c)");
   i = l->next();
   testEquals(i, &o2, "LinkedList fails (13d) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13g)");
   i = l->next();
   testEquals(i, &o3, "LinkedList fails (13h) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13i)");
   i = l->next();
   testEquals(i, &o4, "LinkedList fails (13j) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13k)");
   i = l->next();
   testEquals(i, &o5, "LinkedList fails (13l) ");

   testEquals(l->hasNext(), false, "LinkedList fails (13m)");

   delete l;
}


void LinkedListTest::DoTest2(bool active)
{
   // Test mit Undo-Manager
   UndoManager* um = new UndoManager();
   um->setActive(active);

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
   testEquals(l->hasNext(), true, "LinkedList fails (1a)");
   i = l->next();
   testEquals(i, &o1, "LinkedList fails (1b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (2a)");
   i = l->next();
   testEquals(i, &o2, "LinkedList fails (2b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (3a)");
   i = l->next();
   testEquals(i, &o3, "LinkedList fails (3b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (4a)");
   i = l->next();
   testEquals(i, &o4, "LinkedList fails (4b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (5a)");
   i = l->next();
   testEquals(i, &o5, "LinkedList fails (5b) ");

   testEquals(l->hasNext(), false, "LinkedList fails (6)");

   l->rewind();
   testEquals(l->hasNext(), true, "LinkedList fails (7a)");
   i = l->next();
   testEquals(i, &o1, "LinkedList fails (7b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (8a)");
   i = l->next();
   testEquals(i, &o2, "LinkedList fails (8b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (9a)");
   i = l->next();
   testEquals(i, &o3, "LinkedList fails (9b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (10a)");
   i = l->next();
   testEquals(i, &o4, "LinkedList fails (10b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (11a)");
   i = l->next();
   testEquals(i, &o5, "LinkedList fails (11b) ");

   testEquals(l->hasNext(), false, "LinkedList fails (12)");

   //Addbefore
   l->addBefore(&o3, &o6, um);

   l->rewind();
   testEquals(l->hasNext(), true, "LinkedList fails (13a)");
   i = l->next();
   testEquals(i, &o1, "LinkedList fails (13b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13c)");
   i = l->next();
   testEquals(i, &o2, "LinkedList fails (13d) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13e)");
   i = l->next();
   testEquals(i, &o6, "LinkedList fails (13f) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13g)");
   i = l->next();
   testEquals(i, &o3, "LinkedList fails (13h) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13i)");
   i = l->next();
   testEquals(i, &o4, "LinkedList fails (13j) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13k)");
   i = l->next();
   testEquals(i, &o5, "LinkedList fails (13l) ");

   testEquals(l->hasNext(), false, "LinkedList fails (13m)");

   //Remove
   l->remove(&o6, um);

   l->rewind();
   testEquals(l->hasNext(), true, "LinkedList fails (13a)");
   i = l->next();
   testEquals(i, &o1, "LinkedList fails (13b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13c)");
   i = l->next();
   testEquals(i, &o2, "LinkedList fails (13d) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13g)");
   i = l->next();
   testEquals(i, &o3, "LinkedList fails (13h) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13i)");
   i = l->next();
   testEquals(i, &o4, "LinkedList fails (13j) ");

   testEquals(l->hasNext(), true, "LinkedList fails (13k)");
   i = l->next();
   testEquals(i, &o5, "LinkedList fails (13l) ");

   testEquals(l->hasNext(), false, "LinkedList fails (13m)");

   um->clearStacks();
   l->release();
   delete um;

}

void LinkedListTest::DoTest3(bool active)
{
   // Test mit Undo-Manager
   UndoManager* um = new UndoManager();
   um->setActive(active);

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
   um->close();
   Object* i;

   l->rewind();
   testEquals(l->hasNext(), true, "LinkedList fails (1a)");
   i = l->next();
   testEquals(i, &o1, "LinkedList fails (1b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (2a)");
   i = l->next();
   testEquals(i, &o2, "LinkedList fails (2b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (3a)");
   i = l->next();
   testEquals(i, &o3, "LinkedList fails (3b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (4a)");
   i = l->next();
   testEquals(i, &o4, "LinkedList fails (4b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (5a)");
   i = l->next();
   testEquals(i, &o5, "LinkedList fails (5b) ");

   testEquals(l->hasNext(), false, "LinkedList fails (6)");

   l->rewind();
   testEquals(l->hasNext(), true, "LinkedList fails (7a)");
   i = l->next();
   testEquals(i, &o1, "LinkedList fails (7b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (8a)");
   i = l->next();
   testEquals(i, &o2, "LinkedList fails (8b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (9a)");
   i = l->next();
   testEquals(i, &o3, "LinkedList fails (9b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (10a)");
   i = l->next();
   testEquals(i, &o4, "LinkedList fails (10b) ");

   testEquals(l->hasNext(), true, "LinkedList fails (11a)");
   i = l->next();
   testEquals(i, &o5, "LinkedList fails (11b) ");

   testEquals(l->hasNext(), false, "LinkedList fails (12)");

   l->clear(um);
   um->close();
   testEquals(l->size(), 0UL, "LinkedList fails (13)");

   if(active)// Next test only works with enabled undo manager
   {
      um->undo();
      testEquals(l->size(), 5UL, "LinkedList fails (14)");

      l->rewind();
      testEquals(l->hasNext(), true, "LinkedList fails (15a)");
      i = l->next();
      testEquals(i, &o1, "LinkedList fails (15b) ");

      testEquals(l->hasNext(), true, "LinkedList fails (16a)");
      i = l->next();
      testEquals(i, &o2, "LinkedList fails (16b) ");

      testEquals(l->hasNext(), true, "LinkedList fails (17a)");
      i = l->next();
      testEquals(i, &o3, "LinkedList fails (17b) ");

      testEquals(l->hasNext(), true, "LinkedList fails (18a)");
      i = l->next();
      testEquals(i, &o4, "LinkedList fails (18b) ");

      testEquals(l->hasNext(), true, "LinkedList fails (19a)");
      i = l->next();
      testEquals(i, &o5, "LinkedList fails (19b) ");

      testEquals(l->hasNext(), false, "LinkedList fails (20)");

      l->clear(um);
      um->close();
   }
   testEquals(l->size(), 0UL, "LinkedList fails (21)");

   delete um;
   testEquals(l->referenceCount(), 1, "LinkList ref fails(22)");
   l->release();
}
