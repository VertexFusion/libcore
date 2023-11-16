////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Math.h
// Library:     Jameo Core Library
// Purpose:     Usefull math functions
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     14.10.2012
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

#ifndef jm_Math_h
#define jm_Math_h

#include "Types.h"

namespace jm
{
	/*!
	 \brief This value defines when two points or values are considered identical. This serves to
	 catch numerical inaccuracies and the resulting errors. The predefined value can be changed, but
	 this may change the calculations considerably. 1E-6 is highly recommended as the highest value.
	 */
	double const RESABS = 1E-6;

	/*!
	 \brief  Diese Funktion rechnet den Winkel im Gradmaß in das Bogenmaß um.
	 \param deg Gegebener Winkel im Gradmaß (z.B. 30 für 30°).
	 \return Gibt den Winkel im Bogenmaß zurück.
	 */
	extern "C" DllExport
	double DegToRad(double deg);

	/*!
	 \brief  Diese Funktion rechnet den Winkel im Bogenmaß in das Gradmaß um.
	 \param rad Gegebener Winkel im Bogenmaß (z.B. PI/2 für 90°).
	 \return Gibt den Winkel im Gradmaß zurück.
	 */
	extern "C" DllExport
	double RadToDeg(double rad);

	/*!
	 \brief  Diese Funktion sibt das Vorzeichen einer Zahl zurück
	 \param d Die Zahl, dessen Vorzeichen ermittelt werden soll.
	 \return -1, wenn negativ, 0 bei 0 und 1 bei positivem d.
	 */
	extern "C" DllExport
	int16 Sgn(double d);

	/*!
	 \brief  Diese Funktion rundet eine Zahl kaufmännisch auf die Ganze Zahl
	 \param d Zahl, die gerundet werden soll.
	 \return Ganze Zahl.
	 */
	extern "C" DllExport
	int64 Round(double d);

	/*!
	 \brief  Diese Funktion rundet eine Zahl auf die gewünschte Anzahl der Nachkommastellen.
	 \note Beachte, dass aufgrund der Maschinengenauigkeigt nicht immer der exakte Wert getroffen
	 werden kann.
	 \param f Zahl, die gerundet werden soll.
	 \return Gerundete Zahl
	 */
	extern "C" DllExport
	float RoundFrac(float f, int32 digits);

	/*!
	 \brief Diese Methode prüft unter Berücksichtigung von resabs, ob die beiden Werte identisch
	 sind. Es gilt also |v2-v1| < RESABS. Wenn also RESABS unterschied ist, dann ist der Wert bereits
	 nicht mehr gleich.
	 // ES MUSS KLEINER EPSILON SEIN
	 \return Das Ergebnis von v1==v2
	 */
	extern "C" DllExport
	bool IsEqual(double v1, double v2);

	/*!
	 \brief Diese Methode prüft unter Berücksichtigung von resabs, ob der erste Wert ungleich dem
	 zweiten ist.
	 \return Das Ergebnis von v1!=v2
	 */
	extern "C" DllExport
	bool IsNotEqual(double v1, double v2);

	/*!
	 \brief Diese Methode prüft unter Berücksichtigung von resabs, ob der erste Wert niedriger ist
	 als der zweite
	 \return Das Ergebnis von v1<v2
	 */
	extern "C" DllExport
	bool IsLess(double v1, double v2);

	/*!
	 \brief Diese Methode prüft unter Berücksichtigung von resabs, ob der erste Wert niedriger
	 oder gleich ist als der zweite
	 \return Das Ergebnis von v1<=v2
	 */
	extern "C" DllExport
	bool IsLessEqual(double v1, double v2);

	/*!
	 \brief Diese Methode prüft unter Berücksichtigung von resabs, ob der erste Wert größer ist
	 als der zweite
	 \return Das Ergebnis von v1>v2
	 */
	extern "C" DllExport
	bool IsGreater(double v1, double v2);

	/*!
	 \brief Diese Methode prüft unter Berücksichtigung von resabs, ob der erste Wert größer oder
	 gleich ist als der zweite
	 \return Das Ergebnis von v1<v2
	 */
	extern "C" DllExport
	bool IsGreaterEqual(double v1, double v2);

	/*!
	 \brief Diese Methode prüft , ob die Zahl "Not a Number" ist.
	 \param d Der Wert, der geprüft werden soll
	 \return Das Ergebnis von d!=d
	 */
	extern "C" DllExport
	bool IsNaN(double d);

