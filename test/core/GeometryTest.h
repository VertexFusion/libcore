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
	void ShootAround(double startAngle, double endAngle, double delta);
	void ShootAway(double startAngle, double endAngle, double delta);
	void ShootOut(double startAngle, double endAngle, double delta);
	void ShootTangent(double startAngle, double endAngle, double delta);

public:
	GeometryTest(bool debug);
	void DoTest();
	
};

#endif 
