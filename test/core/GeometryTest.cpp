//
//  GeometryText.cpp
//  jameo
//
//  Created by Uwe Runtemund on 03.08.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "GeometryTest.h"

#include "core/Math.h"
#include "core/Geometry.h"
#include "core/Exception.h"


#ifdef __APPLE__//macOS, iOS
#include <sys/time.h>
#include <mach/mach_time.h>
#define ORWL_NANO (+1.0E-9)
#define ORWL_GIGA UINT64_C(1000000000)

static double orwl_timebase = 0.0;
static uint64_t orwl_timestart = 0;

struct timespec orwl_gettime(void)
{
   // be more careful in a multithreaded environement
   if(!orwl_timestart)
   {
      mach_timebase_info_data_t tb = { 0, 0 };
      mach_timebase_info(&tb);
      orwl_timebase = tb.numer;
      orwl_timebase /= tb.denom;
      orwl_timestart = mach_absolute_time();
   }
   struct timespec t;
   double diff = (mach_absolute_time() - orwl_timestart) * orwl_timebase;
   t.tv_sec = diff * ORWL_NANO;
   t.tv_nsec = diff - (t.tv_sec * ORWL_GIGA);
   return t;
}
#elif defined __linux__ //Linux
#elif defined _WIN32//Windows
#endif





using namespace jm;


GeometryTest::GeometryTest(): Test()
{
   setName("Test Geometry");
}

void GeometryTest::shootAround(double startAngle, double endAngle)
{
   Vertex2 pnt;
   startAngle = degToRad(startAngle);
   endAngle = degToRad(endAngle);
   double s2 = startAngle + M_PI;
   double e2 = endAngle + M_PI;
   const double DBL_PI = 2 * M_PI;

   for(double a = 0; a < 2 * M_PI ; a += 0.01)
   {
      // Shoot
      Vertex2 orig = Vertex2(2.0, 0.0);
      orig.rotate(a);

      Vertex2 result1 = Vertex2(1.0, 0.0);
      result1.rotate(a);

      Vertex2 result2 = Vertex2(-1.0, 0.0);
      result2.rotate(a);

      Vertex2 dir = Vertex2(-1.0, 0.0);
      dir.rotate(a);

      pnt = jm::extensionPointOnArc(orig, dir, Vertex2(0.0, 0.0), 1.0, startAngle, endAngle);

      //Es kann sein, dass die Winkel im Bereich 2pi - 4pi landen, daher wird das abgefragt...

      if((isGreaterEqual(a, startAngle) && isLessEqual(a, endAngle)) ||
            (isGreaterEqual(a + DBL_PI, startAngle) && isLessEqual(a + DBL_PI, endAngle)))
      {
         testEquals(pnt.x, result1.x, "ExtensionPointOnArc fails ANG (x)");
         testEquals(pnt.y, result1.y, "ExtensionPointOnArc fails ANG (y)");
      }
      else if((isGreaterEqual(a, s2) && isLessEqual(a, e2)) || (isGreaterEqual(a + DBL_PI, s2)
              && isLessEqual(a + DBL_PI, e2)))
      {
         testEquals(pnt.x, result2.x, "ExtensionPointOnArc fails ANG (x)");
         testEquals(pnt.y, result2.y, "ExtensionPointOnArc fails ANG (y)");
      }
      else
      {
         //			std::cout << RadToDeg(a) << " " << RadToDeg(startAngle) << " " << RadToDeg(endAngle)<< " NAN \n";
         testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails NAN (x)");
         testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails NAN (y)");
      }

   }
}

void GeometryTest::shootAway(double startAngle, double endAngle)
{
   Vertex2 pnt;
   startAngle = degToRad(startAngle);
   endAngle = degToRad(endAngle);

   //Außerhalb
   for(double a = 0; a < 2 * M_PI ; a += 0.01)
   {
      //Schieße
      Vertex2 orig = Vertex2(2.0, 0.0);
      orig.rotate(a);

      Vertex2 dir = Vertex2(1.0, 0.0);
      dir.rotate(a);

      pnt = jm::extensionPointOnArc(orig, dir, Vertex2(0.0, 0.0), 1.0, startAngle, endAngle);

      //Es kann sein, dass die Winkel im Bereich 2pi - 4pi landen, daher wird das abgefragt...

      testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails NAN (x)");
      testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails NAN (y)");
   }

   //Vom Kreis
   for(double a = 0; a < 2 * M_PI ; a += 0.01)
   {
      //Schieße
      Vertex2 orig = Vertex2(1.0, 0.0);
      orig.rotate(a);

      Vertex2 dir = Vertex2(1.0, 0.0);
      dir.rotate(a);

      pnt = jm::extensionPointOnArc(orig, dir, Vertex2(0.0, 0.0), 1.0, startAngle, endAngle);

      //Es kann sein, dass die Winkel im Bereich 2pi - 4pi landen, daher wird das abgefragt...

      testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails NAN (x)");
      testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails NAN (y)");
   }

}

