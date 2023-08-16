////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Test.h
// Library:     VertexFusion Library
// Purpose:     Declaration of Test class
//
// Author:      Uwe Runtemund (2012-today)
// Modified by:
// Created:     07.10.2012
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

#ifndef jm_Test_h
#define jm_Test_h

#include <vector>

#include "String.h"

namespace jm
{

	class DllExport Test
	{

		public:

			/*!
			 \brief Konstruktor
			 */
			Test(bool debug);

			/*!
			 \brief Destructor
			 */
			virtual ~Test();

			String GetName();//Liefert den Namen des Tests zurück
			void SetName(String name);
			virtual void DoTest() = 0;

			/**
			 * Wenn diese Methode aufgerugen wird, dann wurde ein Throwable geschmissen, die
			 * nicht erwartet wurde
			 * */
			void TestUnexpectedException(String failmessage);

	protected:
		bool debug;
		String name;

		/*!
		 \brief Legt Fehlermeldung fest
		 */
		void SetErrorCode(String error);

		/*!
		 \brief Liefert Fehlermeldung zurück
		 */
		String GetErrorCode();

		/*!
		 \brief Wenn diese Methode aufgerufen wird, dann ist der Test fehlgeschlagen.
		 */
		void TestFail(String message);

		/*!
		 \brief Diese Methode testet, ob die zwei Double-Werte unter Berücksichtigung von resabs
		 gleich sind. Wenn dies nicht der Fall ist, wird die (optionale) Fehlermeldung ausgegeben.
		 */
		void TestEquals(const double actual, const double expected, const String &failmessage);

		/*!
		 \brief Diese Methode testet, ob die zwei Integer-Werte gleich sind.
		 Wenn dies nicht der Fall ist, wird die (optionale) Fehlermeldung ausgegeben
		 */
		void TestEquals(uint64 actual, uint64 expected, String failmessage);

		/*!
		 \brief Diese Methode testet, ob die zwei Integer-Werte gleich sind.
		 Wenn dies nicht der Fall ist, wird die (optionale) Fehlermeldung ausgegeben
		 */
		void TestEquals(void* actual, void* expected, String failmessage);

		/**
		 * Diese Methode testet, ob die zwei Integer-Werte gleich sind.
		 * Wenn dies nicht der Fall ist, wird die (optionale) Fehlermeldung ausgegeben
		 * */
		void TestEquals(int64 actual, int64 expected, String failmessage);

		/**
		 * Diese Methode testet, ob die zwei Integer-Werte gleich sind.
		 * Wenn dies nicht der Fall ist, wird die (optionale) Fehlermeldung ausgegeben
		 * */
		void TestEquals(uint64 actual, int32 expected, String failmessage);

		/**
		 * Diese Methode testet, ob die zwei Integer-Werte gleich sind.
		 * Wenn dies nicht der Fall ist, wird die (optionale) Fehlermeldung ausgegeben
		 * */
		void TestEquals(uint64 actual, uint32 expected, String failmessage);

		/**
		 * Diese Methode testet, ob die zwei Integer-Werte gleich sind.
		 * Wenn dies nicht der Fall ist, wird die (optionale) Fehlermeldung ausgegeben
		 * */
		void TestEquals(int32 actual, int32 expected, String failmessage);

		/**
		 * Diese Methode testet, ob die zwei Integer-Werte gleich sind.
		 * Wenn dies nicht der Fall ist, wird die (optionale) Fehlermeldung ausgegeben
		 * */
		void TestEquals(uint32 actual, uint32 expected, String failmessage);

		/**
		 * Diese Methode testet, ob die zwei Integer-Werte gleich sind.
		 * Wenn dies nicht der Fall ist, wird die (optionale) Fehlermeldung ausgegeben
		 * */
		void TestEquals(uint32 actual, int32 expected, String failmessage);

		/**
		 * Diese Methode testet, ob die zwei Integer-Werte gleich sind.
		 * Wenn dies nicht der Fall ist, wird die (optionale) Fehlermeldung ausgegeben
		 * */
		void TestEquals(int32 actual, uint32 expected, String failmessage);

		/**
		 * Diese Methode testet, ob die zwei String gleich sind
		 * */
		void TestEquals(String actual, String expected, String failmessage);

		/**
		 * Diese Methode testet, ob die zwei String gleich sind
		 * */
		void TestEqualsIgnoreCase(String actual, String expected, String failmessage);

		/**
		 * Diese Methode prüft, ob das übergebene Objekt null ist
		 * */
		void TestNull(void* actual, String failmessage);

		/**
		 * Diese Methode prüft, ob das übergebene NICHT Objekt null ist
		 * */
		void TestNotNull(void* actual, String failmessage);

		/**
		 * Diese Methode prüft, ob das übergebene wahr ist
		 * */
		void TestTrue(bool actual, String failmessage);

		/**
		 * Diese Methode prüft, ob das übergebene falsch ist
		 * */
		void TestFalse(bool actual, String failmessage);

					private:
						String error;
	};

	class TestVector
	{
		private:
			String arg;
			std::vector<Test*> tests;
			void Testrun(Test* test);

		public:
			TestVector(int argc, const char* argv[]);
			~TestVector();
			void AddTest(Test* test);
			void Execute();
	};

	extern "C"
	void LogMessage(String message);

	extern "C" int32 gErrorCount;
	extern "C" int32 gTestCount;
	extern "C" int32 gTotalErrorCount;
	extern "C" int32 gTotalTestCount;

}
#endif