	/*!
	 \brief Diese Methode vertausch die beiden Variablen
	 */
	DllExport
	void Swap(Double& v1, Double& v2);

	/*!
	 \brief Diese Methode vertausch die beiden Variablen
	 */
	DllExport
	void Swap(double &v1, double &v2);

	/*!
	 \brief Diese Methode vertausch die beiden Variablen
	 */
	DllExport
	void Swap(int32 &v1, int32 &v2);

	/*!
	 \brief Diese Methode vertausch die beiden Variablen
	 */
	DllExport
	void Swap(uint32 &v1, uint32 &v2);

	/*!
	 \brief Diese Methode vertausch die beiden Variablen
	 */
	DllExport
	void Swap(uint16 &v1, uint16 &v2);

	/*!
	 \brief Diese Methode vertausch die beiden Variablen
	 */
	DllExport
	void Swap(uint8 &v1, uint8 &v2);

	/*!
	 \brief Returna a random number between 0.0 and 1.0
	 \note Not safe in sence of cryptography. Just an arbitrary number
	 */
	DllExport
	double Random();

	/*!
	 \brief Gibt eine ganzzahlige Zufallszahl zurück
	 \note Not safe in sence of cryptography. Just an arbitrary number
	 \param lower Untere einschließliche Grenze des Wertebereiches der zurückgegeben werden soll
	 \param upper Obere einschließliche Grenze des Wertebereiches der zurückgegeben werden soll
	 */
	DllExport
	int32 Random(int32 lower, int32 upper);

	/*!
	 \brief ermittelt zufällig, ob die bestimmte Wahrscheinlichkeit erfüllt ist
	 */
	DllExport
	bool Propability(double percent);

	/*!
	 \brief Diese Methode interpoliert den Zahlenwert zwischen begin und end.
	 \param begin Startwert für die Interpolation
	 \param end Endwert für die Interpolations
	 \param percent Verschiebungswert zwisch 0 und 1
	 */
	DllExport
	float Interpolate(float begin, float end, float percent);

	/*!
	 \brief Diese Methode interpoliert den Zahlenwert zwischen begin und end.
	 \param begin Startwert für die Interpolation
	 \param end Endwert für die Interpolations
	 \param percent Verschiebungswert zwisch 0 und 1
	 */
	DllExport
	double Interpolate(double begin, double end, double percent);

	DllExport
	double Interpolate(double vbegin, double vend, double begin, double end, double position);

	/*!
	 \brief Diese Methode prüft, ob die übergebene Zahl eine Potenz von 2 ist.
	 \param x Die Zahl, die geprüft werden soll
	 \return Gibt wahr zurück, wenn die Zahl eine Potens von 2 (also 1,2,4,8,16 usw.)ist, andernfalls
	 falsch.
	 */
	DllExport
	bool PowerOf2(int x);

	/*!
	 \brief Diese Methode gibt die kleinste Potenz von 2 über dem gegebenen Wert an. Wenn der Wert
	 selbst
	 eine Potenz von 2 ist, dann wird der Wert zurückgegeben
	 */
	DllExport
	uint32 CeilPowerOf2(uint32 x);

	/*!
	 \brief Diese Funktion berechnet die Relative Maschinengenauigkeit für double-Werte. Sollte
	 bei 64 bit 1.11022e-16 sein. Machne Literatur-Quellen geben auch 2.22045e-16 als Genauigkeit an.
	 */
	DllExport
	double DoubleMaschineEpsilon();

	/*!
	 \brief Diese Funktion berechnet die Relative Maschinengenauigkeit für float-Werte. Sollte bei
	 32 bit 5.96046e-08 sein. Machne Literatur-Quellen geben auch 1.19209e-07 als Genauigkeit an.
	 */
	DllExport
	float FloatMaschineEpsilon();

	/*!
	 \brief Divide one integer by another and round towards minus infinity.
	 \param x Dividend
	 \param y Divisor
	 \return The quotient, rounded towards minus infinity.
	 */
	DllExport
	int64 DivFloor(int64 x, int64 y);

	/*!
	 \brief Calculates the residual value after dividing one integer by another and rounds the
	 quotient towards minus infinity.
	 \param x Dividend
	 \param y Divisor
	 \return Residual value
	 */
	DllExport
	int64 ModFloor(int64 x, int64 y);

}
#endif
