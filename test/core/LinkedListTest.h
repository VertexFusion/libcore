//
//  LinkedListTest.h
//  tornado
//
//  Created by Uwe Runtemund on 10.10.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#ifndef __tornado__LinkedListTest__
#define __tornado__LinkedListTest__

#include "core/Test.h"

class LinkedListTest : public jm::Test
{
   public:
      LinkedListTest();
      void DoTest();

      void DoTest1();
      void DoTest2(bool active);
      void DoTest3(bool active);
};

#endif /* defined(__tornado__LinkedListTest__) */
