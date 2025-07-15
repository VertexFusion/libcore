//
//  VertexTest.cpp
//  tornado
//
//  Created by Uwe Runtemund on 27.10.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#if defined(JM_MACOS) || defined(JM_IOS)
#include <cmath>
#elif defined(JM_LINUX) || defined(JM_ANDROID)
#include <cstdlib>
#include <stdint.h>
#include <cmath>
#elif defined JM_WINDOWS
#endif

#include "VertexTest.h"
#include "core/Vertex2.h"
#include "core/Vertex3.h"
#include "core/Exception.h"
#include "core/Math.h"
#include "core/Vector.h"


using namespace jm;

VertexTest::VertexTest(): Test()
{
   setName("Test Vertex");
}

void VertexTest::doTest()
{


   //180°
   Vertex2 v = Vertex2(1.0, 0.0);
   v.rotate(degToRad(180));
   testEquals(v.x, -1.0, "Vertex2.Rotate 180° (x) fails");
   testEquals(v.y, 0.0, "Vertex2.Rotate 180° (y) fails");

   //90°
   v = Vertex2(1.0, 0.0);
   v.rotate(degToRad(90));
   testEquals(v.x, 0.0, "Vertex2.Rotate 90° (x) fails");
   testEquals(v.y, 1.0, "Vertex2.Rotate 90° (y) fails");

   //-90°
   v = Vertex2(1.0, 0.0);
   v.rotate(degToRad(-90));
   testEquals(v.x, 0.0, "Vertex2.Rotate -90° (x) fails");
   testEquals(v.y, -1.0, "Vertex2.Rotate -90° (y) fails");

   //-360°
   v = Vertex2(1.0, 0.0);
   v.rotate(degToRad(360));
   testEquals(v.x, 1.0, "Vertex2.Rotate 360° (x) fails");
   testEquals(v.y, 0.0, "Vertex2.Rotate 360° (y) fails");

   //60°
   v = Vertex2(1.0, 0.0);
   v.rotate(degToRad(60));
   testEquals(v.x, 1.0 / 2.0, "Vertex2.Rotate 60° (x) fails");
   testEquals(v.y, sqrt(3.0) / 2.0, "Vertex2.Rotate 60° (y) fails");

   // Test case 1: Angle between (1, 0) and (0, 1) should be 90 degrees
   Vertex2 v1(1.0, 0.0);
   Vertex2 v2(0.0, 1.0);
   double expectedAngle = degToRad(90);
   testEquals(v1.angleTo(v2), expectedAngle, "Vertex2.angleTo 90° fails");

   // Test case 2: Angle between (1, 0) and (-1, 0) should be 180 degrees
   v1 = Vertex2(1.0, 0.0);
   v2 = Vertex2(-1.0, 0.0);
   expectedAngle = degToRad(-180);
   testEquals(v1.angleTo(v2), expectedAngle, "Vertex2.angleTo 180° fails");

   // Test case 3: Angle between (1, 0) and (1, 0) should be 0 degrees
   v1 = Vertex2(1.0, 0.0);
   v2 = Vertex2(1.0, 0.0);
   expectedAngle = degToRad(0);
   testEquals(v1.angleTo(v2), expectedAngle, "Vertex2.angleTo 0° fails");

   // Test case 4: Angle between (1, 0) and (0, -1) should be -90 degrees
   v1 = Vertex2(1.0, 0.0);
   v2 = Vertex2(0.0, -1.0);
   expectedAngle = degToRad(-90);
   testEquals(v1.angleTo(v2), expectedAngle, "Vertex2.angleTo -90° fails");

   // Test case 5: Angle between (1, 0) and (sqrt(3)/2, 1/2) should be 30 degrees
   v1 = Vertex2(1.0, 0.0);
   v2 = Vertex2(sqrt(3.0) / 2.0, 1.0 / 2.0);
   expectedAngle = degToRad(30);
   testEquals(v1.angleTo(v2), expectedAngle, "Vertex2.angleTo 30° fails");

   //
   // V3
   //

   //180°
   Vertex3 v3 = Vertex3(1, 0, 0);
   v3.rotateZ(degToRad(180));
   testEquals(v3.x, -1.0, "Vertex2.Rotate 180° (x) fails");
   testEquals(v3.y, 0.0, "Vertex2.Rotate 180° (y) fails");
   testEquals(v3.z, 0.0, "Vertex2.Rotate 180° (z) fails");

   v3 = Vertex3(1, 0, 0);
   v3.rotate(degToRad(180), Vertex3(0, 0, 1));
   testEquals(v3.x, -1.0, "Vertex2.Rotate 180° (x) fails");
   testEquals(v3.y, 0.0, "Vertex2.Rotate 180° (y) fails");
   testEquals(v3.z, 0.0, "Vertex2.Rotate 180° (z) fails");

   v3 = Vertex3(0, 1, 0);
   v3.rotateX(degToRad(180));
   testEquals(v3.x, 0.0, "Vertex2.Rotate 180° (x) fails");
   testEquals(v3.y, -1.0, "Vertex2.Rotate 180° (y) fails");
   testEquals(v3.z, 0.0, "Vertex2.Rotate 180° (z) fails");

   v3 = Vertex3(0, 1, 0);
   v3.rotate(degToRad(180), Vertex3(1, 0, 0));
   testEquals(v3.x, 0.0, "Vertex2.Rotate 180° (x) fails");
   testEquals(v3.y, -1.0, "Vertex2.Rotate 180° (y) fails");
   testEquals(v3.z, 0.0, "Vertex2.Rotate 180° (z) fails");

   v3 = Vertex3(0, 0, 1);
   v3.rotateY(degToRad(180));
   testEquals(v3.x, 0.0, "Vertex2.Rotate 180° (x) fails");
   testEquals(v3.y, 0.0, "Vertex2.Rotate 180° (y) fails");
   testEquals(v3.z, -1.0, "Vertex2.Rotate 180° (z) fails");

   v3 = Vertex3(0, 0, 1);
   v3.rotate(degToRad(180), Vertex3(0, 1, 0));
   testEquals(v3.x, 0.0, "Vertex2.Rotate 180° (x) fails");
   testEquals(v3.y, 0.0, "Vertex2.Rotate 180° (y) fails");
   testEquals(v3.z, -1.0, "Vertex2.Rotate 180° (z) fails");


   //90°
   v3 = Vertex3(1, 0, 0);
   v3.rotateZ(degToRad(90));
   testEquals(v3.x, 0.0, "Vertex2.Rotate 90° (x) fails");
   testEquals(v3.y, 1.0, "Vertex2.Rotate 90° (y) fails");
   testEquals(v3.z, 0.0, "Vertex2.Rotate 90° (z) fails");

   v3 = Vertex3(1, 0, 0);
   v3.rotateZ(degToRad(-90));
   testEquals(v3.x, 0.0, "Vertex2.Rotate -90° (x) fails");
   testEquals(v3.y, -1.0, "Vertex2.Rotate -90° (y) fails");
   testEquals(v3.z, 0.0, "Vertex2.Rotate -90° (y) fails");

   vector();
}

