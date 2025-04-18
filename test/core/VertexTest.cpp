//
//  VertexTest.cpp
//  tornado
//
//  Created by Uwe Runtemund on 27.10.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#ifdef __APPLE__//macOS, iOS
#include <cmath>
#elif defined __linux__ //Linux
#include <cstdlib>
#include <stdint.h>
#include <cmath>
#elif defined _WIN32//Windows
#endif

#include "VertexTest.h"
#include "core/Vertex2.h"
#include "core/Vertex3.h"
#include "core/Exception.h"
#include "core/Math.h"


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

   /*//-90°
   v = Vertex2(1,0);
    v.Rotate(DegToRad(-90));
    TestEquals(v.x, 0.0, "Vertex2.Rotate -90° (x) fails");
    TestEquals(v.y, -1.0, "Vertex2.Rotate -90° (y) fails");

   //-360°
   v = Vertex2(1,0);
    v.Rotate(DegToRad(360));
    TestEquals(v.x, 1.0, "Vertex2.Rotate 360° (x) fails");
    TestEquals(v.y, 0.0, "Vertex2.Rotate 360° (y) fails");

   //60°
   v = Vertex2(1,0);
    v.Rotate(DegToRad(60));
    TestEquals(v.x, 1.0/2.0, "Vertex2.Rotate 60° (x) fails");
    TestEquals(v.y, sqrt(3.0)/2.0, "Vertex2.Rotate 60° (y) fails");
   */
}