void GeometryTest::shootOut(double startAngle, double endAngle)
{
   Vertex2 pnt;
   startAngle = degToRad(startAngle);
   endAngle = degToRad(endAngle);
   const double DBL_PI = 2 * M_PI;

   for(double a = 0; a < 2 * M_PI ; a += 0.01)
   {
      //Schieße
      Vertex2 orig = Vertex2(1.0, -1.0);
      orig.rotate(a);

      Vertex2 result1 = Vertex2(1.0, 0.0);
      result1.rotate(a);

      Vertex2 dir = Vertex2(0.0, 1.0);
      dir.rotate(a);

      pnt = jm::extensionPointOnArc(orig, dir, Vertex2(0.0, 0.0), 1.0, startAngle, endAngle);

      //Es kann sein, dass die Winkel im Bereich 2pi - 4pi landen, daher wird das abgefragt...

      if((isGreaterEqual(a, startAngle) && isLessEqual(a, endAngle)) ||
            (isGreaterEqual(a + DBL_PI, startAngle) && isLessEqual(a + DBL_PI, endAngle)))
      {
         testEquals(pnt.x, result1.x, "ExtensionPointOnArc fails ANG (x)");
         testEquals(pnt.y, result1.y, "ExtensionPointOnArc fails ANG (y)");
      }
      else
      {
         //			std::cout << RadToDeg(a) << " " << RadToDeg(startAngle) << " " << RadToDeg(endAngle)<< " NAN \n";
         testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails NAN (x)");
         testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails NAN (y)");
      }

   }
}

void GeometryTest::shootTangent(double startAngle, double endAngle)
{
   Vertex2 pnt;
   startAngle = degToRad(startAngle);
   endAngle = degToRad(endAngle);
   const double DBL_PI = 2 * M_PI;

   //Schieße tangierend am Kreis vorbei

   for(double a = 0; a < 2 * M_PI ; a += 0.01)
   {
      //Schieße
      Vertex2 result1 = Vertex2(1.0, 0.0);
      result1.rotate(a);

      Vertex2 dir = Vertex2(11.0, 0.0);
      dir.rotate(a);

      pnt = jm::extensionPointOnArc(Vertex2(0.0, 0.0), dir, Vertex2(0.0, 0.0), 1.0, startAngle, endAngle);

      //Es kann sein, dass die Winkel im Bereich 2pi - 4pi landen, daher wird das abgefragt...

      if((isGreaterEqual(a, startAngle) && isLessEqual(a, endAngle)) ||
            (isGreaterEqual(a + DBL_PI, startAngle) && isLessEqual(a + DBL_PI, endAngle)))
      {
         testEquals(pnt.x, result1.x, "ExtensionPointOnArc fails ANG (x)");
         testEquals(pnt.y, result1.y, "ExtensionPointOnArc fails ANG (y)");
      }
      else
      {
         //			std::cout << RadToDeg(a) << " " << RadToDeg(startAngle) << " " << RadToDeg(endAngle)<< " NAN \n";
         testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails NAN (x)");
         testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails NAN (y)");
      }

   }
}



