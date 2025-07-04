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
   setName("Test Matrix");
}

void MatrixTest::doTest()
{

   Matrix A = Matrix(1, 1);
   testEquals(A.rows(), 1UL, "Matrix.rows() not 1");
   testEquals(A.cols(), 1UL, "Matrix.cols() not 1");


   A = Matrix(2, 2);
   testEquals(A.rows(), 2UL, "Matrix.rows() not 2");
   testEquals(A.cols(), 2UL, "Matrix.cols() not 2");

   //Leere Matrix muss 0-Einträge haben
   testEquals(A.get(0, 0), 0.0, "Value not 0");
   testEquals(A.get(0, 1), 0.0, "Value not 0");
   testEquals(A.get(1, 0), 0.0, "Value not 0");
   testEquals(A.get(1, 1), 0.0, "Value not 0");

   //Setze Diags auf 1
   A.diag(1);
   testEquals(A.get(0, 0), 1.0, "Value not 0");
   testEquals(A.get(0, 1), 0.0, "Value not 0");
   testEquals(A.get(1, 0), 0.0, "Value not 0");
   testEquals(A.get(1, 1), 1.0, "Value not 0");

   A = Matrix(3, 3);
   testEquals(A.rows(), 3UL, "Matrix.rows() not 3");
   testEquals(A.cols(), 3UL, "Matrix.cols() not 3");

   //Leere Matrix muss 0-Einträge haben
   testEquals(A.get(0, 0), 0.0, "Value not 0");
   testEquals(A.get(0, 1), 0.0, "Value not 0");
   testEquals(A.get(0, 2), 0.0, "Value not 0");
   testEquals(A.get(1, 0), 0.0, "Value not 0");
   testEquals(A.get(1, 1), 0.0, "Value not 0");
   testEquals(A.get(1, 2), 0.0, "Value not 0");
   testEquals(A.get(2, 0), 0.0, "Value not 0");
   testEquals(A.get(2, 1), 0.0, "Value not 0");
   testEquals(A.get(2, 2), 0.0, "Value not 0");

   A.diag(1);
   testEquals(A.get(0, 0), 1.0, "Value not 0");
   testEquals(A.get(0, 1), 0.0, "Value not 0");
   testEquals(A.get(0, 2), 0.0, "Value not 0");
   testEquals(A.get(1, 0), 0.0, "Value not 0");
   testEquals(A.get(1, 1), 1.0, "Value not 0");
   testEquals(A.get(1, 2), 0.0, "Value not 0");
   testEquals(A.get(2, 0), 0.0, "Value not 0");
   testEquals(A.get(2, 1), 0.0, "Value not 0");
   testEquals(A.get(2, 2), 1.0, "Value not 0");

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

   testEquals(data[0], 1.0, "Value not 0 3x3");
   testEquals(data[3], 2.0, "Value not 1 3x3");
   testEquals(data[6], 3.0, "Value not 2 3x3");
   testEquals(data[1], 4.0, "Value not 3 3x3");
   testEquals(data[4], 5.0, "Value not 4 3x3");
   testEquals(data[7], 6.0, "Value not 5 3x3");
   testEquals(data[2], 7.0, "Value not 6 3x3");
   testEquals(data[5], 8.0, "Value not 7 3x3");
   testEquals(data[8], 9.0, "Value not 8 3x3");


   A = Matrix(3, 1);
   A.set(0, 0, 1);
   A.set(1, 0, 2);
   A.set(2, 0, 3);
   data = A.ref();
   testEquals(data[0], 1.0, "Value not 0 3x1");
   testEquals(data[1], 2.0, "Value not 1 3x1");
   testEquals(data[2], 3.0, "Value not 2 3x1");

   A = Matrix(4, 4);
   testEquals(A.rows(), 4UL, "Matrix.rows() not 4");
   testEquals(A.cols(), 4UL, "Matrix.cols() not 4");

   //Leere Matrix muss 0-Einträge haben
   testEquals(A.get(0, 0), 0.0, "Value not 0");
   testEquals(A.get(0, 1), 0.0, "Value not 0");
   testEquals(A.get(0, 2), 0.0, "Value not 0");
   testEquals(A.get(0, 3), 0.0, "Value not 0");
   testEquals(A.get(1, 0), 0.0, "Value not 0");
   testEquals(A.get(1, 1), 0.0, "Value not 0");
   testEquals(A.get(1, 2), 0.0, "Value not 0");
   testEquals(A.get(1, 3), 0.0, "Value not 0");
   testEquals(A.get(2, 0), 0.0, "Value not 0");
   testEquals(A.get(2, 1), 0.0, "Value not 0");
   testEquals(A.get(2, 2), 0.0, "Value not 0");
   testEquals(A.get(2, 3), 0.0, "Value not 0");
   testEquals(A.get(3, 0), 0.0, "Value not 0");
   testEquals(A.get(3, 1), 0.0, "Value not 0");
   testEquals(A.get(3, 2), 0.0, "Value not 0");
   testEquals(A.get(3, 3), 0.0, "Value not 0");

   A.diag(1);
   testEquals(A.get(0, 0), 1.0, "Value not 0");
   testEquals(A.get(0, 1), 0.0, "Value not 0");
   testEquals(A.get(0, 2), 0.0, "Value not 0");
   testEquals(A.get(0, 3), 0.0, "Value not 0");
   testEquals(A.get(1, 0), 0.0, "Value not 0");
   testEquals(A.get(1, 1), 1.0, "Value not 0");
   testEquals(A.get(1, 2), 0.0, "Value not 0");
   testEquals(A.get(1, 3), 0.0, "Value not 0");
   testEquals(A.get(2, 0), 0.0, "Value not 0");
   testEquals(A.get(2, 1), 0.0, "Value not 0");
   testEquals(A.get(2, 2), 1.0, "Value not 0");
   testEquals(A.get(2, 3), 0.0, "Value not 0");
   testEquals(A.get(3, 0), 0.0, "Value not 0");
   testEquals(A.get(3, 1), 0.0, "Value not 0");
   testEquals(A.get(3, 2), 0.0, "Value not 0");
   testEquals(A.get(3, 3), 1.0, "Value not 0");


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

   testEquals(C.rows(), 2UL, "Matrix.rows() not 2");
   testEquals(C.cols(), 2UL, "Matrix.cols() not 2");

   testEquals(C.get(0, 0), 7.0, "Value not 7");
   testEquals(C.get(0, 1), 8.0, "Value not 8");
   testEquals(C.get(1, 0), 9.0, "Value not 9");
   testEquals(C.get(1, 1), 2.0, "Value not 2");

   //Teste Matrixmultiplikation mit Zahl
   A = Matrix(2, 2);
   A.set(0, 0, 1);
   A.set(0, 1, 2);
   A.set(1, 0, 3);
   A.set(1, 1, 4);

   C = 4.0 * A;

   testEquals(C.rows(), 2UL, "Matrix.rows() not 2");
   testEquals(C.cols(), 2UL, "Matrix.cols() not 2");

   testEquals(C.get(0, 0), 4.0, "Value not 4");
   testEquals(C.get(0, 1), 8.0, "Value not 8");
   testEquals(C.get(1, 0), 12.0, "Value not 12");
   testEquals(C.get(1, 1), 16.0, "Value not 16");

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
   testEquals(A.get(0, 0), 10.0, "Value not 10");
   testEquals(A.get(0, 1), 11.0, "Value not 11");
   testEquals(A.get(0, 2), 3.0, "Value not 3");
   testEquals(A.get(1, 0), 12.0, "Value not 12");
   testEquals(A.get(1, 1), 13.0, "Value not 13");
   testEquals(A.get(1, 2), 6.0, "Value not 6");
   testEquals(A.get(2, 0), 7.0, "Value not 7");
   testEquals(A.get(2, 1), 8.0, "Value not 8");
   testEquals(A.get(2, 2), 9.0, "Value not 9");


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
   testEquals(det, 1.0, "Det not 2");

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
   testEquals(det, 3.0, "Det not 3");

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
   testEquals(det, 66.0, "Det not 66");

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
   testEquals(A.get(0, 0), -12.0 / 7.0, "Value not -12/7");
   testEquals(A.get(0, 1), 57.0 / 7.0, "Value not 57/7");
   testEquals(A.get(0, 2), 5.0 / 7.0, "Value not 5/7");
   testEquals(A.get(1, 0), 1.0 / 7.0, "Value not 1/7");
   testEquals(A.get(1, 1), -3.0 / 7.0, "Value not -3/7");
   testEquals(A.get(1, 2), -1.0 / 7.0, "Value not -1/7");
   testEquals(A.get(2, 0), -11.0 / 7.0, "Value not -11/7");
   testEquals(A.get(2, 1), 47.0 / 7.0, "Value not 47/7");
   testEquals(A.get(2, 2), 4.0 / 7.0, "Value not 4/7");

   //Teste 2x2 Matrixinvertierung
   A = Matrix(2, 2);
   A.set(0, 0, 5);
   A.set(0, 1, -2);
   A.set(1, 0, 4);
   A.set(1, 1, 7);

   A.inverse();
   testEquals(A.get(0, 0), 7.0 / 43.0, "Value not 7/43");
   testEquals(A.get(0, 1), 2.0 / 43.0, "Value not 2/43");
   testEquals(A.get(1, 0), -4.0 / 43.0, "Value not -4/43");
   testEquals(A.get(1, 1), 5.0 / 43.0, "Value not 5/43");


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
   testEquals(det, 1.0, "Det not 1");

   A.inverse();
   testEquals(A.get(0, 0), -6.0, "Value not -6");
   testEquals(A.get(0, 1), -8.0, "Value not -8");
   testEquals(A.get(0, 2), 1.0, "Value not 1");
   testEquals(A.get(0, 3), 13.0, "Value not 13");
   testEquals(A.get(1, 0), -42.0, "Value not -42");
   testEquals(A.get(1, 1), -56.0, "Value not -56");
   testEquals(A.get(1, 2), 6.0, "Value not 6");
   testEquals(A.get(1, 3), 93.0, "Value not 93");
   testEquals(A.get(2, 0), 9.0, "Value not 9");
   testEquals(A.get(2, 1), 12.0, "Value not 12");
   testEquals(A.get(2, 2), -1.0, "Value not -1");
   testEquals(A.get(2, 3), -20.0, "Value not -20");
   testEquals(A.get(3, 0), 35.0, "Value not 35");
   testEquals(A.get(3, 1), 47.0, "Value not 47");
   testEquals(A.get(3, 2), -5.0, "Value not 5");
   testEquals(A.get(3, 3), -78.0, "Value not -78");

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

   double norm = A.norm(jm::MatrixNorm::kNorm1);
   testEquals(norm, 5.0, "Norm_1 not 5");

   norm = A.norm(jm::MatrixNorm::kNormInf);
   testEquals(norm, 6.0, "Norm_inf not 6");


   //
   // Test rotation matrix
   //
   jm::Vertex3 xAxis(1, 0, 0);
   jm::Vertex3 yAxis(0, 1, 0);

   // Align X to y

   jm::Matrix rotationMatrix = Matrix::generate3x3RotationMatrix(xAxis, yAxis);

   // Apply the rotation matrix to the x-axis
   jm::Vertex3 rotatedXAxis = rotationMatrix * xAxis;

   // Check if the rotated x-axis aligns with the y-axis
   testEquals(rotatedXAxis.x, 0.0, "rotatedXAxis.x not 0");
   testEquals(rotatedXAxis.y, 1.0, "rotatedXAxis.y not 1");
   testEquals(rotatedXAxis.z, 0.0, "rotatedXAxis.z not 0");

   // Align X to Z

   jm::Vertex3 zAxis(0, 0, 1);

   rotationMatrix = Matrix::generate3x3RotationMatrix(xAxis, zAxis);

   // Apply the rotation matrix to the x-axis
   rotatedXAxis = rotationMatrix * xAxis;

   // Check if the rotated x-axis aligns with the z-axis
   testEquals(rotatedXAxis.x, 0.0, "rotatedXAxis.x not 0");
   testEquals(rotatedXAxis.y, 0.0, "rotatedXAxis.y not 0");
   testEquals(rotatedXAxis.z, 1.0, "rotatedXAxis.z not 1");

   // Align arbitrary

   jm::Vertex3 u(1, 2, 3);
   jm::Vertex3 v(4, 5, 6);

   rotationMatrix = Matrix::generate3x3RotationMatrix(u, v);

   // Apply the rotation matrix to the vector u
   jm::Vertex3 rotatedU = rotationMatrix * u;

   // Normalize both vectors for comparison
   jm::Vertex3 v_norm = v.normalized();
   jm::Vertex3 rotatedU_norm = rotatedU.normalized();

   // Check if the rotated u aligns with v
   testEquals(rotatedU_norm.x, v_norm.x, "rotatedU_norm.x not v_norm.x");
   testEquals(rotatedU_norm.y, v_norm.y, "rotatedU_norm.y not v_norm.y");
   testEquals(rotatedU_norm.z, v_norm.z, "rotatedU_norm.z not v_norm.z");

   //
   // 180 degree rotation
   //

   // Define the x-axis
   xAxis = jm::Vertex3(1, 0, 0);

   // Define the axis of rotation (y-axis in this case)
   yAxis = jm::Vertex3(-1, 0, 0);

   // Define the expected result after 180-degree rotation around the y-axis
   jm::Vertex3 expectedRotatedXAxis(-1, 0, 0);

   // Create a rotation matrix for 180 degrees (π radians)
   rotationMatrix = Matrix::generate3x3RotationMatrix(xAxis, yAxis);

   // Apply the rotation matrix to the x-axis
   rotatedXAxis = rotationMatrix * xAxis;

   // Check if the rotated x-axis aligns with the expected result
   testEquals(rotatedXAxis.x, expectedRotatedXAxis.x, "rotatedXAxis.x not -1");
   testEquals(rotatedXAxis.y, expectedRotatedXAxis.y, "rotatedXAxis.y not 0");
   testEquals(rotatedXAxis.z, expectedRotatedXAxis.z, "rotatedXAxis.z not 0");

   constructors();
}

