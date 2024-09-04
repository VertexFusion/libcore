//
//  GeometryTest.h
//  jameo
//
//  Created by Uwe Runtemund on 03.08.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#ifndef jm_GeometryTest_h
#define jm_GeometryTest_h

#include "core/Test.h"

class GeometryTest : public jm::Test
{
   private:
      void shootAround(double startAngle, double endAngle);
      void shootAway(double startAngle, double endAngle);
      void shootOut(double startAngle, double endAngle);
      void shootTangent(double startAngle, double endAngle);

   public:
      GeometryTest();
      void DoTest();

};

#endif
