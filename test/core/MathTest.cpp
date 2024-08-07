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

void MathTest::DoTest()
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
}

