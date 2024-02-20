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
      mach_timebase_info_data_t tb = { 0 };
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
   SetName("Test Geometry");
}

void GeometryTest::ShootAround(double startAngle, double endAngle, double delta)
{
   Vertex2 pnt;
   startAngle = DegToRad(startAngle);
   endAngle = DegToRad(endAngle);
   double s2 = startAngle + M_PI;
   double e2 = endAngle + M_PI;
   const double DBL_PI = 2 * M_PI;

   for(double a = 0; a < 2 * M_PI ; a += 0.01)
   {
      //Schieße
      Vertex2 orig = Vertex2(2, 0);
      orig.Rotate(a);

      Vertex2 result1 = Vertex2(1, 0);
      result1.Rotate(a);

      Vertex2 result2 = Vertex2(-1, 0);
      result2.Rotate(a);

      Vertex2 dir = Vertex2(-1, 0);
      dir.Rotate(a);

      pnt = jm::ExtensionPointOnArc(orig, dir, Vertex2(0, 0), 1.0, startAngle, endAngle);

      //Es kann sein, dass die Winkel im Bereich 2pi - 4pi landen, daher wird das abgefragt...

      if((IsGreaterEqual(a, startAngle) && IsLessEqual(a, endAngle)) ||
            (IsGreaterEqual(a + DBL_PI, startAngle) && IsLessEqual(a + DBL_PI, endAngle)))
      {
         TestEquals(pnt.x, result1.x, "ExtensionPointOnArc fails ANG (x)");
         TestEquals(pnt.y, result1.y, "ExtensionPointOnArc fails ANG (y)");
      }
      else if((IsGreaterEqual(a, s2) && IsLessEqual(a, e2)) || (IsGreaterEqual(a + DBL_PI, s2) && IsLessEqual(a + DBL_PI, e2)))
      {
         TestEquals(pnt.x, result2.x, "ExtensionPointOnArc fails ANG (x)");
         TestEquals(pnt.y, result2.y, "ExtensionPointOnArc fails ANG (y)");
      }
      else
      {
         //			std::cout << RadToDeg(a) << " " << RadToDeg(startAngle) << " " << RadToDeg(endAngle)<< " NAN \n";
         TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails NAN (x)");
         TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails NAN (y)");
      }

   }
}

void GeometryTest::ShootAway(double startAngle, double endAngle, double delta)
{
   Vertex2 pnt;
   startAngle = DegToRad(startAngle);
   endAngle = DegToRad(endAngle);

   //Außerhalb
   for(double a = 0; a < 2 * M_PI ; a += 0.01)
   {
      //Schieße
      Vertex2 orig = Vertex2(2, 0);
      orig.Rotate(a);

      Vertex2 dir = Vertex2(1, 0);
      dir.Rotate(a);

      pnt = jm::ExtensionPointOnArc(orig, dir, Vertex2(0, 0), 1.0, startAngle, endAngle);

      //Es kann sein, dass die Winkel im Bereich 2pi - 4pi landen, daher wird das abgefragt...

      TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails NAN (x)");
      TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails NAN (y)");
   }

   //Vom Kreis
   for(double a = 0; a < 2 * M_PI ; a += 0.01)
   {
      //Schieße
      Vertex2 orig = Vertex2(1, 0);
      orig.Rotate(a);

      Vertex2 dir = Vertex2(1, 0);
      dir.Rotate(a);

      pnt = jm::ExtensionPointOnArc(orig, dir, Vertex2(0, 0), 1.0, startAngle, endAngle);

      //Es kann sein, dass die Winkel im Bereich 2pi - 4pi landen, daher wird das abgefragt...

      TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails NAN (x)");
      TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails NAN (y)");
   }

}

