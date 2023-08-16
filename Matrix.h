////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Matrix.h
// Library:     VertexFusion Library
// Purpose:     Matrix Class
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     22.10.2012
//
// Copyright:   (c) 2012 Jameo Software, Germany. https://jameo.de
//
// Licence:     The MIT License
//              Permission is hereby granted, free of charge, to any person obtaining a copy of this
//              software and associated documentation files (the "Software"), to deal in the
//              Software without restriction, including without limitation the rights to use, copy,
//              modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//              and to permit persons to whom the Software is furnished to do so, subject to the
//              following conditions:
//
//              The above copyright notice and this permission notice shall be included in all
//              copies or substantial portions of the Software.
//
//              THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//              INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//              PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//              HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
//              CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
//              OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef jm_Matrix_h
#define jm_Matrix_h

#include "Types.h"
#include "Vector.h"
#include "Vertex2.h"
#include "Vertex3.h"

namespace jm
{

	/*!
	 \brief Liste mit den verfügbaren Matrix-Normen
	 */
	enum MatrixNorm
	{
		kMatrixNorm1,//Spaltensummennorm
		kMatrixNormInf//Zeilensummennorm
	};

	/*!
	 \brief An mxn-dimensional matrix.
	 \ingroup core
	 */
	struct DllExport Matrix
	{
			DllExport
			friend const Matrix operator*(const Matrix &A, const Matrix &B);

			DllExport
			friend const Matrix operator*(const double &d, const Matrix &b);

			DllExport
			friend const Vertex3 operator*(const Matrix &A, const Vertex3 &b);

			DllExport
			friend const Matrix operator+(const Matrix &A, const Matrix &B);

			DllExport
			friend const Matrix operator-(const Matrix &A, const Matrix &B);

			DllExport
			friend const Matrix operator/(const Matrix &A, const double &d);

		private:

			/*!
			 \brief Dieses Feld speichert die Daten. In Analogie zur OpenGL Speicherkonvention werden die Daten Spaltenweise gespeichert.
			 */
			double* data;

		public:

			/*!
			 \brief Anzahl der Zeilen
			 */
			uint32 m;

			/*!
			 \brief Anzahl der Spalten
			 */
			uint32 n;

			/*!
			 \brief Dieser Konstruktor erzeugt eine Matrix und initialisiert sie mit Nullen.
			 \param rows Anzahl der Zeilen, die die Matrix enthalten soll.
			 \param cols Anzahl der Spalten, die die Matrix enthalten soll.
			 */
			Matrix(uint32 rows, uint32 cols);

			/*!
			 \brief Spezialkonstruktor für eine 3x3-Matrix.
			 \param c1 Die erste Spalte der Matrix
			 \param c2 Die zweite Spalte der Matrix
			 \param c3 Die dritte Spalte der Matrix
			 \param rowwise wenn wahr, dann wird die Matrix zeilenweise gefüllt.
			 */
			Matrix(Vertex3 c1, Vertex3 c2, Vertex3 c3, bool rowwise);

			/*!
			 \brief Standardkonstruktor
			 */
			Matrix();

			/*!
			 \brief Konstruktor richtet eine Matrix 1x1 mit dem Zahlenwert als Eintrag ein
			 */
			Matrix(double value);

			/*!
			 \brief Copy-Konstruktor
			 */
			Matrix(const Matrix &other);

			/*!
			 \brief Copy-Konstruktor
			 */
			Matrix(const Matrix* other);

			/*!
			 \brief Destructor
			 */
			virtual ~Matrix();

			/*!
			 \brief Legt den Wert eine Zelle fest
			 \param row Der 0-basierte Index der Zeile
			 \param col Der 0-basierte Index der Spalte
			 \param value Der Wert der Zelle
			 */
			void Set(uint32 row, uint32 col, double value);

			/*!
			 \brief Addiert auf den Wert einer Zelle den übergebenen Wert hinzu
			 \param row Der 0-basierte Index der Zeile
			 \param col Der 0-basierte Index der Spalte
			 \param value Der Wert, der auf die Zelle hinzuaddiert werden soll
			 */
			void Add(uint32 row, uint32 col, double value);

			/*!
			 \brief Gibt den Wert eine Zelle zurück
			 \param row Der 0-basierte Index der Zeile
			 \param col Der 0-basierte Index der Spalte
			 */
			double Get(uint32 row, uint32 col) const;

			/*!
			 \brief Diese Methode füllt alle Elemente der Matrix mit 0.
			 */
			void Zeros();

