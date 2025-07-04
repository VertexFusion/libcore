//
//  Testcase.cpp
//  jameo
//
//  Created by Uwe Runtemund on 17.01.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "core/Core.h"
#include "StringListTest.h"

using namespace jm;

StringListTest::StringListTest(): Test()
{
   setName("Test StringList");
}

void StringListTest::doTest()
{
   // Size // append
   StringList list;
   testEquals(list.size(), 0UL, "StringList::size()==0 failed");
   list.append("item3");
   testEquals(list.size(), 1UL, "StringList::size()==1 failed");
   testEquals(list[0], "item3", "list[0]!=item3");
   list.append("item1");
   testEquals(list.size(), 2UL, "StringList::size()==2 failed");
   testEquals(list[1], "item1", "list[1]!=item1");
   list.append("item2");
   testEquals(list.size(), 3UL, "StringList::size()==3 failed");
   testEquals(list[2], "item2", "list[2]!=item2");

   // contains
   testTrue(list.contains("item2"), "StringList::contains()==true failed");
   testFalse(list.contains("itemX"), "StringList::contains()==false failed");

   // join
   String join = list.join(Char('.'));
   testEquals(join, "item3.item1.item2", "StringList::join failed");

   // sort
   list.sort();
   testEquals(list[0], "item1", "list[0]!=item1");
   testEquals(list[1], "item2", "list[1]!=item2");
   testEquals(list[2], "item3", "list[2]!=item3");

   // Range base for
   int64 index = 0;
   for(const jm::String& string : list)
   {
      if(index == 0)testEquals(string, "item1", "list[0]!=item1");
      if(index == 1)testEquals(string, "item2", "list[1]!=item2");
      if(index == 2)testEquals(string, "item3", "list[2]!=item3");
      index++;
   }
   testEquals(index, 3, "index wrong");

   // remove
   list.remove("item2");
   testEquals(list.size(), 2UL, "StringList::size()==2 failed");
   testEquals(list[0], "item1", "list[0]!=item1");
   testEquals(list[1], "item3", "list[1]!=item3");

   // clear
   list.clear();
   testEquals(list.size(), 0UL, "StringList::clear() failed");

   // Initialize list with specified size
   StringList list2(5);
   testEquals(list2.size(), 5UL, "StringList::size()==5 failed");
   testEquals(list2[0], jm::kEmptyString, "list[0]!=");
   testEquals(list2[1], jm::kEmptyString, "list[1]!=");
   testEquals(list2[2], jm::kEmptyString, "list[2]!=");
   testEquals(list2[3], jm::kEmptyString, "list[3]!=");
   testEquals(list2[4], jm::kEmptyString, "list[4]!=");
}