void GeometryTest::ShootOut(double startAngle, double endAngle, double delta)
{
   Vertex2 pnt;
   startAngle = DegToRad(startAngle);
   endAngle = DegToRad(endAngle);
   const double DBL_PI = 2 * M_PI;

   for(double a = 0; a < 2 * M_PI ; a += 0.01)
   {
      //Schieße
      Vertex2 orig = Vertex2(1, -1);
      orig.Rotate(a);

      Vertex2 result1 = Vertex2(1, 0);
      result1.Rotate(a);

      Vertex2 dir = Vertex2(0, 1);
      dir.Rotate(a);

      pnt = jm::ExtensionPointOnArc(orig, dir, Vertex2(0, 0), 1.0, startAngle, endAngle);

      //Es kann sein, dass die Winkel im Bereich 2pi - 4pi landen, daher wird das abgefragt...

      if((IsGreaterEqual(a, startAngle) && IsLessEqual(a, endAngle)) ||
            (IsGreaterEqual(a + DBL_PI, startAngle) && IsLessEqual(a + DBL_PI, endAngle)))
      {
         TestEquals(pnt.x, result1.x, "ExtensionPointOnArc fails ANG (x)");
         TestEquals(pnt.y, result1.y, "ExtensionPointOnArc fails ANG (y)");
      }
      else
      {
         //			std::cout << RadToDeg(a) << " " << RadToDeg(startAngle) << " " << RadToDeg(endAngle)<< " NAN \n";
         TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails NAN (x)");
         TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails NAN (y)");
      }

   }
}

void GeometryTest::ShootTangent(double startAngle, double endAngle, double delta)
{
   Vertex2 pnt;
   startAngle = DegToRad(startAngle);
   endAngle = DegToRad(endAngle);
   const double DBL_PI = 2 * M_PI;

   //Schieße tangierend am Kreis vorbei

   for(double a = 0; a < 2 * M_PI ; a += 0.01)
   {
      //Schieße
      Vertex2 result1 = Vertex2(1, 0);
      result1.Rotate(a);

      Vertex2 dir = Vertex2(11, 0);
      dir.Rotate(a);

      pnt = jm::ExtensionPointOnArc(Vertex2(0, 0), dir, Vertex2(0, 0), 1.0, startAngle, endAngle);

      //Es kann sein, dass die Winkel im Bereich 2pi - 4pi landen, daher wird das abgefragt...

      if((IsGreaterEqual(a, startAngle) && IsLessEqual(a, endAngle)) ||
            (IsGreaterEqual(a + DBL_PI, startAngle) && IsLessEqual(a + DBL_PI, endAngle)))
      {
         TestEquals(pnt.x, result1.x, "ExtensionPointOnArc fails ANG (x)");
         TestEquals(pnt.y, result1.y, "ExtensionPointOnArc fails ANG (y)");
      }
      else
      {
         //			std::cout << RadToDeg(a) << " " << RadToDeg(startAngle) << " " << RadToDeg(endAngle)<< " NAN \n";
         TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails NAN (x)");
         TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails NAN (y)");
      }

   }
}