void MatrixTest::constructors()
{
   // Test default constructor
   Matrix A;
   testEquals(A.rows(), 0UL, "Matrix.rows() not 0");
   testEquals(A.cols(), 0UL, "Matrix.cols() not 0");

   // Test constructor with size
   A = Matrix(3, 4);
   testEquals(A.rows(), 3UL, "Matrix.rows() not 3");
   testEquals(A.cols(), 4UL, "Matrix.cols() not 4");

   testEquals(A.get(0, 0), 0.0, "Value not 0");
   testEquals(A.get(0, 1), 0.0, "Value not 0");
   testEquals(A.get(0, 2), 0.0, "Value not 0");
   testEquals(A.get(0, 3), 0.0, "Value not 0");
   testEquals(A.get(1, 0), 0.0, "Value not 0");
   testEquals(A.get(1, 1), 0.0, "Value not 0");
   testEquals(A.get(1, 2), 0.0, "Value not 0");
   testEquals(A.get(1, 3), 0.0, "Value not 0");
   testEquals(A.get(2, 0), 0.0, "Value not 0");
   testEquals(A.get(2, 1), 0.0, "Value not 0");
   testEquals(A.get(2, 2), 0.0, "Value not 0");
   testEquals(A.get(2, 3), 0.0, "Value not 0");

   A.set(0, 0, 1);
   A.set(0, 1, 2);
   A.set(0, 2, 3);
   A.set(0, 3, 4);
   A.set(1, 0, 5);
   A.set(1, 1, 6);
   A.set(1, 2, 7);
   A.set(1, 3, 8);
   A.set(2, 0, 9);
   A.set(2, 1, 10);
   A.set(2, 2, 11);
   A.set(2, 3, 12);
   testEquals(A.get(0, 0), 1.0, "Value not 1");
   testEquals(A.get(0, 1), 2.0, "Value not 2");
   testEquals(A.get(0, 2), 3.0, "Value not 3");
   testEquals(A.get(0, 3), 4.0, "Value not 4");
   testEquals(A.get(1, 0), 5.0, "Value not 5");
   testEquals(A.get(1, 1), 6.0, "Value not 6");
   testEquals(A.get(1, 2), 7.0, "Value not 7");
   testEquals(A.get(1, 3), 8.0, "Value not 8");
   testEquals(A.get(2, 0), 9.0, "Value not 9");
   testEquals(A.get(2, 1), 10.0, "Value not 10");
   testEquals(A.get(2, 2), 11.0, "Value not 11");
   testEquals(A.get(2, 3), 12.0, "Value not 12");

   // Test copy constructor
   Matrix B = A;
   testEquals(B.rows(), A.rows(), "Matrix.rows() not equal");
   testEquals(B.cols(), A.cols(), "Matrix.cols() not equal");
   testEquals(B.get(0, 0), A.get(0, 0), "Value not equal");
   testEquals(B.get(0, 1), A.get(0, 1), "Value not equal");
   testEquals(B.get(0, 2), A.get(0, 2), "Value not equal");
   testEquals(B.get(0, 3), A.get(0, 3), "Value not equal");
   testEquals(B.get(1, 0), A.get(1, 0), "Value not equal");
   testEquals(B.get(1, 1), A.get(1, 1), "Value not equal");
   testEquals(B.get(1, 2), A.get(1, 2), "Value not equal");
   testEquals(B.get(1, 3), A.get(1, 3), "Value not equal");
   testEquals(B.get(2, 0), A.get(2, 0), "Value not equal");
   testEquals(B.get(2, 1), A.get(2, 1), "Value not equal");
   testEquals(B.get(2, 2), A.get(2, 2), "Value not equal");
   testEquals(B.get(2, 3), A.get(2, 3), "Value not equal");

   // Test reference constructor
   B = Matrix(&A);
   testEquals(B.rows(), A.rows(), "Matrix.rows() not equal");
   testEquals(B.cols(), A.cols(), "Matrix.cols() not equal");
   testEquals(B.get(0, 0), A.get(0, 0), "Value not equal");
   testEquals(B.get(0, 1), A.get(0, 1), "Value not equal");
   testEquals(B.get(0, 2), A.get(0, 2), "Value not equal");
   testEquals(B.get(0, 3), A.get(0, 3), "Value not equal");
   testEquals(B.get(1, 0), A.get(1, 0), "Value not equal");
   testEquals(B.get(1, 1), A.get(1, 1), "Value not equal");
   testEquals(B.get(1, 2), A.get(1, 2), "Value not equal");
   testEquals(B.get(1, 3), A.get(1, 3), "Value not equal");
   testEquals(B.get(2, 0), A.get(2, 0), "Value not equal");
   testEquals(B.get(2, 1), A.get(2, 1), "Value not equal");
   testEquals(B.get(2, 2), A.get(2, 2), "Value not equal");
   testEquals(B.get(2, 3), A.get(2, 3), "Value not equal");

   // Test Vertex3 constructor
   jm::Vertex3 c1(1, 2, 3);
   jm::Vertex3 c2(4, 5, 6);
   jm::Vertex3 c3(7, 8, 9);
   A = Matrix(c1, c2, c3, false);
   testEquals(A.rows(), 3UL, "Matrix.rows() not 3");
   testEquals(A.cols(), 3UL, "Matrix.cols() not 3");
   testEquals(A.get(0, 0), 1.0, "Value not 1");
   testEquals(A.get(1, 0), 2.0, "Value not 2");
   testEquals(A.get(2, 0), 3.0, "Value not 3");
   testEquals(A.get(0, 1), 4.0, "Value not 4");
   testEquals(A.get(1, 1), 5.0, "Value not 5");
   testEquals(A.get(2, 1), 6.0, "Value not 6");
   testEquals(A.get(0, 2), 7.0, "Value not 7");
   testEquals(A.get(1, 2), 8.0, "Value not 8");
   testEquals(A.get(2, 2), 9.0, "Value not 9");

   A = Matrix(c1, c2, c3, true);
   testEquals(A.rows(), 3UL, "Matrix.rows() not 3");
   testEquals(A.cols(), 3UL, "Matrix.cols() not 3");
   testEquals(A.get(0, 0), 1.0, "Value not 1");
   testEquals(A.get(0, 1), 2.0, "Value not 2");
   testEquals(A.get(0, 2), 3.0, "Value not 3");
   testEquals(A.get(1, 0), 4.0, "Value not 4");
   testEquals(A.get(1, 1), 5.0, "Value not 5");
   testEquals(A.get(1, 2), 6.0, "Value not 6");
   testEquals(A.get(2, 0), 7.0, "Value not 7");
   testEquals(A.get(2, 1), 8.0, "Value not 8");
   testEquals(A.get(2, 2), 9.0, "Value not 9");

}