void GeometryTest::doTest()
{

   /*
    * Teste IntersectionPointLineAndPlane
    */

   // 1. Test

   //Gerade
   Vertex3 p = Vertex3(1, 2, 3);
   Vertex3 r = Vertex3(-1, 0, 1);

   //Ebene
   Vertex3 a = Vertex3(-1, 3, 0);
   Vertex3 n = Vertex3(-1, 0, 0);

   Vertex3 s = jm::intersectionPointLineAndPlane(a, n, p, r, true);
   testEquals(s.x, -1.0, "IntersectionPointLineAndPlane fails (1x)");
   testEquals(s.y, 2.0, "IntersectionPointLineAndPlane fails (1y)");
   testEquals(s.z, 5.0, "IntersectionPointLineAndPlane fails (1z)");

   // 2. Test (Gerade parallel)
   // Funktion muss NAN liefern

   //Gerade
   p = Vertex3(1, 2, 3);
   r = Vertex3(-1, 1, 0);

   //Ebene
   a = Vertex3(-1, 3, 1);
   n = Vertex3(0, 0, 1);

   s = jm::intersectionPointLineAndPlane(a, n, p, r, true);
   testFalse(s.isValid(), "IntersectionPointLineAndPlane fails (1)");


   // 3. Test (Ebenennormalenvektor ist Nullvektor)
   // Funktion muss NAN liefern

   //Gerade
   p = Vertex3(1, 2, 3);
   r = Vertex3(-1, 1, 0);

   //Ebene
   a = Vertex3(-1, 3, 1);
   n = Vertex3(0, 0, 0);

   s = jm::intersectionPointLineAndPlane(a, n, p, r, true);
   testFalse(s.isValid(), "IntersectionPointLineAndPlane fails (3)");


   // 4. Test (Richtungsvektor ist Nullvektor)
   // Funktion muss NAN liefern

   //Gerade
   p = Vertex3(1, 2, 3);
   r = Vertex3(0, 0, 0);

   //Ebene
   a = Vertex3(-1, 3, 1);
   n = Vertex3(1, 2, 4);

   s = jm::intersectionPointLineAndPlane(a, n, p, r, true);
   testFalse(s.isValid(), "IntersectionPointLineAndPlane fails (4)");

   /*	Vertex3 closestPointOnPlane( Vertex3 point, Vertex3 position, Vertex3 normal );

   Vertex3 closestPointOnLine( Vertex3 point, Vertex3 position, Vertex3 direction );

   Vertex3 closestPointOnLine( Vertex3 position1, Vertex3 direction1, Vertex3 position2, Vertex3 direction2 );

   Vertex3 closestPointOnLine( Vertex3 point, Vertex3 lineStart, Vertex3 lineEnd, bool extend );*/

   /*
    * Teste DistancePointToPlane
    */

   //1. Test
   p = Vertex3(5, -2, 0);

   a = Vertex3(-10, 0, 0);
   n = Vertex3(-1, 4, 19);

   double d = jm::distancePointToPlane(p, a, n);
   testEquals(d, 1.18299234970937128252, "DistancePointToPlane fails (1)");

   //2. Test
   p = Vertex3(5, -2, 365.25);

   a = Vertex3(-10, 5680, 0);
   n = Vertex3(0, 0, 1);

   d = jm::distancePointToPlane(p, a, n);
   testEquals(d, 365.25, "DistancePointToPlane fails (2)");

   //3. Test (Punkt liegt in Ebene)
   p = Vertex3(5, -2, 23);

   a = Vertex3(-10, 5680, 23);
   n = Vertex3(0, 0, 1);

   d = jm::distancePointToPlane(p, a, n);
   testEquals(d, 0.0, "DistancePointToPlane fails (3)");

   //4. Test (Punkt ist Ortsvektor)
   p = Vertex3(-10, 5680, 23);

   a = Vertex3(-10, 5680, 23);
   n = Vertex3(0, 0, 1);

   d = jm::distancePointToPlane(p, a, n);
   testEquals(d, 0.0, "DistancePointToPlane fails (4)");

   /*
   	double distancePointToPoint( Vertex3 point1, Vertex3 point2 );

   	double distancePointToLine( Vertex3 point, Vertex3 position, Vertex3 direction );

   	double distancePointToLine( Vertex3 point, Vertex3 lineStart, Vertex3 lineEnd, bool extend );*/

   // Test case 1: Point in circle plane
   Vertex3 point(10.0, 10.0, 0.0);
   Vertex3 center(0.0, 0.0, 0.0);
   double radius = 5.0;
   Vertex3 normal(0.0, 0.0, 1.0);

   // Expected result
   Vertex3 expected3d(5.0 * cos(M_PI_4), 5.0 * sin(M_PI_4), 0.0);

   // Call the function
   Vertex3 result3d = closestPointOnCircle(point, center, radius, normal);

   testEquals(result3d.x, expected3d.x, "closestPointOnCircle fails (1x)");
   testEquals(result3d.y, expected3d.y, "closestPointOnCircle fails (1y)");
   testEquals(result3d.z, expected3d.z, "closestPointOnCircle fails (1z)");

   // Test case 2: Point not on the plane
   point = Vertex3(10.0, 10.0, 10.0);
   center = Vertex3(0.0, 0.0, 0.0);
   radius = 5.0;
   normal = Vertex3(0.0, 0.0, 1.0);

   expected3d = Vertex3(5.0 * cos(M_PI_4), 5.0 * sin(M_PI_4), 0.0);
   result3d = closestPointOnCircle(point, center, radius, normal);

   testEquals(result3d.x, expected3d.x, "closestPointOnCircle fails (2x)");
   testEquals(result3d.y, expected3d.y, "closestPointOnCircle fails (2y)");
   testEquals(result3d.z, expected3d.z, "closestPointOnCircle fails (2z)");


   /*
    * Teste DistanceLineToLine
    */

   // 1. Test (windschief)
   Vertex3 p1 = Vertex3(2, 0, 0);
   Vertex3 r1 = Vertex3(0, 1, 0);

   Vertex3 p2 = Vertex3(-2, 0, 0);
   Vertex3 r2 = Vertex3(0, 0, 1);

   d = jm::distanceLineToLine(p1, r1, p2, r2);
   testEquals(d, 4.0, "DistanceLineToLine fails (1)");

   // 2. Test (windschief)
   p1 = Vertex3(2, 1, 1);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(-2, 1, 1);
   r2 = Vertex3(0, 0, 1);

   d = jm::distanceLineToLine(p1, r1, p2, r2);
   testEquals(d, 4.0, "DistanceLineToLine fails (2)");

   // 3. Test (windschief)
   p1 = Vertex3(2, 3, 56);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(-2, 34, -87);
   r2 = Vertex3(0, 0, 1);

   d = jm::distanceLineToLine(p1, r1, p2, r2);
   testEquals(d, 4.0, "DistanceLineToLine fails (3)");

   // 4. Test (kreuzen sich)
   p1 = Vertex3(-2, 3, 56);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(-2, 34, -87);
   r2 = Vertex3(0, 0, 1);

   d = jm::distanceLineToLine(p1, r1, p2, r2);
   testEquals(d, 0.0, "DistanceLineToLine fails (4)");

   // 5. Test (kreuzen sich)
   p1 = Vertex3(2, 0, 0);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(2, 0, 0);
   r2 = Vertex3(0, 0, 1);

   d = jm::distanceLineToLine(p1, r1, p2, r2);
   testEquals(d, 0.0, "DistanceLineToLine fails (5)");

   // 6. Test (parallel)
   p1 = Vertex3(-2, 0, 0);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(2, 0, 0);
   r2 = Vertex3(0, 1, 0);

   d = jm::distanceLineToLine(p1, r1, p2, r2);
   testEquals(d, 4.0, "DistanceLineToLine fails (6)");

   // 6. Test (identisch)
   p1 = Vertex3(-2, 0, 0);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(-2, 0, 0);
   r2 = Vertex3(0, 1, 0);

   d = jm::distanceLineToLine(p1, r1, p2, r2);
   testEquals(d, 0.0, "DistanceLineToLine fails (7)");


   /*	bool isPointOnPlane( Vertex3 point, Vertex3 position, Vertex3 normal );

   	bool isPointOnLine( Vertex3 point, Vertex3 position, Vertex3 direction );

   	bool isPointOnLine( Vertex3 point, Vertex3 lineStart, Vertex3 lineEnd, bool extend );

   	bool isPointOnCircle( Vertex3 point, Vertex3 center, double radius, Vertex3 normal );

   	bool isSamePoint( Vertex3 point1, Vertex3 point2 );*/



   //
   //Teste Kreisschnittpunkte AM VOLLKREIS
   //

   //Strahl geht auf Kreis

   Vertex2 pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                         Vertex2(1.0, 0.0),
                                         Vertex2(5.0, 1.0),
                                         1.0, 0, degToRad(360));
   testEquals(pnt.x, 4.0, "ExtensionPointOnArc fails (1x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (1y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.5, 0, degToRad(360));
   testEquals(pnt.x, 3.5, "ExtensionPointOnArc fails (2x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (2y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 2.5),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.5, 0, degToRad(360));
   testEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (3x)");
   testEquals(pnt.y, 2.5, "ExtensionPointOnArc fails (3y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 2.51),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.5, 0, degToRad(360));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (4x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (4y)");

   //Strahl startet im Kreis
   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, 0, degToRad(360));
   testEquals(pnt.x, 2.0, "ExtensionPointOnArc fails (5x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (5y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(0.0, 1.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, 0, degToRad(360));
   testEquals(pnt.x, 1.0, "ExtensionPointOnArc fails (6x)");
   testEquals(pnt.y, 2.0, "ExtensionPointOnArc fails (6y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(-1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, 0, degToRad(360));
   testEquals(pnt.x, 0.0, "ExtensionPointOnArc fails (7x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (7y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(0.0, -1.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, 0, degToRad(360));
   testEquals(pnt.x, 1.0, "ExtensionPointOnArc fails (8x)");
   testEquals(pnt.y, 0.0, "ExtensionPointOnArc fails (8y)");

   //Strahl startet hinter Kreis
   pnt = jm::extensionPointOnArc(Vertex2(3.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, 0, degToRad(360));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (9x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (9y)");

   //Strahl startet auf Kreis
   pnt = jm::extensionPointOnArc(Vertex2(0.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, 0, degToRad(360));
   testEquals(pnt.x, 2.0, "ExtensionPointOnArc fails (10x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (10y)");

   pnt = jm::extensionPointOnArc(Vertex2(2.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, 0, degToRad(360));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (11x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (11y)");

   //
   // Teste nun die Methode mit Kreisabschnitten
   //
   //

   #ifdef __APPLE__//macOS, iOS
   timespec start = orwl_gettime();
   #endif

   //Strahl geht auf Kreis

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.0, 0, degToRad(90));
   testEquals(pnt.x, 6.0, "ExtensionPointOnArc fails (12x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (12y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.5, 0,  degToRad(90));
   testEquals(pnt.x, 6.5, "ExtensionPointOnArc fails (13x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (13y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 2.5),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.5, 0,  degToRad(90));
   testEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (14x)");
   testEquals(pnt.y, 2.5, "ExtensionPointOnArc fails (14y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 2.51),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.5, 0,  degToRad(90));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (15x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (15y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 0.99),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.5, 0,  degToRad(90));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (16x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (16y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.0, degToRad(270), degToRad(90));
   testEquals(pnt.x, 6.0, "ExtensionPointOnArc fails (17x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (17y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.5, degToRad(270), degToRad(90));
   testEquals(pnt.x, 6.5, "ExtensionPointOnArc fails (18x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (18y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 2.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.0, degToRad(270), degToRad(90));
   testEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (19x)");
   testEquals(pnt.y, 2.0, "ExtensionPointOnArc fails (19y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 0.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.0, degToRad(270), degToRad(90));
   testEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (20x)");
   testEquals(pnt.y, 0.0, "ExtensionPointOnArc fails (20y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.0, degToRad(90), degToRad(270));
   testEquals(pnt.x, 4.0, "ExtensionPointOnArc fails (21x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (21y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 2.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.0, degToRad(90), degToRad(270));
   testEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (22x)");
   testEquals(pnt.y, 2.0, "ExtensionPointOnArc fails (22y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 0.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(5.0, 1.0),
                                 1.0, degToRad(90), degToRad(270));
   testEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (23x)");
   testEquals(pnt.y, 0.0, "ExtensionPointOnArc fails (23y)");

   //Strahl startet im Kreis
   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(315), degToRad(45));
   testEquals(pnt.x, 2.0, "ExtensionPointOnArc fails (24x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (24y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(0.0, 1.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(315), degToRad(45));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (25x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (25y)");

   pnt = jm:: extensionPointOnArc(Vertex2(1.0, 1.0),
                                  Vertex2(-1.0, 0.0),
                                  Vertex2(1.0, 1.0),
                                  1.0, degToRad(315), degToRad(45));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (26x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (26y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(0.0, -1.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(315), degToRad(45));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (27x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (27y)");


   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(45), degToRad(135));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (28x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (28y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0), Vertex2(0.0, 1.0), Vertex2(1.0, 1.0), 1.0,
                                 degToRad(45), degToRad(135));
   testEquals(pnt.x, 1.0, "ExtensionPointOnArc fails (29x)");
   testEquals(pnt.y, 2.0, "ExtensionPointOnArc fails (29y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(-1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(45), degToRad(135));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (30x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (30y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(0.0, -1.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(45), degToRad(135));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (31x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (31y)");


   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(135), degToRad(225));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (32x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (33y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(0.0, 1.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(135), degToRad(225));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (34x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (34y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(-1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(135), degToRad(225));
   testEquals(pnt.x, 0.0, "ExtensionPointOnArc fails (35x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (35y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(0.0, -1.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(135), degToRad(225));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (36x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (36y)");


   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(225), degToRad(315));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (37x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (37y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(0.0, 1.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(225), degToRad(315));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (38x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (38y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(-1.0, 0.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(225), degToRad(315));
   testTrue(isNaN(pnt.x), "ExtensionPointOnArc fails (39x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnArc fails (39y)");

   pnt = jm::extensionPointOnArc(Vertex2(1.0, 1.0),
                                 Vertex2(0.0, -1.0),
                                 Vertex2(1.0, 1.0),
                                 1.0, degToRad(225), degToRad(315));
   testEquals(pnt.x, 1.0, "ExtensionPointOnArc fails (40x)");
   testEquals(pnt.y, 0.0, "ExtensionPointOnArc fails (40y)");


   shootAround(0, 90);
   shootAround(90, 180);
   shootAround(180, 270);
   shootAround(270, 360);

   shootAround(45, 135);
   shootAround(135, 225);
   shootAround(225, 315);
   shootAround(315, 405);

   shootAway(0, 90);
   shootAway(90, 180);
   shootAway(180, 270);
   shootAway(270, 360);

   shootAway(45, 135);
   shootAway(135, 225);
   shootAway(225, 315);
   shootAway(315, 405);

   shootOut(0, 90);
   shootOut(90, 180);
   shootOut(180, 270);
   shootOut(270, 360);

   shootOut(45, 135);
   shootOut(135, 225);
   shootOut(225, 315);
   shootOut(315, 405);

   shootTangent(0, 90);
   shootTangent(90, 180);
   shootTangent(180, 270);
   shootTangent(270, 360);

   shootTangent(45, 135);
   shootTangent(135, 225);
   shootTangent(225, 315);
   shootTangent(315, 405);


   /*! Teste Extensionpoint on Line */

   //am Startpunkt vorbei
   pnt = jm::extensionPointOnLine(Vertex2(1.0, -0.1),
                                  Vertex2(1.0, 0.0),
                                  Vertex2(5.0, 0.0),
                                  Vertex2(5.0, 10.0));
   testTrue(isNaN(pnt.x), "ExtensionPointOnLine fails (1x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnLine fails (1y)");

   //Startpunkt
   pnt = jm::extensionPointOnLine(Vertex2(1.0, 0.0),
                                  Vertex2(1.0, 0.0),
                                  Vertex2(5.0, 0.0),
                                  Vertex2(5.0, 10.0));
   testEquals(pnt.x, 5.0, "ExtensionPointOnLine fails (2x)");
   testEquals(pnt.y, 0.0, "ExtensionPointOnLine fails (2y)");

   //Auf der Linie
   pnt = jm::extensionPointOnLine(Vertex2(1.0, 1.0),
                                  Vertex2(1.0, 0.0),
                                  Vertex2(5.0, 0.0),
                                  Vertex2(5.0, 10.0));
   testEquals(pnt.x, 5.0, "ExtensionPointOnLine fails (3x)");
   testEquals(pnt.y, 1.0, "ExtensionPointOnLine fails (3y)");

   //Endpunkt
   pnt = jm::extensionPointOnLine(Vertex2(1.0, 10.0),
                                  Vertex2(1.0, 0.0),
                                  Vertex2(5.0, 0.0),
                                  Vertex2(5.0, 10.0));
   testEquals(pnt.x, 5.0, "ExtensionPointOnLine fails (4x)");
   testEquals(pnt.y, 10.0, "ExtensionPointOnLine fails (4y)");

   //am Endunkt vorbei
   pnt = jm::extensionPointOnLine(Vertex2(1.0, 10.1),
                                  Vertex2(1.0, 0.0),
                                  Vertex2(5.0, 0.0),
                                  Vertex2(5.0, 10.0));
   testTrue(isNaN(pnt.x), "ExtensionPointOnLine fails (5x)");
   testTrue(isNaN(pnt.y), "ExtensionPointOnLine fails (5y)");


   //Schuss nach Diagonal Rechts...
   for(int64 a = 0; a < 3600; a++)
   {
      Vertex2 beg = Vertex2(-1.0, 0.0);
      Vertex2 end = Vertex2(1.0, 0.0);
      double ang = jm::degToRad(a / 3600.0);
      beg.rotate(ang);
      end.rotate(ang);
      beg.y += 2.0;
      end.y += 2.0;
      pnt = jm::extensionPointOnLine(Vertex2(-100.0, 0.0), Vertex2(100.0, 2.0), beg, end);
      if(jm::isEqual(ang, 0.01999733397))
      {
         testTrue(isNaN(pnt.x), "ExtensionPointOnLine fails (6x nan)");
         testTrue(isNaN(pnt.y), "ExtensionPointOnLine fails (6y nan)");
      }
      else
      {
         testEquals(pnt.x, 0.0, "ExtensionPointOnLine fails (6x)");
         testEquals(pnt.y, 2.0, "ExtensionPointOnLine fails (6y)");
      }
   }

   /* Teste Crosses */
   testTrue(jm::crosses(Vertex2(0.0, 0.0), Vertex2(1.0, 1.0),
                        Vertex2(0.0, 1.0), Vertex2(1.0, 0.0)), "Crosses fails (1)");
   testTrue(jm::crosses(Vertex2(1.0, 1.0), Vertex2(0.0, 0.0),
                        Vertex2(0.0, 1.0), Vertex2(1.0, 0.0)), "Crosses fails (2)");
   testTrue(jm::crosses(Vertex2(0.0, 0.0), Vertex2(1.0, 1.0),
                        Vertex2(1.0, 0.0), Vertex2(0.0, 1.0)), "Crosses fails (3)");
   testTrue(jm::crosses(Vertex2(1.0, 1.0), Vertex2(0.0, 0.0),
                        Vertex2(1.0, 0.0), Vertex2(0.0, 1.0)), "Crosses fails (4)");

   testFalse(jm::crosses(Vertex2(0.0, 0.0), Vertex2(1.0, 0.0),
                         Vertex2(0.0, 1.0), Vertex2(1.0, 1.0)), "Crosses fails (5)");
   testFalse(jm::crosses(Vertex2(0.0, 0.0), Vertex2(1.0, 0.0),
                         Vertex2(0.1, 0.5), Vertex2(1.0, 0.5)), "Crosses fails (6)");
   testFalse(jm::crosses(Vertex2(0.0, 0.0), Vertex2(1.0, 0.0),
                         Vertex2(1.0, 0.5), Vertex2(0.1, 0.5)), "Crosses fails (6)");

   testFalse(jm::crosses(Vertex2(397.0, 293.0), Vertex2(416.0, 312.0),
                         Vertex2(379.0, 272.0), Vertex2(379.0, 262.0)), "Crosses fails (7)");


   // Intersection point 2d
   jm::Vertex2 v1(0.0, 1.0);
   jm::Vertex2 d1(1.0, 0.0);
   jm::Vertex2 v2(1.0, 0.0);
   jm::Vertex2 d2(0.0, 1.0);
   jm::Vertex2 ip = jm::intersectionPoint(v1, d1, v2, d2);

   testEquals(ip.x, 1.0, "intersectionPoint() fails 1");
   testEquals(ip.y, 1.0, "intersectionPoint() fails 1");

   d1 = jm::Vertex2(-1.0, 0.0);
   d2 = jm::Vertex2(0.0, 1.0);
   ip = jm::intersectionPoint(v1, d1, v2, d2);

   testEquals(ip.x, 1.0, "intersectionPoint() fails 2");
   testEquals(ip.y, 1.0, "intersectionPoint() fails 2");

   d1 = jm::Vertex2(1.0, 0.0);
   d2 = jm::Vertex2(0.0, -1.0);
   ip = jm::intersectionPoint(v1, d1, v2, d2);

   testEquals(ip.x, 1.0, "intersectionPoint() fails 3");
   testEquals(ip.y, 1.0, "intersectionPoint() fails 3");

   d1 = jm::Vertex2(-1.0, 0.0);
   d2 = jm::Vertex2(0.0, -1.0);
   ip = jm::intersectionPoint(v1, d1, v2, d2);

   testEquals(ip.x, 1.0, "intersectionPoint() fails 4");
   testEquals(ip.y, 1.0, "intersectionPoint() fails 4");

   //
   // circleParameterBy2TangentsRadius
   //
   v1 = jm::Vertex2(-1.0, 1.0);
   v2 = jm::Vertex2(1.0, -1.0);
   d1 = jm::Vertex2(2.0, 0.0);
   d2 = jm::Vertex2(0.0, 2.0);
   jm::circleParameterBy2TangentsRadius(ip, 0.5, v1, d1, v2, d2);

   testEquals(ip.x, 0.5, "circleParameterBy2TangentsRadius() fails 1");
   testEquals(ip.y, 0.5, "circleParameterBy2TangentsRadius() fails 1");


   v1 = jm::Vertex2(23, 107);
   v2 = jm::Vertex2(26, 107);
   d1 = jm::Vertex2(0, -3);
   d2 = jm::Vertex2(-3, 0);
   jm::circleParameterBy2TangentsRadius(ip, 3, v1, d1, v2, d2);

   testEquals(ip.x, 26.0, "circleParameterBy2TangentsRadius() fails 1");
   testEquals(ip.y, 104.0, "circleParameterBy2TangentsRadius() fails 1");

   // points on cross point of tangents
   v1 = jm::Vertex2(1.0, 1.0);
   v2 = jm::Vertex2(1.0, 1.0);
   d1 = jm::Vertex2(-1.0, 0.0);
   d2 = jm::Vertex2(0.0, -1.0);
   jm::circleParameterBy2TangentsRadius(ip, 0.5, v1, d1, v2, d2);

   testEquals(ip.x, 0.5, "circleParameterBy2TangentsRadius() fails 1");
   testEquals(ip.y, 0.5, "circleParameterBy2TangentsRadius() fails 1");

   jm::circleParameterBy2TangentsRadius(ip, 0.5, v1, d2, v2, d1);

   testEquals(ip.x, 0.5, "circleParameterBy2TangentsRadius() fails 1");
   testEquals(ip.y, 0.5, "circleParameterBy2TangentsRadius() fails 1");

   d1 = jm::Vertex2(1.0, 0.0);
   d2 = jm::Vertex2(0.0, -1.0);
   jm::circleParameterBy2TangentsRadius(ip, 0.5, v1, d1, v2, d2);

   testEquals(ip.x, 1.5, "circleParameterBy2TangentsRadius() fails 1");
   testEquals(ip.y, 0.5, "circleParameterBy2TangentsRadius() fails 1");

   jm::circleParameterBy2TangentsRadius(ip, 0.5, v1, d2, v2, d1);

   testEquals(ip.x, 1.5, "circleParameterBy2TangentsRadius() fails 1");
   testEquals(ip.y, 0.5, "circleParameterBy2TangentsRadius() fails 1");

   d1 = jm::Vertex2(-1.0, 0.0);
   d2 = jm::Vertex2(0.0, 1.0);
   jm::circleParameterBy2TangentsRadius(ip, 0.5, v1, d1, v2, d2);

   testEquals(ip.x, 0.5, "circleParameterBy2TangentsRadius() fails 1");
   testEquals(ip.y, 1.5, "circleParameterBy2TangentsRadius() fails 1");

   jm::circleParameterBy2TangentsRadius(ip, 0.5, v1, d2, v2, d1);

   testEquals(ip.x, 0.5, "circleParameterBy2TangentsRadius() fails 1");
   testEquals(ip.y, 1.5, "circleParameterBy2TangentsRadius() fails 1");

   d1 = jm::Vertex2(1.0, 0.0);
   d2 = jm::Vertex2(0.0, 1.0);
   jm::circleParameterBy2TangentsRadius(ip, 0.5, v1, d1, v2, d2);

   testEquals(ip.x, 1.5, "circleParameterBy2TangentsRadius() fails 1");
   testEquals(ip.y, 1.5, "circleParameterBy2TangentsRadius() fails 1");

   jm::circleParameterBy2TangentsRadius(ip, 0.5, v1, d2, v2, d1);

   testEquals(ip.x, 1.5, "circleParameterBy2TangentsRadius() fails 1");
   testEquals(ip.y, 1.5, "circleParameterBy2TangentsRadius() fails 1");

   //
   // Closest point on line (diagonal)
   //
   v1 = jm::Vertex2(3, 4);
   v2 = jm::Vertex2(0, 0);
   d2 = jm::Vertex2(1, 1);
   Vertex2 expected(3.5, 3.5);

   Vertex2 result = closestPointOnLine(v1, v2, d2);
   testEquals(expected.x, result.x, "closestPointOnLine() fails 1");
   testEquals(expected.y, result.y, "closestPointOnLine() fails 1");

   //Closest point on line (horizontal)
   v1 = Vertex2(3, 4);
   v2 = Vertex2(0, 4);
   d2 = Vertex2(1, 0);
   expected = Vertex2(3, 4);

   result = closestPointOnLine(v1, v2, d2);
   testEquals(expected.x, result.x, "closestPointOnLine() fails 1");
   testEquals(expected.y, result.y, "closestPointOnLine() fails 1");

   // Closest point on line (vertical)
   v1 = Vertex2(3, 4);
   v2 = Vertex2(3, 0);
   d2 = Vertex2(0, 1);
   expected = Vertex2(3, 4);

   result = closestPointOnLine(v1, v2, d2);
   testEquals(expected.x, result.x, "closestPointOnLine() fails 1");
   testEquals(expected.y, result.y, "closestPointOnLine() fails 1");

   //
   // Distance point to point
   //
   v1 = Vertex2(3, 4);
   v2 = Vertex2(0, 0);
   double dist = jm::distancePointToPoint(v1, v2);
   testEquals(dist, 5.0, "distance() fails (1)");

   //
   // Intersection points of two circles
   // 

   // not intersecting
   v1 = Vertex2(0, 0);
   v2 = Vertex2(5, 0);
   double rd1 = 2;
   double rd2 = 2;
   Vertex2 ip1, ip2;
   jm::intersectionPointsOfCircles(v1, rd1, v2, rd2, ip1, ip2);
   testFalse(ip1.isValid(), "intersectionPointsOfCircles() fails (1)");
   testFalse(ip2.isValid(), "intersectionPointsOfCircles() fails (1)");
   testTrue(isNaN(ip1.x), "intersectionPointsOfCircles() fails (2)");
   testTrue(isNaN(ip1.y), "intersectionPointsOfCircles() fails (2)");
   testTrue(isNaN(ip2.x), "intersectionPointsOfCircles() fails (2)");
   testTrue(isNaN(ip2.y), "intersectionPointsOfCircles() fails (2)");

   // same circle
   v1 = Vertex2(0, 0);
   v2 = Vertex2(0, 0);
   rd1 = 2;
   rd2 = 2;
   jm::intersectionPointsOfCircles(v1, rd1, v2, rd2, ip1, ip2);
   testFalse(ip1.isValid(), "intersectionPointsOfCircles() fails (3)");
   testFalse(ip2.isValid(), "intersectionPointsOfCircles() fails (3)");
   testTrue(isNaN(ip1.x), "intersectionPointsOfCircles() fails (4)");
   testTrue(isNaN(ip1.y), "intersectionPointsOfCircles() fails (4)");
   testTrue(isNaN(ip2.x), "intersectionPointsOfCircles() fails (4)");
   testTrue(isNaN(ip2.y), "intersectionPointsOfCircles() fails (4)");

   // not intersection inside
   v1 = Vertex2(0.2, 0);
   rd1 = 1.5;
   rd2 = 2;
   jm::intersectionPointsOfCircles(v1, rd1, v2, rd2, ip1, ip2);
   testFalse(ip1.isValid(), "intersectionPointsOfCircles() fails (3)");
   testFalse(ip2.isValid(), "intersectionPointsOfCircles() fails (3)");
   testTrue(isNaN(ip1.x), "intersectionPointsOfCircles() fails (4)");
   testTrue(isNaN(ip1.y), "intersectionPointsOfCircles() fails (4)");
   testTrue(isNaN(ip2.x), "intersectionPointsOfCircles() fails (4)");
   testTrue(isNaN(ip2.y), "intersectionPointsOfCircles() fails (4)");

   // intersection in one point
   v1 = Vertex2(0, 0);
   v2 = Vertex2(4, 0);
   rd1 = 2;
   rd2 = 2;
   jm::intersectionPointsOfCircles(v1, rd1, v2, rd2, ip1, ip2);
   testTrue(ip1.isValid(), "intersectionPointsOfCircles() fails (5)");
   testTrue(ip2.isValid(), "intersectionPointsOfCircles() fails (5)");
   testEquals(ip1.x, 2.0, "intersectionPointsOfCircles() fails (6)");
   testEquals(ip1.y, 0.0, "intersectionPointsOfCircles() fails (6)");
   testEquals(ip2.x, 2.0, "intersectionPointsOfCircles() fails (6)");
   testEquals(ip2.y, 0.0, "intersectionPointsOfCircles() fails (6)");

   // intersection in two points
   v1 = Vertex2(0, 0);
   v2 = Vertex2(8, 0);
   rd1 = 5;
   rd2 = 5;
   jm::intersectionPointsOfCircles(v1, rd1, v2, rd2, ip1, ip2);
   testTrue(ip1.isValid(), "intersectionPointsOfCircles() fails (7)");
   testTrue(ip2.isValid(), "intersectionPointsOfCircles() fails (7)");
   testEquals(ip1.x, 4.0, "intersectionPointsOfCircles() fails (8)");
   testEquals(ip1.y, -3.0, "intersectionPointsOfCircles() fails (8)");
   testEquals(ip2.x, 4.0, "intersectionPointsOfCircles() fails (8)");
   testEquals(ip2.y, 3.0, "intersectionPointsOfCircles() fails (8)");
   

   #ifdef __APPLE__//macOS, iOS
   timespec end = orwl_gettime();

   long nanos = end.tv_nsec - start.tv_nsec;

   std::cout << "\n\nNANOS: " << nanos << "\n\n";
   #endif

   extents();
   points3d();
}

void GeometryTest::extents()
{

   Extents e;
   testFalse(e.isValid(), "Extents fails (1)");

   e.add(Vertex3(0.0, 0.0,0.0));
   testTrue(e.isValid(), "Extents fails (2)");
   testEquals(e.minPoint().x, 0.0, "Extents fails (3)");
   testEquals(e.minPoint().y, 0.0, "Extents fails (4)");
   testEquals(e.minPoint().z, 0.0, "Extents fails (5)");
   testEquals(e.maxPoint().x, 0.0, "Extents fails (6)");
   testEquals(e.maxPoint().y, 0.0, "Extents fails (7)");
   testEquals(e.maxPoint().z, 0.0, "Extents fails (8)");

   Extents e2;
   e2.add(Vertex3(1.0, 2.0, 3.0));

   e.add(e2);
   testTrue(e.isValid(), "Extents fails (9)");
   testEquals(e.minPoint().x, 0.0, "Extents fails (10)");
   testEquals(e.minPoint().y, 0.0, "Extents fails (11)");
   testEquals(e.minPoint().z, 0.0, "Extents fails (12)");
   testEquals(e.maxPoint().x, 1.0, "Extents fails (13)");
   testEquals(e.maxPoint().y, 2.0, "Extents fails (14)");
   testEquals(e.maxPoint().z, 3.0, "Extents fails (15)");

   e.add(Vertex2(-1.0,-2.0));
   testTrue(e.isValid(), "Extents fails (16)");
   testEquals(e.minPoint().x, -1.0, "Extents fails (17)");
   testEquals(e.minPoint().y, -2.0, "Extents fails (18)");
   testEquals(e.minPoint().z, 0.0, "Extents fails (19)");
   testEquals(e.maxPoint().x, 1.0, "Extents fails (20)");
   testEquals(e.maxPoint().y, 2.0, "Extents fails (21)");
   testEquals(e.maxPoint().z, 3.0, "Extents fails (22)");

   jm::Vertex3 delta=e.delta();
   testEquals(delta.x, 2.0, "Extents fails (23)");
   testEquals(delta.y, 4.0, "Extents fails (24)");
   testEquals(delta.z, 3.0, "Extents fails (25)");
}

void GeometryTest::points3d()
{

   // distancve point to line
   jm::Vertex3 o1(0.0, 0.0, 0.0);
   jm::Vertex3 o2(0.0, 0.0, 3.0);
   jm::Vertex3 pt(3.0, 4.0, 2.0);
   jm::Vertex3 d1(0.0, 0.0, 1.0);

   double distance=jm::distancePointToLine(pt, o1, d1);
   testEquals(distance, 5.0, "distancePointToLine() fails (1)");

   // closest point on line
   jm::Vertex3 result=jm::closestPointOnLine(pt, o1, o2, false);
   testEquals(result.x, 0.0, "closestPointOnLine() fails (1)");
   testEquals(result.y, 0.0, "closestPointOnLine() fails (2)");
   testEquals(result.z, 2.0, "closestPointOnLine() fails (3)");

   pt=jm::Vertex3(3.0, 4.0, 5.0);
   result=jm::closestPointOnLine(pt, o1, o2, true);
   testEquals(result.x, 0.0, "closestPointOnLine() fails (4)");
   testEquals(result.y, 0.0, "closestPointOnLine() fails (5)");
   testEquals(result.z, 5.0, "closestPointOnLine() fails (6)");

   distance=jm::distancePointToLine(pt, o1, o2, true);
   testEquals(distance, 5.0, "distancePointToLine() fails (2)");

   distance=jm::distancePointToLine(pt, o1, o2, false);
   testTrue(jm::isNaN(distance), "distancePointToLine() fails (3)");

   pt=jm::Vertex3(3.0, 4.0, 5.0);
   result=jm::closestPointOnLine(pt, o1, o2, false);
   testFalse(result.isValid(), "closestPointOnLine() fails (7)");
   testTrue(isNaN(result.x), "closestPointOnLine() fails (8)");
   testTrue(isNaN(result.y), "closestPointOnLine() fails (9)");
   testTrue(isNaN(result.z), "closestPointOnLine() fails (10)");

   // distance point to circle
   jm::Vertex3 center(0.0, 0.0, 0.0);
   double radius=5.0;
   jm::Vertex3 pt1(0.0, 0.0, 0.0);
   jm::Vertex3 pt2(1.0, 0.0, 0.0);
   jm::Vertex3 pt3(5.0, 0.0, 0.0);
   jm::Vertex3 pt4(10.0, 0.0, 0.0);
   distance=jm::distancePointToCircle(pt1, center, radius, jm::Vertex3(0.0, 0.0, 1.0));
   testEquals(distance, 5.0, "distancePointToCircle() fails (1)");
   distance=jm::distancePointToCircle(pt2, center, radius, jm::Vertex3(0.0, 0.0, 1.0));
   testEquals(distance, 4.0, "distancePointToCircle() fails (2)");
   distance=jm::distancePointToCircle(pt3, center, radius, jm::Vertex3(0.0, 0.0, 1.0));
   testEquals(distance, 0.0, "distancePointToCircle() fails (3)");
   distance=jm::distancePointToCircle(pt4, center, radius, jm::Vertex3(0.0, 0.0, 1.0));
   testEquals(distance, 5.0, "distancePointToCircle() fails (4)");

}