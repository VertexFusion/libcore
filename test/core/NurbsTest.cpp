//
//  MatrixTest.cpp
//  jameo
//
//  Created by Uwe Runtemund on 18.04.14.
//  Copyright (c) 2014 Jameo Software. All rights reserved.
//

#include "core/Core.h"
#include "NurbsTest.h"

using namespace jm;

NurbsTest::NurbsTest(): Test()
{
   setName("Test Nurbs");
}

void NurbsTest::testBasisFunctionPartitionOfUnity()
{
        // Grad 2, offene Kurve
    uint32 degree = 2;
    std::vector<Vertex3> cps = { Vertex3(0,0,0),
                                 Vertex3(1,1,0),
                                 Vertex3(2,0,0),
                                 Vertex3(3,1,0),
                                 Vertex3(4,0,0)};
    std::vector<double> knots = {0,0,0,1,2,3,3,3};
    std::vector<double> weights(cps.size(), 1.0);

    Nurbs nurbs(degree,
                cps.data(),
                cps.size(),
                knots.data(),
                knots.size(),
                weights.data(),
                weights.size());

    // Summe der Basisfunktionen muss 1 sein
    double t = knots[degree];
    const double limit = knots[knots.size()-degree-1];
    while( t <= limit)
    {
        double sumN = 0.0;
        for (uint32 i = 0; i < cps.size(); ++i)
        {
            sumN += nurbs.N(i, degree, t);
        }

        testEquals(sumN, 1.0,"sumN wrong");
        t += 0.1;
    }
}

void NurbsTest::testOpenSplineEndpoints()
{
    uint32 degree = 3;
    std::vector<Vertex3> cps = { Vertex3(0,0,0),
                                 Vertex3(1,0,0),
                                 Vertex3(2,0,0),
                                 Vertex3(3,0,0),
                                 Vertex3(4,0,0),
                                 Vertex3(5,0,0)};
    std::vector<double> knots = {0,0,0,0,1,2,3,3,3,3};
    std::vector<double> weights(cps.size(), 1.0);

    Nurbs nurbs(degree,
                cps.data(),
                cps.size(),
                knots.data(),
                knots.size(),
                weights.data(),
                weights.size());

    // Start-Parameter (knot at degree)
    double startParam = knots[degree];
    Vertex3 startPt = nurbs.point(startParam);

    testEquals(startPt.x, cps.front().x,"Start X wrong.");
    testEquals(startPt.y, cps.front().y,"Start Y wrong.");
    testEquals(startPt.z, cps.front().z,"Start Z wrong.");

    // End-Parameter (knot at mKnotCount - degree - 1)
    double endParam = knots[knots.size() - degree - 1];
    Vertex3 endPt = nurbs.point(endParam);

    testEquals(endPt.x, cps.back().x,"End X wrong.");
    testEquals(endPt.y, cps.back().y,"End Y wrong.");
    testEquals(endPt.z, cps.back().z,"End Z wrong.");

    // Check if curve is clamped
    testTrue(nurbs.isClamped(), "Spline should be clamped.");

    // Check if curve is not periodic
    //testFalse(nurbs.isPeriodic(), "Spline should not be periodic.");

    // Check if curve is not closed (start and end points are not the same)
    testFalse(nurbs.isClosed(), "Spline should not be closed.");

}