			/*!
			 \brief Diese Methode transponiert die Matrix
			 */
			void Transpose();

			/*!
			 \brief Diese Methode fügt den Inhalt der Anderen Matrix in diese Matrix ein.
			 Oberes linkes Element ist 0,0
			 */
			void Insert(const Matrix &A);

			/*!
			\brief Diese Methode fügt den Inhalt der Anderen Matrix in diese Matrix ein.
			Oberes linkes Element ist r,c
			*/
			void Insert(const Matrix &A, uint32 r, uint32 c);

			/*!
			 \brief Diese Methode setzt alle Werte auf den Diagonalelementen auf den gewünschten Wert.
			 */
			void Diag(double value);

			Matrix &operator=(const Matrix &A);

			/*!
			 \brief berechnet die Determinante einer Matrix
			 */
			VxfErrorStatus Det(double &det) const;

			/*!
			 \brief Invertiert diese Matrix
			 */
			VxfErrorStatus Inverse();

			/*!
			 \brief Diese Methode gibt die Referenz auf das Datenarray zurück.
			 Zwar wäre es möglich, hierrüber die Werte direkt zu bearbeiten, aber
			 einziger Grund für diese Methode ist der Zugriff für OpenGL.
			 */
			double* GetRef();

			/*!
			 \brief Diese Methode berechnet die Kondition der Matrix nach entsprechender Matrixnorm
			 */
			double Norm(MatrixNorm norm);

			/*!
			 \brief Diese Statische Funktion generiert eine 3x3 Rotationsmatrix
			 \param angle Rotationswinkel im Bogenmaß
			 \param axis Rotationsachse (muss normalisiert sein)
			 */
			static Matrix Generate3x3RotationMatrix(const double angle, const Vertex3 &axis);

			/*!
			 \brief Diese Statische Funktion generiert eine 3x3 Rotationsmatrix für eine Rotation um die X-Achse
			 \param angle Rotationswinkel im Bogenmaß
			 */
			static Matrix Generate3x3RotationXMatrix(const double angle);

			/*!
			 \brief Diese Statische Funktion generiert eine 3x3 Rotationsmatrix für eine Rotation um die Y-Achse
			 \param angle Rotationswinkel im Bogenmaß
			 */
			static Matrix Generate3x3RotationYMatrix(const double angle);

			/*!
			 \brief Diese Statische Funktion generiert eine 3x3 Rotationsmatrix für eine Rotation um die Z-Achse
			 \param angle Rotationswinkel im Bogenmaß
			 */
			static Matrix Generate3x3RotationZMatrix(const double angle);

			/*!
			 \brief Gibt den Inhalt der Matric auf der Konsole aus...
			 */
			void Print() const;

			/*!
			 \brief Diese Methode berechnet die Anzahl der Elemente, die nicht 0.0 sind.
			 Zur Zeit wird dies ohne eps gemacht.
			 */
			uint32 CountNonZeroElements() const;
	};


	/*!
	 \brief Implementierung des Operators M * M (Matrixmultiplikation)
	 */
	DllExport
	const Matrix operator*(const Matrix &A, const Matrix &B);


	/*!
	 \brief Implementierung des Operators d * M (Skalare multiplikation)
	 */
	DllExport
	const Matrix operator*(const double &d, const Matrix &b);

	/*!
	 \brief Implementierung des Operators M * d (Skalare multiplikation)
	 */
	DllExport
	const Matrix operator*(const Matrix &b, const double &d);

	/*!
	 \brief Implementierung des Operators M * v (Maktrixmultiplikation mit einem Vektor) Die Matrix muss Quadratisch sein...
	 */
	DllExport
	const Vector operator*(const Matrix& A, const Vector& b);

	/*!
	 \brief Implementierung des Operators M * v (Maktrixmultiplikation mit einem Vektor) Die Matrix muss 3x3 sein...
	 */
	DllExport
	const Vertex3 operator*(const Matrix &A, const Vertex3 &b);

	/*!
	 \brief Implementierung des Operators M / d (Skalare Division)
	 */
	DllExport
	const Matrix operator/(const Matrix &b, const double &d);

	/*!
	 \brief Implementierung des Operators M + M
	 */
	DllExport
	const Matrix operator+(const Matrix &A, const Matrix &B);

	/*!
	 \brief Implementierung des Operators M - M
	 */
	DllExport
	const Matrix operator-(const Matrix &A, const Matrix &B);

}
#endif