void VertexTest::vector()
{
   // Default constructor
   Vector v = Vector();
   testTrue(v.m == 0, "Vector m not 0");
   testNull(v.data, "Vector data not null");

   // Constructor with size
   v = Vector(3);
   testTrue(v.m == 3, "Vector m not 3");
   testNotNull(v.data, "Vector data null");
   testEquals(v.data[0], 0.0, "Vector data[0] not 0");
   testEquals(v.data[1], 0.0, "Vector data[1] not 0");
   testEquals(v.data[2], 0.0, "Vector data[2] not 0");

   v.data[0] = 1.0;
   v.data[1] = 2.0;
   v.data[2] = 3.0;

   // Copy constructor
   Vector v2 = Vector(v);
   testTrue(v2.m == 3, "Vector m not 3");
   testNotNull(v2.data, "Vector data null");
   testEquals(v2.data[0], 1.0, "Vector data[0] not 1");
   testEquals(v2.data[1], 2.0, "Vector data[1] not 2");
   testEquals(v2.data[2], 3.0, "Vector data[2] not 3");

   // abs
   testEquals(v.abs(), sqrt(14.0), "Vector abs not sqrt(14)");

   // normalize
   v.normalize();
   testEquals(v.data[0], 1.0 / sqrt(14.0), "Vector data[0] not 1/sqrt(14)");

   // zeros
   v.zeros();
   testEquals(v.data[0], 0.0, "Vector data[0] not 0");
   testEquals(v.data[1], 0.0, "Vector data[1] not 0");
   testEquals(v.data[2], 0.0, "Vector data[2] not 0");
   testTrue(v.m == 3, "Vector m not 3");

   // ones
   v.ones();
   testEquals(v.data[0], 1.0, "Vector data[0] not 1");
   testEquals(v.data[1], 1.0, "Vector data[1] not 1");
   testEquals(v.data[2], 1.0, "Vector data[2] not 1");
   testTrue(v.m == 3, "Vector m not 3");

   // dot product
   v2 = Vector(3);
   v2.data[0] = 1.0;
   v2.data[1] = 2.0;
   v2.data[2] = 3.0;
   testEquals(v.dotProduct(v2), 6.0, "Vector dot product not 3");
   testEquals(v2.dotProduct(v), 6.0, "Vector dot product not 3");

   // add
   Vector result = v + v2;
   testEquals(result.data[0], 2.0, "Vector add data[0] not 2");
   testEquals(result.data[1], 3.0, "Vector add data[1] not 3");
   testEquals(result.data[2], 4.0, "Vector add data[2] not 4");
   testTrue(result.m == 3, "Vector add m not 3");

   // subtract
   result = v - v2;
   testEquals(result.data[0], 0.0, "Vector subtract data[0] not 0");
   testEquals(result.data[1], -1.0, "Vector subtract data[1] not -1");
   testEquals(result.data[2], -2.0, "Vector subtract data[2] not -2");

   // multiply
   result = 2.0 * v2;
   testEquals(result.data[0], 2.0, "Vector multiply data[0] not 2");
   testEquals(result.data[1], 4.0, "Vector multiply data[1] not 4");
   testEquals(result.data[2], 6.0, "Vector multiply data[2] not 6");
}