void NurbsTest::testClosedNonClampedSpline()
{
    uint32 degree = 3;
    std::vector<Vertex3> cps = {
        Vertex3(-0.25, 0, 0),
        Vertex3(-0.25, 0.5, 0),
        Vertex3(0.25, 0.5, 0),
        Vertex3(0.25, 0, 0),
        Vertex3(0.25, -0.5, 0),
        Vertex3(-0.25, -0.5, 0),
        Vertex3(-0.25, 0, 0)
    };
    std::vector<double> knots = {0,0,0,0.5,0.5,0.5,1,1,1};
    std::vector<double> weights = {1, 0.33333, 0.33333, 1, 0.33333, 0.33333, 1};

    Nurbs nurbs(degree,
                cps.data(),
                cps.size(),
                knots.data(),
                knots.size(),
                weights.data(),
                weights.size());

    testFalse(nurbs.isClamped(),"isClamped() return wrong value");
    testTrue(nurbs.isClosed(),"isClosed() return wrong value");

    double startParam = nurbs.start();
    double endParam = nurbs.end();

    Vertex3 pStart = nurbs.point(startParam);
    Vertex3 pEnd = nurbs.point(endParam);

    testEquals(startParam, 0.0, "Start param wrong");
    testEquals(endParam, 1.0, "End param wrong");

    testEquals(pStart.x, -0.25,"Start X wrong.");
    testEquals(pStart.y, 0.0,"Start Y wrong.");
    testEquals(pStart.z, 1.0,"Start Z wrong.");

    // Start und Endpunkt sollten gleich sein (geschlossen)
    testEquals(pStart.x, pEnd.x,"Start==End X wrong.");
    testEquals(pStart.y, pEnd.y,"Start==End Y wrong.");
    testEquals(pStart.z, pEnd.z,"Start==End Z wrong.");
}

void NurbsTest::testPeriodicSpline()
{
    uint32 degree = 3;
    std::vector<Vertex3> cps = {
        Vertex3(0,0,0),
        Vertex3(1,0,0),
        Vertex3(2,0,0),
        Vertex3(3,0,0),
        Vertex3(0,0,0),  // Kontrollpunkt wiederholt für Periodizität
        Vertex3(1,0,0),
        Vertex3(2,0,0)
    };

    // Knotenvector für periodische Kurve (kontrollpunkte + degree +1)
    std::vector<double> knots = {0,1,2,3,4,5,6,7,8,9,10};
    std::vector<double> weights(cps.size(), 1.0);

    Nurbs nurbs(degree,
                cps.data(),
                cps.size(),
                knots.data(),
                knots.size(),
                weights.data(),
                weights.size());

    //testTrue(nurbs.isClosed(),"isClosed() return wrong value");
    //testTrue(nurbs.isPeriodic(),"isPeriodic() return wrong value");

    // Parameterbereich abdecken und prüfen, dass Punkt innerhalb erwartetem Bereich liegt
    double t = knots[degree];
    const double limit = knots[knots.size()-degree-1];
    while(t <= limit)
    {
        Vertex3 p = nurbs.point(t);
        // Für eine Linie auf X-Achse sollte y,z ~0 sein
        testEquals(p.y, 0.0,"py");
        testEquals(p.z, 0.0, "pz");
        testTrue(jm::isGreaterEqual(p.x, 0.0),"px");
        testTrue(jm::isLessEqual(p.x, 3.0),"px");

        t += 0.5;
    }
}

void NurbsTest::testDegree1InterpolatesControlPoints()
{
    uint32 degree = 1;
    std::vector<Vertex3> cps = {
        Vertex3(0,0,0),
        Vertex3(1,1,0),
        Vertex3(2,0,0)};

    std::vector<double> knots = {0.0, 0.0, 0.5, 1.0, 1.0};
    std::vector<double> weights = {1.0,1.0,1.0};

    Nurbs nurbs(degree,
                cps.data(),
                cps.size(),
                knots.data(),
                knots.size(),
                weights.data(),
                weights.size());

    // Test control points
    jm::Vertex3 p1 = nurbs.point(0.0);
    testTrue(p1==cps[0],"Point 0 wrong");

    jm::Vertex3 p2 = nurbs.point(0.5);
    testTrue(p2==cps[1],"Point 1 wrong");

    jm::Vertex3 p3 = nurbs.point(1.0);
    testTrue(p3==cps[2],"Point 2 wrong");

    // Test mid points on line
    jm::Vertex3 p4 = nurbs.point(0.25);
    testTrue(p4==jm::Vertex3(0.5,0.5,0),"Point 3 wrong");

    // Test mid points on line
    jm::Vertex3 p5 = nurbs.point(0.75);
    testTrue(p5==jm::Vertex3(1.5,0.5,0),"Point 4 wrong");
}

void NurbsTest::doTest()
{
    testBasisFunctionPartitionOfUnity();
    testOpenSplineEndpoints();
    //testClosedNonClampedSpline();
    testPeriodicSpline();
    testDegree1InterpolatesControlPoints();
}
