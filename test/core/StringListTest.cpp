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
    testEquals(list.size(),0,"StringList::size()==0 failed");
    list.append("item3");
    testEquals(list.size(),1,"StringList::size()==1 failed");
    testEquals(list[0],"item3","list[0]!=item3");
    list.append("item1");
    testEquals(list.size(),2,"StringList::size()==2 failed");
    testEquals(list[1],"item1","list[1]!=item1");
    list.append("item2");
    testEquals(list.size(),3,"StringList::size()==3 failed");
    testEquals(list[2],"item2","list[2]!=item2");

    // contains
    testTrue(list.contains("item2"),"StringList::contains()==true failed");
    testFalse(list.contains("itemX"),"StringList::contains()==false failed");

    // join
    String join = list.join(Char('.'));
    testEquals(join,"item3.item1.item2","StringList::join failed");

    // sort
    list.sort();
    testEquals(list[0],"item1","list[0]!=item1");
    testEquals(list[1],"item2","list[1]!=item2");
    testEquals(list[2],"item3","list[2]!=item3");

   // Range base for
   int64 index=0;
   for(const jm::String& string:list)
   {
      if(index==0)testEquals(string,"item1","list[0]!=item1");
      if(index==1)testEquals(string,"item2","list[1]!=item2");
      if(index==2)testEquals(string,"item3","list[2]!=item3");
      index++;
   }

    // remove
    list.remove("item2");
    testEquals(list.size(),2,"StringList::size()==2 failed");
    testEquals(list[0],"item1","list[0]!=item1");
    testEquals(list[1],"item3","list[1]!=item3");

    // clear
    list.clear();
    testEquals(list.size(),0,"StringList::clear() failed");

}
