//
//  MathTest.cpp
//  tornado
//
//  Created by Uwe Runtemund on 06.11.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "MathTest.h"

#include "core/Math.h"
#include "core/Exception.h"
#include "core/System.h"

using namespace jm;

MathTest::MathTest(): Test()
{
   SetName("Test Math");
}

void MathTest::doTest()
{
   double values[7] = {-10E+6, -12.3456789, -2, 0, 2, 12.3456789, 10E+6};

   std::cout << "float machine epsilon: " << floatMaschineEpsilon() << std::endl;
   std::cout << "double machine epsilon: " << doubleMaschineEpsilon() << std::endl;

   // Test signed values
   uint8 ui8 = 27;
   TestTrue(ui8 == 27, "uint8 == 27 fails");
   TestFalse(ui8 != 27, "uint8 != 27 fails");

   int8 i8 = 19;
   TestTrue(i8 == 19, "int8 == 19 fails");
   TestFalse(i8 != 19, "int8 != 19 fails");
   i8 = -19;
   TestTrue(i8 == -19, "int8 == -19 fails");
   TestFalse(i8 != -19, "int8 != -19 fails");

   for(uint32 a = 0; a < 5; a++)
   {
      double value = values[a];

      //
      // Frühere Tests haben hier bits manipuliert und genau die Grenze getestet. Das führte aber bei
      // unterschiedlichen Compilern, Betriebssystemen und sogar Zahlen zu nicht reproduzierbaren Ergebnissen
      // Es wird daher nun nur noch über RESABS geprüft.


      double smaller = RESABS * 0.01;
      double bigger = RESABS * 1.01;

      double testEqual1 = value + smaller;
      double testEqual2 = value - smaller;

      double testNotEqual1 = value + bigger;
      double testNotEqual2 = value - bigger;

      //Teste IsEqual
      TestTrue(isEqual(value, testEqual1), "IsEqual() fails (1)"); //Sind gleich
      TestTrue(isEqual(value, testEqual2), "IsEqual() fails (2)"); //Sind gleich
      TestFalse(isEqual(value, testNotEqual1),
                "IsEqual() fails (3)"); //Sind ungleich (Testwert ist zu groß)
      TestFalse(isEqual(value, testNotEqual2),
                "IsEqual() fails (4)"); //Sind ungleich (Testwert ist zu klein)

      //Teste IsNotEqual - Ergebnisse müssen genau anders herum sein.
      TestFalse(isNotEqual(value, testEqual1), "IsNotEqual() fails (1)");
      TestFalse(isNotEqual(value, testEqual2), "IsNotEqual() fails (2)");
      TestTrue(isNotEqual(value, testNotEqual1), "IsNotEqual() fails (3)");
      TestTrue(isNotEqual(value, testNotEqual2), "IsNotEqual() fails (4)");

      //Teste Less
      TestFalse(isLess(testEqual1, value), "IsLess() fails (1)"); //Wert ist ganz klar gleich
      TestFalse(isLess(testEqual2, value), "IsLess() fails (2)"); //Wert ist ganz klar gleich
      TestFalse(isLess(testNotEqual1, value), "IsLess() fails (3)"); //Wert ist ganz klar größer
      TestTrue(isLess(testNotEqual2, value), "IsLess() fails (4)"); //Wert ist ganz klar kleiner

      //Teste Greater
      TestFalse(isGreater(testEqual1, value), "IsGreater() fails (1)"); //Wert ist ganz klar gleich
      TestFalse(isGreater(testEqual2, value), "IsGreater() fails (2)"); //Wert ist ganz klar gleich
      TestTrue(isGreater(testNotEqual1, value), "IsGreater() fails (3)"); //Wert ist ganz klar größer
      TestFalse(isGreater(testNotEqual2, value), "IsGreater() fails (4)"); //Wert ist ganz klar kleiner

      //Teste Less equal
      TestTrue(isLessEqual(testEqual1, value), "IsLessEqual() fails (1)"); //Wert ist ganz klar gleich
      TestTrue(isLessEqual(testEqual2, value), "IsLessEqual() fails (2)"); //Wert ist ganz klar gleich
      TestFalse(isLessEqual(testNotEqual1, value),
                "IsLessEqual() fails (3)"); //Wert ist ganz klar größer
      TestTrue(isLessEqual(testNotEqual2, value), "IsLessEqual() fails (4)"); //Wert ist ganz klar kleiner

      //Teste Greater equal
      TestTrue(isGreaterEqual(testEqual1, value),
               "IsGreaterEqual() fails (1)"); //Wert ist ganz klar gleich
      TestTrue(isGreaterEqual(testEqual2, value),
               "IsGreaterEqual() fails (2)"); //Wert ist ganz klar gleich
      TestTrue(isGreaterEqual(testNotEqual1, value),
               "IsGreaterEqual() fails (3)"); //Wert ist ganz klar größer
      TestFalse(isGreaterEqual(testNotEqual2, value),
                "IsGreaterEqual() fails (4)"); //Wert ist ganz klar kleiner

      //Teste Interpolate
      double begin = 2.0;
      double end = 4.0;

      TestEquals(interpolate(begin, end, 0.0), 2.0, "Interpolate fails (1)");
      TestEquals(interpolate(begin, end, 0.5), 3.0, "Interpolate fails (2)");
      TestEquals(interpolate(begin, end, 1.0), 4.0, "Interpolate fails (3)");

      TestEquals(interpolate(10, 20, begin, end, 2.0), 10.0, "Interpolate fails (4)");
      TestEquals(interpolate(10, 20, begin, end, 3.0), 15.0, "Interpolate fails (5)");
      TestEquals(interpolate(10, 20, begin, end, 4.0), 20.0, "Interpolate fails (6)");

   }


   // Test degToRad function
   TestEquals(jm::degToRad(180), M_PI, "degToRad(180) != M_PI");
   TestEquals(jm::degToRad(90), M_PI / 2, "degToRad(90) != M_PI / 2");

   // Test radToDeg function
   TestEquals(jm::radToDeg(M_PI), 180.0, "radToDeg(M_PI) != 180");
   TestEquals(jm::radToDeg(M_PI / 2), 90.0, "radToDeg(M_PI / 2) != 90");

   // Test sign function
   TestEquals(jm::sign(10),1, "sign(10) != 1");
   TestEquals(jm::sign(-10),-1, "sign(-10) != -1");
   TestEquals(jm::sign(0),0, "sign(0) != 0");

   // Test round function
   TestEquals(jm::round(10.5), (int64)11,"round(10.5) != 11");
   TestEquals(jm::round(10.4), (int64)10,"round(10.4) != 10");
   TestEquals(jm::round(-10.6), (int64)-11,"round(-10.6) != -11");
   TestEquals(jm::round(-2.5), (int64)-3,"round(-2.5) != -3");
   TestEquals(jm::round(-2.1), (int64)-2,"round(-2.1) != -2");

   // Test roundFrac function
   TestEquals(jm::roundFrac(10.555, 2), 10.56f,"roundFrac(10.555, 2) != 10.56");
   TestEquals(jm::roundFrac(-10.554, 2), -10.55f,"roundFrac(-10.554, 2) != -10.55");

   // Test isNaN function
   TestEquals(jm::isNaN(NAN), true, "isNaN(NAN) should be true");
   TestEquals(jm::isNaN(0.0), false, "isNaN(0.0) should be false");
   TestEquals(jm::isNaN(1.0), false, "isNaN(1.0) should be false");

   // Test swap for double
   double a = 1.0, b = 2.0;
   jm::swap(a, b);
   TestEquals(a, 2.0, "SwapDouble: a should be 2.0 after swap");
   TestEquals(b, 1.0, "SwapDouble: b should be 1.0 after swap");

   // Test swap for int32
   int32 c = 1, d = 2;
   jm::swap(c, d);
   TestEquals(c, 2, "SwapInt32: c should be 2 after swap");
   TestEquals(d, 1, "SwapInt32: d should be 1 after swap");

   // Test swap for uint32
   uint32 e = 1, f = 2;
   jm::swap(e, f);
   TestEquals(e, 2u, "SwapUInt32: e should be 2 after swap");
   TestEquals(f, 1u, "SwapUInt32: f should be 1 after swap");

   // Test swap for uint16
   uint16 g = 1, h = 2;
   jm::swap(g, h);
   TestEquals(g, 2u, "SwapUInt16: g should be 2 after swap");
   TestEquals(h, 1u, "SwapUInt16: h should be 1 after swap");

   // Test swap for uint8
   uint8 i = 1, j = 2;
   jm::swap(i, j);
   TestEquals(i, 2u, "SwapUInt16: g should be 2 after swap");
   TestEquals(j, 1u, "SwapUInt16: h should be 1 after swap");

   // Test random function
   TestEquals(jm::random() >= 0.0 && jm::random() <= 1.0, true, "random() should return a value between 0.0 and 1.0");

   // Test random with range function
   int32 randomInRange = jm::random(10, 20);
   TestEquals(randomInRange >= 10 && randomInRange <= 20, true, "random(10, 20) should return a value between 10 and 20");

   // Test probability function
   // This test might be a bit tricky due to the randomness, but we can test edge cases
   TestEquals(jm::probability(0.0), false, "probability(0.0) should always return false");
   TestEquals(jm::probability(100.0), true, "probability(100.0) should always return true");

   // Test interpolate function for float
   float interpolatedFloat = jm::interpolate(0.0f, 10.0f, 0.5f);
   TestEquals(interpolatedFloat, 5.0f, "interpolate(0.0f, 10.0f, 0.5f) should return 5.0f");

   // Test interpolate function for double
   double interpolatedDouble = jm::interpolate(0.0, 10.0, 0.5);
   TestEquals(interpolatedDouble, 5.0, "interpolate(0.0, 10.0, 0.5) should return 5.0");

   // Test interpolate with position function
   double interpolatedPosition = jm::interpolate(0.0, 10.0, 0.0, 10.0, 5.0);
   TestEquals(interpolatedPosition, 5.0, "interpolate(0.0, 10.0, 0.0, 10.0, 5.0) should return 5.0");

   // Test powerOf2 function
   TestEquals(jm::powerOf2(1), true, "powerOf2(1) should return true");
   TestEquals(jm::powerOf2(2), true, "powerOf2(2) should return true");
   TestEquals(jm::powerOf2(3), false, "powerOf2(3) should return false");
   TestEquals(jm::powerOf2(4), true, "powerOf2(4) should return true");
   TestEquals(jm::powerOf2(0), false, "powerOf2(0) should return false");

   // Test ceilPowerOf2 function
   TestEquals(jm::ceilPowerOf2(3), 4u, "ceilPowerOf2(3) should return 4");
   TestEquals(jm::ceilPowerOf2(8), 8u, "ceilPowerOf2(8) should return 8");
   TestEquals(jm::ceilPowerOf2(9), 16u, "ceilPowerOf2(9) should return 16");

   // Test doubleMaschineEpsilon function
   // Note: This test assumes the function calculates the machine epsilon correctly for double precision.
   double expectedDoubleEpsilon = std::numeric_limits<double>::epsilon();
   TestEquals(jm::doubleMaschineEpsilon(), expectedDoubleEpsilon, "doubleMaschineEpsilon() should return the correct machine epsilon for double");

   // Test floatMaschineEpsilon function
   // Note: This test assumes the function calculates the machine epsilon correctly for float precision.
   float expectedFloatEpsilon = std::numeric_limits<float>::epsilon();
   TestEquals(jm::floatMaschineEpsilon(), expectedFloatEpsilon, "floatMaschineEpsilon() should return the correct machine epsilon for float");

   // Test divFloor function
   TestEquals(jm::divFloor(10, 3), 3l, "divFloor(10, 3) should return 3");
   TestEquals(jm::divFloor(-10, 3), -4l, "divFloor(-10, 3) should return -4");
   TestEquals(jm::divFloor(10, -3), -4l, "divFloor(10, -3) should return -4");
   TestEquals(jm::divFloor(-10, -3), 3l, "divFloor(-10, -3) should return 3");
   TestEquals(jm::divFloor(10, 5), 2l, "divFloor(10, 5) should return 2");

   // Test modFloor function
    TestEquals(jm::modFloor(10, 3), 1L,"modFloor(10, 3) should return 1");
    TestEquals(jm::modFloor(-10, 3), 2L,"modFloor(-10, 3) should return 2");
    TestEquals(jm::modFloor(10, -3), -2L,"modFloor(10, -3) should return -2");
    TestEquals(jm::modFloor(-10, -3), -1L,"modFloor(-10, -3) should return -1");
    TestEquals(jm::modFloor(0, 3), 0L,"modFloor(0, 3) should return 0");
    TestEquals(jm::modFloor(10, 0), 0L,"modFloor(10, 0) should return 0");
    TestEquals(jm::modFloor(0, 0), 0L,"modFloor(0, 0) should return 0");
}

