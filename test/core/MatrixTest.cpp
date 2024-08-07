//
//  MatrixTest.cpp
//  jameo
//
//  Created by Uwe Runtemund on 18.04.14.
//  Copyright (c) 2014 Jameo Software. All rights reserved.
//

#include "MatrixTest.h"

#include "VertexTest.h"
#include "core/Vertex2.h"
#include "core/Exception.h"
#include "core/Math.h"
#include "core/Matrix.h"

using namespace jm;

MatrixTest::MatrixTest(): Test()
{
   SetName("Test Matrix");
}

void MatrixTest::DoTest()
{

   Matrix A = Matrix(1, 1);
   TestEquals(A.m, 1, "Matrix.m not 1");
   TestEquals(A.n, 1, "Matrix.n not 1");


   A = Matrix(2, 2);
   TestEquals(A.m, 2, "Matrix.m not 2");
   TestEquals(A.n, 2, "Matrix.n not 2");

   //Leere Matrix muss 0-Einträge haben
   TestEquals(A.get(0, 0), 0.0, "Value not 0");
   TestEquals(A.get(0, 1), 0.0, "Value not 0");
   TestEquals(A.get(1, 0), 0.0, "Value not 0");
   TestEquals(A.get(1, 1), 0.0, "Value not 0");

   //Setze Diags auf 1
   A.diag(1);
   TestEquals(A.get(0, 0), 1.0, "Value not 0");
   TestEquals(A.get(0, 1), 0.0, "Value not 0");
   TestEquals(A.get(1, 0), 0.0, "Value not 0");
   TestEquals(A.get(1, 1), 1.0, "Value not 0");

   A = Matrix(3, 3);
   TestEquals(A.m, 3, "Matrix.m not 3");
   TestEquals(A.n, 3, "Matrix.n not 3");

   //Leere Matrix muss 0-Einträge haben
   TestEquals(A.get(0, 0), 0.0, "Value not 0");
   TestEquals(A.get(0, 1), 0.0, "Value not 0");
   TestEquals(A.get(0, 2), 0.0, "Value not 0");
   TestEquals(A.get(1, 0), 0.0, "Value not 0");
   TestEquals(A.get(1, 1), 0.0, "Value not 0");
   TestEquals(A.get(1, 2), 0.0, "Value not 0");
   TestEquals(A.get(2, 0), 0.0, "Value not 0");
   TestEquals(A.get(2, 1), 0.0, "Value not 0");
   TestEquals(A.get(2, 2), 0.0, "Value not 0");

   A.diag(1);
   TestEquals(A.get(0, 0), 1.0, "Value not 0");
   TestEquals(A.get(0, 1), 0.0, "Value not 0");
   TestEquals(A.get(0, 2), 0.0, "Value not 0");
   TestEquals(A.get(1, 0), 0.0, "Value not 0");
   TestEquals(A.get(1, 1), 1.0, "Value not 0");
   TestEquals(A.get(1, 2), 0.0, "Value not 0");
   TestEquals(A.get(2, 0), 0.0, "Value not 0");
   TestEquals(A.get(2, 1), 0.0, "Value not 0");
   TestEquals(A.get(2, 2), 1.0, "Value not 0");

   //Teste richtige Position
   A = Matrix(3, 3);
   A.set(0, 0, 1);
   A.set(0, 1, 2);
   A.set(0, 2, 3);
   A.set(1, 0, 4);
   A.set(1, 1, 5);
   A.set(1, 2, 6);
   A.set(2, 0, 7);
   A.set(2, 1, 8);
   A.set(2, 2, 9);

   const double* data = A.ref();

   // Index
   // | 0 3 6 |
   // | 1 4 7 |
   // | 2 5 8 |

   TestEquals(data[0], 1.0, "Value not 0 3x3");
   TestEquals(data[3], 2.0, "Value not 1 3x3");
   TestEquals(data[6], 3.0, "Value not 2 3x3");
   TestEquals(data[1], 4.0, "Value not 3 3x3");
   TestEquals(data[4], 5.0, "Value not 4 3x3");
   TestEquals(data[7], 6.0, "Value not 5 3x3");
   TestEquals(data[2], 7.0, "Value not 6 3x3");
   TestEquals(data[5], 8.0, "Value not 7 3x3");
   TestEquals(data[8], 9.0, "Value not 8 3x3");


   A = Matrix(3, 1);
   A.set(0, 0, 1);
   A.set(1, 0, 2);
   A.set(2, 0, 3);
   data = A.ref();
   TestEquals(data[0], 1.0, "Value not 0 3x1");
   TestEquals(data[1], 2.0, "Value not 1 3x1");
   TestEquals(data[2], 3.0, "Value not 2 3x1");

   A = Matrix(4, 4);
   TestEquals(A.m, 4, "Matrix.m not 4");
   TestEquals(A.n, 4, "Matrix.n not 4");

   //Leere Matrix muss 0-Einträge haben
   TestEquals(A.get(0, 0), 0.0, "Value not 0");
   TestEquals(A.get(0, 1), 0.0, "Value not 0");
   TestEquals(A.get(0, 2), 0.0, "Value not 0");
   TestEquals(A.get(0, 3), 0.0, "Value not 0");
   TestEquals(A.get(1, 0), 0.0, "Value not 0");
   TestEquals(A.get(1, 1), 0.0, "Value not 0");
   TestEquals(A.get(1, 2), 0.0, "Value not 0");
   TestEquals(A.get(1, 3), 0.0, "Value not 0");
   TestEquals(A.get(2, 0), 0.0, "Value not 0");
   TestEquals(A.get(2, 1), 0.0, "Value not 0");
   TestEquals(A.get(2, 2), 0.0, "Value not 0");
   TestEquals(A.get(2, 3), 0.0, "Value not 0");
   TestEquals(A.get(3, 0), 0.0, "Value not 0");
   TestEquals(A.get(3, 1), 0.0, "Value not 0");
   TestEquals(A.get(3, 2), 0.0, "Value not 0");
   TestEquals(A.get(3, 3), 0.0, "Value not 0");

   A.diag(1);
   TestEquals(A.get(0, 0), 1.0, "Value not 0");
   TestEquals(A.get(0, 1), 0.0, "Value not 0");
   TestEquals(A.get(0, 2), 0.0, "Value not 0");
   TestEquals(A.get(0, 3), 0.0, "Value not 0");
   TestEquals(A.get(1, 0), 0.0, "Value not 0");
   TestEquals(A.get(1, 1), 1.0, "Value not 0");
   TestEquals(A.get(1, 2), 0.0, "Value not 0");
   TestEquals(A.get(1, 3), 0.0, "Value not 0");
   TestEquals(A.get(2, 0), 0.0, "Value not 0");
   TestEquals(A.get(2, 1), 0.0, "Value not 0");
   TestEquals(A.get(2, 2), 1.0, "Value not 0");
   TestEquals(A.get(2, 3), 0.0, "Value not 0");
   TestEquals(A.get(3, 0), 0.0, "Value not 0");
   TestEquals(A.get(3, 1), 0.0, "Value not 0");
   TestEquals(A.get(3, 2), 0.0, "Value not 0");
   TestEquals(A.get(3, 3), 1.0, "Value not 0");


   //Teste Matrixmultiplikation
   //
   // A =
   // | 3 2 1 |
   // | 1 0 2 |
   A = Matrix(2, 3);
   A.set(0, 0, 3);
   A.set(0, 1, 2);
   A.set(0, 2, 1);
   A.set(1, 0, 1);
   A.set(1, 1, 0);
   A.set(1, 2, 2);

   //
   // B =
   // | 1 2 |
   // | 0 1 |
   // | 4 0 |
   Matrix B = Matrix(3, 2);
   B.set(0, 0, 1);
   B.set(0, 1, 2);
   B.set(1, 0, 0);
   B.set(1, 1, 1);
   B.set(2, 0, 4);
   B.set(2, 1, 0);

   Matrix C = A * B;

   TestEquals(C.m, 2, "Matrix.m not 2");
   TestEquals(C.n, 2, "Matrix.n not 2");

   TestEquals(C.get(0, 0), 7.0, "Value not 7");
   TestEquals(C.get(0, 1), 8.0, "Value not 8");
   TestEquals(C.get(1, 0), 9.0, "Value not 9");
   TestEquals(C.get(1, 1), 2.0, "Value not 2");

   //Teste Matrixmultiplikation mit Zahl
   A = Matrix(2, 2);
   A.set(0, 0, 1);
   A.set(0, 1, 2);
   A.set(1, 0, 3);
   A.set(1, 1, 4);

   C = 4.0 * A;

   TestEquals(C.m, 2, "Matrix.m not 2");
   TestEquals(C.n, 2, "Matrix.n not 2");

   TestEquals(C.get(0, 0), 4.0, "Value not 4");
   TestEquals(C.get(0, 1), 8.0, "Value not 8");
   TestEquals(C.get(1, 0), 12.0, "Value not 12");
   TestEquals(C.get(1, 1), 16.0, "Value not 16");

   //Teste insert
   A = Matrix(3, 3);
   A.set(0, 0, 1);
   A.set(0, 1, 2);
   A.set(0, 2, 3);
   A.set(1, 0, 4);
   A.set(1, 1, 5);
   A.set(1, 2, 6);
   A.set(2, 0, 7);
   A.set(2, 1, 8);
   A.set(2, 2, 9);

   B = Matrix(2, 2);
   B.set(0, 0, 10);
   B.set(0, 1, 11);
   B.set(1, 0, 12);
   B.set(1, 1, 13);

   A.insert(B);
   TestEquals(A.get(0, 0), 10.0, "Value not 10");
   TestEquals(A.get(0, 1), 11.0, "Value not 11");
   TestEquals(A.get(0, 2), 3.0, "Value not 3");
   TestEquals(A.get(1, 0), 12.0, "Value not 12");
   TestEquals(A.get(1, 1), 13.0, "Value not 13");
   TestEquals(A.get(1, 2), 6.0, "Value not 6");
   TestEquals(A.get(2, 0), 7.0, "Value not 7");
   TestEquals(A.get(2, 1), 8.0, "Value not 8");
   TestEquals(A.get(2, 2), 9.0, "Value not 9");


   //
   //Teste Determinanten-Berechnung
   //

   // 2x2
   A = Matrix(2, 2);
   A.set(0, 0, 3);
   A.set(0, 1, 2);
   A.set(1, 0, 1);
   A.set(1, 1, 1);
   double det = 0;
   A.det(det);
   TestEquals(det, 1.0, "Det not 2");

   //3x3
   A = Matrix(3, 3);
   A.set(0, 0, 0);
   A.set(0, 1, 1);
   A.set(0, 2, 2);
   A.set(1, 0, 3);
   A.set(1, 1, 2);
   A.set(1, 2, 1);
   A.set(2, 0, 1);
   A.set(2, 1, 1);
   A.set(2, 2, 0);
   A.det(det);
   TestEquals(det, 3.0, "Det not 3");

   //4x4
   A = Matrix(4, 4);
   A.set(0, 0, 5);
   A.set(0, 1, 0);
   A.set(0, 2, 3);
   A.set(0, 3, -1);
   A.set(1, 0, 3);
   A.set(1, 1, 0);
   A.set(1, 2, 0);
   A.set(1, 3, 4);
   A.set(2, 0, -1);
   A.set(2, 1, 2);
   A.set(2, 2, 4);
   A.set(2, 3, -2);
   A.set(3, 0, 1);
   A.set(3, 1, 0);
   A.set(3, 2, 0);
   A.set(3, 3, 5);
   A.det(det);
   TestEquals(det, 66.0, "Det not 66");

   //Teste 3x3 Matrixinvertierung
   A = Matrix(3, 3);
   A.set(0, 0, 5);
   A.set(0, 1, 1);
   A.set(0, 2, -6);
   A.set(1, 0, 1);
   A.set(1, 1, 1);
   A.set(1, 2, -1);
   A.set(2, 0, 2);
   A.set(2, 1, -9);
   A.set(2, 2, -3);

   A.inverse();
   TestEquals(A.get(0, 0), -12.0 / 7.0, "Value not -12/7");
   TestEquals(A.get(0, 1), 57.0 / 7.0, "Value not 57/7");
   TestEquals(A.get(0, 2), 5.0 / 7.0, "Value not 5/7");
   TestEquals(A.get(1, 0), 1.0 / 7.0, "Value not 1/7");
   TestEquals(A.get(1, 1), -3.0 / 7.0, "Value not -3/7");
   TestEquals(A.get(1, 2), -1.0 / 7.0, "Value not -1/7");
   TestEquals(A.get(2, 0), -11.0 / 7.0, "Value not -11/7");
   TestEquals(A.get(2, 1), 47.0 / 7.0, "Value not 47/7");
   TestEquals(A.get(2, 2), 4.0 / 7.0, "Value not 4/7");

   //Teste 2x2 Matrixinvertierung
   A = Matrix(2, 2);
   A.set(0, 0, 5);
   A.set(0, 1, -2);
   A.set(1, 0, 4);
   A.set(1, 1, 7);

   A.inverse();
   TestEquals(A.get(0, 0), 7.0 / 43.0, "Value not 7/43");
   TestEquals(A.get(0, 1), 2.0 / 43.0, "Value not 2/43");
   TestEquals(A.get(1, 0), -4.0 / 43.0, "Value not -4/43");
   TestEquals(A.get(1, 1), 5.0 / 43.0, "Value not 5/43");


   //Teste 4x4 Matrixinvertierung
   A = Matrix(4, 4);
   A.set(0, 0, -1);
   A.set(0, 1, -3);
   A.set(0, 2, 1);
   A.set(0, 3, -4);
   A.set(1, 0, -6);
   A.set(1, 1, 4);
   A.set(1, 2, 3);
   A.set(1, 3, 3);
   A.set(2, 0, -1);
   A.set(2, 1, 1);
   A.set(2, 2, 4);
   A.set(2, 3, 0);
   A.set(3, 0, -4);
   A.set(3, 1, 1);
   A.set(3, 2, 2);
   A.set(3, 3, 0);

   A.det(det);
   TestEquals(det, 1.0, "Det not 1");

   A.inverse();
   TestEquals(A.get(0, 0), -6.0, "Value not -6");
   TestEquals(A.get(0, 1), -8.0, "Value not -8");
   TestEquals(A.get(0, 2), 1.0, "Value not 1");
   TestEquals(A.get(0, 3), 13.0, "Value not 13");
   TestEquals(A.get(1, 0), -42.0, "Value not -42");
   TestEquals(A.get(1, 1), -56.0, "Value not -56");
   TestEquals(A.get(1, 2), 6.0, "Value not 6");
   TestEquals(A.get(1, 3), 93.0, "Value not 93");
   TestEquals(A.get(2, 0), 9.0, "Value not 9");
   TestEquals(A.get(2, 1), 12.0, "Value not 12");
   TestEquals(A.get(2, 2), -1.0, "Value not -1");
   TestEquals(A.get(2, 3), -20.0, "Value not -20");
   TestEquals(A.get(3, 0), 35.0, "Value not 35");
   TestEquals(A.get(3, 1), 47.0, "Value not 47");
   TestEquals(A.get(3, 2), -5.0, "Value not 5");
   TestEquals(A.get(3, 3), -78.0, "Value not -78");

   //
   //Teste Matrix-Norm
   //

   // 2x3
   A = Matrix(2, 3);
   A.set(0, 0, 1);
   A.set(0, 1, -2);
   A.set(0, 2, -3);
   A.set(1, 0, 2);
   A.set(1, 1, 3);
   A.set(1, 2, 1);

   double norm = A.norm(jm::kMatrixNorm1);
   TestEquals(norm, 5.0, "Norm_1 not 5");

   norm = A.norm(jm::kMatrixNormInf);
   TestEquals(norm, 6.0, "Norm_inf not 6");


}
