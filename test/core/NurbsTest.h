//
//  NurbsTest.h
//  jameo
//
//  Created by Uwe Runtemund on 28.06.25.
//  Copyright (c) 2014 Jameo Software. All rights reserved.
//

#ifndef __jameo__NurbsTest__
#define __jameo__NurbsTest__

#include "core/Test.h"

class NurbsTest : public jm::Test
{
   public:
      NurbsTest();
      void doTest();

   private:

      void testBasisFunctionPartitionOfUnity();
      void testOpenSplineEndpoints();
      void testClosedNonClampedSpline();
      void testPeriodicSpline();
      void testDegree1InterpolatesControlPoints();

};

#endif
