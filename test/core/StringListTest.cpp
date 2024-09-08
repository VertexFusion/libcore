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
   SetName("Test StringList");
}

void StringListTest::doTest()
{
    // Size // append
    StringList list;
    TestEquals(list.size(),0,"StringList::size()==0 failed");
    list.append("item3");
    TestEquals(list.size(),1,"StringList::size()==1 failed");
    TestEquals(list[0],"item3","list[0]!=item3");
    list.append("item1");
    TestEquals(list.size(),2,"StringList::size()==2 failed");
    TestEquals(list[1],"item1","list[1]!=item1");
    list.append("item2");
    TestEquals(list.size(),3,"StringList::size()==3 failed");
    TestEquals(list[2],"item2","list[2]!=item2");

    // contains
    TestTrue(list.contains("item2"),"StringList::contains()==true failed");
    TestFalse(list.contains("itemX"),"StringList::contains()==false failed");

    // join
    String join = list.join(Char('.'));
    TestEquals(join,"item3.item1.item2","StringList::join failed");

    // sort
    list.sort();
    TestEquals(list[0],"item1","list[0]!=item1");
    TestEquals(list[1],"item2","list[1]!=item2");
    TestEquals(list[2],"item3","list[2]!=item3");

    // remove
    list.remove("item2");
    TestEquals(list.size(),2,"StringList::size()==2 failed");
    TestEquals(list[0],"item1","list[0]!=item1");
    TestEquals(list[1],"item3","list[1]!=item3");

    // clear
    list.clear();
    TestEquals(list.size(),0,"StringList::clear() failed");

}