void GeometryTest::DoTest()
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

   Vertex3 s = jm::IntersectionPointLineAndPlane(a, n, p, r, true);
   TestEquals(s.x, -1.0, "IntersectionPointLineAndPlane fails (1x)");
   TestEquals(s.y, 2.0, "IntersectionPointLineAndPlane fails (1y)");
   TestEquals(s.z, 5.0, "IntersectionPointLineAndPlane fails (1z)");

   // 2. Test (Gerade parallel)
   // Funktion muss NAN liefern

   //Gerade
   p = Vertex3(1, 2, 3);
   r = Vertex3(-1, 1, 0);

   //Ebene
   a = Vertex3(-1, 3, 1);
   n = Vertex3(0, 0, 1);

   s = jm::IntersectionPointLineAndPlane(a, n, p, r, true);
   TestFalse(s.IsValid(), "IntersectionPointLineAndPlane fails (1)");


   // 3. Test (Ebenennormalenvektor ist Nullvektor)
   // Funktion muss NAN liefern

   //Gerade
   p = Vertex3(1, 2, 3);
   r = Vertex3(-1, 1, 0);

   //Ebene
   a = Vertex3(-1, 3, 1);
   n = Vertex3(0, 0, 0);

   s = jm::IntersectionPointLineAndPlane(a, n, p, r, true);
   TestFalse(s.IsValid(), "IntersectionPointLineAndPlane fails (3)");


   // 4. Test (Richtungsvektor ist Nullvektor)
   // Funktion muss NAN liefern

   //Gerade
   p = Vertex3(1, 2, 3);
   r = Vertex3(0, 0, 0);

   //Ebene
   a = Vertex3(-1, 3, 1);
   n = Vertex3(1, 2, 4);

   s = jm::IntersectionPointLineAndPlane(a, n, p, r, true);
   TestFalse(s.IsValid(), "IntersectionPointLineAndPlane fails (4)");

   /*	Vertex3 ClosestPointOnPlane( Vertex3 point, Vertex3 position, Vertex3 normal );

   Vertex3 ClosestPointOnLine( Vertex3 point, Vertex3 position, Vertex3 direction );

   Vertex3 ClosestPointOnLine( Vertex3 position1, Vertex3 direction1, Vertex3 position2, Vertex3 direction2 );

   Vertex3 ClosestPointOnLine( Vertex3 point, Vertex3 lineStart, Vertex3 lineEnd, bool extend );

   Vertex3 ClosestPointOnCircle( Vertex3 point, Vertex3 center, double radius, Vertex3 normal );*/


   /*
    * Teste DistancePointToPlane
    */

   //1. Test
   p = Vertex3(5, -2, 0);

   a = Vertex3(-10, 0, 0);
   n = Vertex3(-1, 4, 19);

   double d = jm::DistancePointToPlane(p, a, n);
   TestEquals(d, 1.18299234970937128252, "DistancePointToPlane fails (1)");

   //2. Test
   p = Vertex3(5, -2, 365.25);

   a = Vertex3(-10, 5680, 0);
   n = Vertex3(0, 0, 1);

   d = jm::DistancePointToPlane(p, a, n);
   TestEquals(d, 365.25, "DistancePointToPlane fails (2)");

   //3. Test (Punkt liegt in Ebene)
   p = Vertex3(5, -2, 23);

   a = Vertex3(-10, 5680, 23);
   n = Vertex3(0, 0, 1);

   d = jm::DistancePointToPlane(p, a, n);
   TestEquals(d, 0.0, "DistancePointToPlane fails (3)");

   //4. Test (Punkt ist Ortsvektor)
   p = Vertex3(-10, 5680, 23);

   a = Vertex3(-10, 5680, 23);
   n = Vertex3(0, 0, 1);

   d = jm::DistancePointToPlane(p, a, n);
   TestEquals(d, 0.0, "DistancePointToPlane fails (4)");

   /*
   	double DistancePointToPoint( Vertex3 point1, Vertex3 point2 );

   	double DistancePointToLine( Vertex3 point, Vertex3 position, Vertex3 direction );

   	double DistancePointToLine( Vertex3 point, Vertex3 lineStart, Vertex3 lineEnd, bool extend );

   	double DistancePointToCircle( Vertex3 point, Vertex3 center, double radius, Vertex3 normal );*/

   /*
    * Teste DistanceLineToLine
    */

   // 1. Test (windschief)
   Vertex3 p1 = Vertex3(2, 0, 0);
   Vertex3 r1 = Vertex3(0, 1, 0);

   Vertex3 p2 = Vertex3(-2, 0, 0);
   Vertex3 r2 = Vertex3(0, 0, 1);

   d = jm::DistanceLineToLine(p1, r1, p2, r2);
   TestEquals(d, 4.0, "DistanceLineToLine fails (1)");

   // 2. Test (windschief)
   p1 = Vertex3(2, 1, 1);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(-2, 1, 1);
   r2 = Vertex3(0, 0, 1);

   d = jm::DistanceLineToLine(p1, r1, p2, r2);
   TestEquals(d, 4.0, "DistanceLineToLine fails (2)");

   // 3. Test (windschief)
   p1 = Vertex3(2, 3, 56);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(-2, 34, -87);
   r2 = Vertex3(0, 0, 1);

   d = jm::DistanceLineToLine(p1, r1, p2, r2);
   TestEquals(d, 4.0, "DistanceLineToLine fails (3)");

   // 4. Test (kreuzen sich)
   p1 = Vertex3(-2, 3, 56);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(-2, 34, -87);
   r2 = Vertex3(0, 0, 1);

   d = jm::DistanceLineToLine(p1, r1, p2, r2);
   TestEquals(d, 0.0, "DistanceLineToLine fails (4)");

   // 5. Test (kreuzen sich)
   p1 = Vertex3(2, 0, 0);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(2, 0, 0);
   r2 = Vertex3(0, 0, 1);

   d = jm::DistanceLineToLine(p1, r1, p2, r2);
   TestEquals(d, 0.0, "DistanceLineToLine fails (5)");

   // 6. Test (parallel)
   p1 = Vertex3(-2, 0, 0);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(2, 0, 0);
   r2 = Vertex3(0, 1, 0);

   d = jm::DistanceLineToLine(p1, r1, p2, r2);
   TestEquals(d, 4.0, "DistanceLineToLine fails (6)");

   // 6. Test (identisch)
   p1 = Vertex3(-2, 0, 0);
   r1 = Vertex3(0, 1, 0);

   p2 = Vertex3(-2, 0, 0);
   r2 = Vertex3(0, 1, 0);

   d = jm::DistanceLineToLine(p1, r1, p2, r2);
   TestEquals(d, 0.0, "DistanceLineToLine fails (7)");


   /*	bool IsOnPlane( Vertex3 point, Vertex3 position, Vertex3 normal );

   	bool IsOnLine( Vertex3 point, Vertex3 position, Vertex3 direction );

   	bool IsOnLine( Vertex3 point, Vertex3 lineStart, Vertex3 lineEnd, bool extend );

   	bool IsOnCircle( Vertex3 point, Vertex3 center, double radius, Vertex3 normal );

   	bool IsSamePoint( Vertex3 point1, Vertex3 point2 );*/



   //
   //Teste Kreisschnittpunkte AM VOLLKREIS
   //

   //Strahl geht auf Kreis

   Vertex2 pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(5, 1), 1.0, 0, DegToRad(360));
   TestEquals(pnt.x, 4.0, "ExtensionPointOnArc fails (1x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (1y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(5, 1), 1.5, 0, DegToRad(360));
   TestEquals(pnt.x, 3.5, "ExtensionPointOnArc fails (2x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (2y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 2.5), Vertex2(1, 0), Vertex2(5, 1), 1.5, 0, DegToRad(360));
   TestEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (3x)");
   TestEquals(pnt.y, 2.5, "ExtensionPointOnArc fails (3y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 2.51), Vertex2(1, 0), Vertex2(5, 1), 1.5, 0, DegToRad(360));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (4x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (4y)");

   //Strahl startet im Kreis
   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(1, 1), 1.0, 0, DegToRad(360));
   TestEquals(pnt.x, 2.0, "ExtensionPointOnArc fails (5x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (5y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(0, 1), Vertex2(1, 1), 1.0, 0, DegToRad(360));
   TestEquals(pnt.x, 1.0, "ExtensionPointOnArc fails (6x)");
   TestEquals(pnt.y, 2.0, "ExtensionPointOnArc fails (6y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(-1, 0), Vertex2(1, 1), 1.0, 0, DegToRad(360));
   TestEquals(pnt.x, 0.0, "ExtensionPointOnArc fails (7x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (7y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(0, -1), Vertex2(1, 1), 1.0, 0, DegToRad(360));
   TestEquals(pnt.x, 1.0, "ExtensionPointOnArc fails (8x)");
   TestEquals(pnt.y, 0.0, "ExtensionPointOnArc fails (8y)");

   //Strahl startet hinter Kreis
   pnt = jm::ExtensionPointOnArc(Vertex2(3, 1), Vertex2(1, 0), Vertex2(1, 1), 1.0, 0, DegToRad(360));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (9x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (9y)");

   //Strahl startet auf Kreis
   pnt = jm::ExtensionPointOnArc(Vertex2(0, 1), Vertex2(1, 0), Vertex2(1, 1), 1.0, 0, DegToRad(360));
   TestEquals(pnt.x, 2.0, "ExtensionPointOnArc fails (10x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (10y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(2, 1), Vertex2(1, 0), Vertex2(1, 1), 1.0, 0, DegToRad(360));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (11x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (11y)");

   //
   // Teste nun die Methode mit Kreisabschnitten
   //
   //

   #ifdef __APPLE__//macOS, iOS
   timespec start = orwl_gettime();
   #endif

   //Strahl geht auf Kreis

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(5, 1), 1.0, 0, DegToRad(90));
   TestEquals(pnt.x, 6.0, "ExtensionPointOnArc fails (12x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (12y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(5, 1), 1.5, 0,  DegToRad(90));
   TestEquals(pnt.x, 6.5, "ExtensionPointOnArc fails (13x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (13y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 2.5), Vertex2(1, 0), Vertex2(5, 1), 1.5, 0,  DegToRad(90));
   TestEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (14x)");
   TestEquals(pnt.y, 2.5, "ExtensionPointOnArc fails (14y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 2.51), Vertex2(1, 0), Vertex2(5, 1), 1.5, 0,  DegToRad(90));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (15x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (15y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 0.99), Vertex2(1, 0), Vertex2(5, 1), 1.5, 0,  DegToRad(90));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (16x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (16y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(5, 1), 1.0, DegToRad(270), DegToRad(90));
   TestEquals(pnt.x, 6.0, "ExtensionPointOnArc fails (17x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (17y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(5, 1), 1.5, DegToRad(270), DegToRad(90));
   TestEquals(pnt.x, 6.5, "ExtensionPointOnArc fails (18x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (18y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 2), Vertex2(1, 0), Vertex2(5, 1), 1.0, DegToRad(270), DegToRad(90));
   TestEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (19x)");
   TestEquals(pnt.y, 2.0, "ExtensionPointOnArc fails (19y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 0), Vertex2(1, 0), Vertex2(5, 1), 1.0, DegToRad(270), DegToRad(90));
   TestEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (20x)");
   TestEquals(pnt.y, 0.0, "ExtensionPointOnArc fails (20y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(5, 1), 1.0, DegToRad(90), DegToRad(270));
   TestEquals(pnt.x, 4.0, "ExtensionPointOnArc fails (21x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (21y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 2), Vertex2(1, 0), Vertex2(5, 1), 1.0, DegToRad(90), DegToRad(270));
   TestEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (22x)");
   TestEquals(pnt.y, 2.0, "ExtensionPointOnArc fails (22y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 0), Vertex2(1, 0), Vertex2(5, 1), 1.0, DegToRad(90), DegToRad(270));
   TestEquals(pnt.x, 5.0, "ExtensionPointOnArc fails (23x)");
   TestEquals(pnt.y, 0.0, "ExtensionPointOnArc fails (23y)");

   //Strahl startet im Kreis
   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(1, 1), 1.0, DegToRad(315), DegToRad(45));
   TestEquals(pnt.x, 2.0, "ExtensionPointOnArc fails (24x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (24y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(0, 1), Vertex2(1, 1), 1.0, DegToRad(315), DegToRad(45));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (25x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (25y)");

   pnt = jm:: ExtensionPointOnArc(Vertex2(1, 1), Vertex2(-1, 0), Vertex2(1, 1), 1.0, DegToRad(315), DegToRad(45));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (26x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (26y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(0, -1), Vertex2(1, 1), 1.0, DegToRad(315), DegToRad(45));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (27x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (27y)");


   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(1, 1), 1.0, DegToRad(45), DegToRad(135));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (28x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (28y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(0, 1), Vertex2(1, 1), 1.0, DegToRad(45), DegToRad(135));
   TestEquals(pnt.x, 1.0, "ExtensionPointOnArc fails (29x)");
   TestEquals(pnt.y, 2.0, "ExtensionPointOnArc fails (29y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(-1, 0), Vertex2(1, 1), 1.0, DegToRad(45), DegToRad(135));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (30x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (30y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(0, -1), Vertex2(1, 1), 1.0, DegToRad(45), DegToRad(135));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (31x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (31y)");


   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(1, 1), 1.0, DegToRad(135), DegToRad(225));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (32x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (33y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(0, 1), Vertex2(1, 1), 1.0, DegToRad(135), DegToRad(225));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (34x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (34y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(-1, 0), Vertex2(1, 1), 1.0, DegToRad(135), DegToRad(225));
   TestEquals(pnt.x, 0.0, "ExtensionPointOnArc fails (35x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnArc fails (35y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(0, -1), Vertex2(1, 1), 1.0, DegToRad(135), DegToRad(225));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (36x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (36y)");


   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(1, 0), Vertex2(1, 1), 1.0, DegToRad(225), DegToRad(315));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (37x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (37y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(0, 1), Vertex2(1, 1), 1.0, DegToRad(225), DegToRad(315));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (38x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (38y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(-1, 0), Vertex2(1, 1), 1.0, DegToRad(225), DegToRad(315));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnArc fails (39x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnArc fails (39y)");

   pnt = jm::ExtensionPointOnArc(Vertex2(1, 1), Vertex2(0, -1), Vertex2(1, 1), 1.0, DegToRad(225), DegToRad(315));
   TestEquals(pnt.x, 1.0, "ExtensionPointOnArc fails (40x)");
   TestEquals(pnt.y, 0.0, "ExtensionPointOnArc fails (40y)");


   ShootAround(0, 90, 0.01);
   ShootAround(90, 180, 0.01);
   ShootAround(180, 270, 0.01);
   ShootAround(270, 360, 0.01);

   ShootAround(45, 135, 0.01);
   ShootAround(135, 225, 0.01);
   ShootAround(225, 315, 0.01);
   ShootAround(315, 405, 0.01);

   ShootAway(0, 90, 0.01);
   ShootAway(90, 180, 0.01);
   ShootAway(180, 270, 0.01);
   ShootAway(270, 360, 0.01);

   ShootAway(45, 135, 0.01);
   ShootAway(135, 225, 0.01);
   ShootAway(225, 315, 0.01);
   ShootAway(315, 405, 0.01);

   ShootOut(0, 90, 0.01);
   ShootOut(90, 180, 0.01);
   ShootOut(180, 270, 0.01);
   ShootOut(270, 360, 0.01);

   ShootOut(45, 135, 0.01);
   ShootOut(135, 225, 0.01);
   ShootOut(225, 315, 0.01);
   ShootOut(315, 405, 0.01);

   ShootTangent(0, 90, 0.01);
   ShootTangent(90, 180, 0.01);
   ShootTangent(180, 270, 0.01);
   ShootTangent(270, 360, 0.01);

   ShootTangent(45, 135, 0.01);
   ShootTangent(135, 225, 0.01);
   ShootTangent(225, 315, 0.01);
   ShootTangent(315, 405, 0.01);


   /*! Teste Extensionpoint on Line */

   //am Startpunkt vorbei
   pnt = jm::ExtensionPointOnLine(Vertex2(1, -0.1), Vertex2(1, 0), Vertex2(5, 0), Vertex2(5, 10));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnLine fails (1x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnLine fails (1y)");

   //Startpunkt
   pnt = jm::ExtensionPointOnLine(Vertex2(1, 0), Vertex2(1, 0), Vertex2(5, 0), Vertex2(5, 10));
   TestEquals(pnt.x, 5.0, "ExtensionPointOnLine fails (2x)");
   TestEquals(pnt.y, 0.0, "ExtensionPointOnLine fails (2y)");

   //Auf der Linie
   pnt = jm::ExtensionPointOnLine(Vertex2(1, 1), Vertex2(1, 0), Vertex2(5, 0), Vertex2(5, 10));
   TestEquals(pnt.x, 5.0, "ExtensionPointOnLine fails (3x)");
   TestEquals(pnt.y, 1.0, "ExtensionPointOnLine fails (3y)");

   //Endpunkt
   pnt = jm::ExtensionPointOnLine(Vertex2(1, 10), Vertex2(1, 0), Vertex2(5, 0), Vertex2(5, 10));
   TestEquals(pnt.x, 5.0, "ExtensionPointOnLine fails (4x)");
   TestEquals(pnt.y, 10.0, "ExtensionPointOnLine fails (4y)");

   //am Endunkt vorbei
   pnt = jm::ExtensionPointOnLine(Vertex2(1, 10.1), Vertex2(1, 0), Vertex2(5, 0), Vertex2(5, 10));
   TestTrue(IsNaN(pnt.x), "ExtensionPointOnLine fails (5x)");
   TestTrue(IsNaN(pnt.y), "ExtensionPointOnLine fails (5y)");


   //Schuss nach Diagonal Rechts...
   for(int a = 0; a < 3600; a++)
   {
      Vertex2 beg = Vertex2(-1, 0);
      Vertex2 end = Vertex2(1, 0);
      double ang = jm::DegToRad(a / 3600.0);
      beg.Rotate(ang);
      end.Rotate(ang);
      beg.y += 2;
      end.y += 2;
      pnt = jm::ExtensionPointOnLine(Vertex2(-100, 0), Vertex2(100, 2), beg, end);
      if(jm::IsEqual(ang, 0.01999733397))
      {
         TestTrue(IsNaN(pnt.x), "ExtensionPointOnLine fails (6x nan)");
         TestTrue(IsNaN(pnt.y), "ExtensionPointOnLine fails (6y nan)");
      }
      else
      {
         TestEquals(pnt.x, 0.0, "ExtensionPointOnLine fails (6x)");
         TestEquals(pnt.y, 2.0, "ExtensionPointOnLine fails (6y)");
      }
   }

   /* Teste Crosses */
   TestTrue(jm::Crosses(Vertex2(0, 0), Vertex2(1, 1), Vertex2(0, 1), Vertex2(1, 0)), "Crosses fails (1)");
   TestTrue(jm::Crosses(Vertex2(1, 1), Vertex2(0, 0), Vertex2(0, 1), Vertex2(1, 0)), "Crosses fails (2)");
   TestTrue(jm::Crosses(Vertex2(0, 0), Vertex2(1, 1), Vertex2(1, 0), Vertex2(0, 1)), "Crosses fails (3)");
   TestTrue(jm::Crosses(Vertex2(1, 1), Vertex2(0, 0), Vertex2(1, 0), Vertex2(0, 1)), "Crosses fails (4)");

   TestFalse(jm::Crosses(Vertex2(0, 0), Vertex2(1, 0), Vertex2(0, 1), Vertex2(1, 1)), "Crosses fails (5)");
   TestFalse(jm::Crosses(Vertex2(0, 0), Vertex2(1, 0), Vertex2(0.1, 0.5), Vertex2(1.0, 0.5)), "Crosses fails (6)");
   TestFalse(jm::Crosses(Vertex2(0, 0), Vertex2(1, 0), Vertex2(1.0, 0.5), Vertex2(0.1, 0.5)), "Crosses fails (6)");

   TestFalse(jm::Crosses(Vertex2(397, 293), Vertex2(416, 312), Vertex2(379, 272), Vertex2(379, 262)), "Crosses fails (7)");

   #ifdef __APPLE__//macOS, iOS
   timespec end = orwl_gettime();

   long nanos = end.tv_nsec - start.tv_nsec;

   std::cout << "\n\nNANOS: " << nanos << "\n\n";
   #endif


}

