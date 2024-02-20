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


using namespace std;
using namespace jm;

VertexTest::VertexTest(): Test()
{
   SetName("Test Vertex");
}

void VertexTest::DoTest()
{


   //180°
   Vertex2 v = Vertex2(1, 0);
   v.Rotate(DegToRad(180));
   TestEquals(v.x, -1.0, "Vertex2.Rotate 180° (x) fails");
   TestEquals(v.y, 0.0, "Vertex2.Rotate 180° (y) fails");

   //90°
   v = Vertex2(1, 0);
   v.Rotate(DegToRad(90));
   TestEquals(v.x, 0.0, "Vertex2.Rotate 90° (x) fails");
   TestEquals(v.y, 1.0, "Vertex2.Rotate 90° (y) fails");

   //-90°
   v = Vertex2(1, 0);
   v.Rotate(DegToRad(-90));
   TestEquals(v.x, 0.0, "Vertex2.Rotate -90° (x) fails");
   TestEquals(v.y, -1.0, "Vertex2.Rotate -90° (y) fails");

   //-360°
   v = Vertex2(1, 0);
   v.Rotate(DegToRad(360));
   TestEquals(v.x, 1.0, "Vertex2.Rotate 360° (x) fails");
   TestEquals(v.y, 0.0, "Vertex2.Rotate 360° (y) fails");

   //60°
   v = Vertex2(1, 0);
   v.Rotate(DegToRad(60));
   TestEquals(v.x, 1.0 / 2.0, "Vertex2.Rotate 60° (x) fails");
   TestEquals(v.y, sqrt(3.0) / 2.0, "Vertex2.Rotate 60° (y) fails");


   //
   // V3
   //

   //180°
   Vertex3 v3 = Vertex3(1, 0, 0);
   v3.RotateZ(DegToRad(180));
   TestEquals(v3.x, -1.0, "Vertex2.Rotate 180° (x) fails");
   TestEquals(v3.y, 0.0, "Vertex2.Rotate 180° (y) fails");
   TestEquals(v3.z, 0.0, "Vertex2.Rotate 180° (z) fails");

   v3 = Vertex3(1, 0, 0);
   v3.Rotate(DegToRad(180), Vertex3(0, 0, 1));
   TestEquals(v3.x, -1.0, "Vertex2.Rotate 180° (x) fails");
   TestEquals(v3.y, 0.0, "Vertex2.Rotate 180° (y) fails");
   TestEquals(v3.z, 0.0, "Vertex2.Rotate 180° (z) fails");

   v3 = Vertex3(0, 1, 0);
   v3.RotateX(DegToRad(180));
   TestEquals(v3.x, 0.0, "Vertex2.Rotate 180° (x) fails");
   TestEquals(v3.y, -1.0, "Vertex2.Rotate 180° (y) fails");
   TestEquals(v3.z, 0.0, "Vertex2.Rotate 180° (z) fails");

   v3 = Vertex3(0, 1, 0);
   v3.Rotate(DegToRad(180), Vertex3(1, 0, 0));
   TestEquals(v3.x, 0.0, "Vertex2.Rotate 180° (x) fails");
   TestEquals(v3.y, -1.0, "Vertex2.Rotate 180° (y) fails");
   TestEquals(v3.z, 0.0, "Vertex2.Rotate 180° (z) fails");

   v3 = Vertex3(0, 0, 1);
   v3.RotateY(DegToRad(180));
   TestEquals(v3.x, 0.0, "Vertex2.Rotate 180° (x) fails");
   TestEquals(v3.y, 0.0, "Vertex2.Rotate 180° (y) fails");
   TestEquals(v3.z, -1.0, "Vertex2.Rotate 180° (z) fails");

   v3 = Vertex3(0, 0, 1);
   v3.Rotate(DegToRad(180), Vertex3(0, 1, 0));
   TestEquals(v3.x, 0.0, "Vertex2.Rotate 180° (x) fails");
   TestEquals(v3.y, 0.0, "Vertex2.Rotate 180° (y) fails");
   TestEquals(v3.z, -1.0, "Vertex2.Rotate 180° (z) fails");


   //90°
   v3 = Vertex3(1, 0, 0);
   v3.RotateZ(DegToRad(90));
   TestEquals(v3.x, 0.0, "Vertex2.Rotate 90° (x) fails");
   TestEquals(v3.y, 1.0, "Vertex2.Rotate 90° (y) fails");
   TestEquals(v3.z, 0.0, "Vertex2.Rotate 90° (z) fails");

   v3 = Vertex3(1, 0, 0);
   v3.RotateZ(DegToRad(-90));
   TestEquals(v3.x, 0.0, "Vertex2.Rotate -90° (x) fails");
   TestEquals(v3.y, -1.0, "Vertex2.Rotate -90° (y) fails");
   TestEquals(v3.z, 0.0, "Vertex2.Rotate -90° (y) fails");

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
