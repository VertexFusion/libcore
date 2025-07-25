////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Test.h
// Library:     Jameo Core Library
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


/*!
 \defgroup test Test

 \brief A collection of classes to provide unit tests.

 Jameo Core library provides simple ways to perform unit testing. The following example code shows
 the minimum requirements for an test app:

~~~~~{.cpp}
#include "core/Core.h"

// Example test class to show simple test anatomy.
class ExampleTest: public jm::Test
{
	public:

		// Constructor
		ExampleTest():Test()
		{
			setName("Example Test");
		};

		// Mandatory overridden test method. The heart of the test!
		void doTest() override
		{
			int32 a=2;
			int32 b=5;
			testEquals(a,b,"a is not b");
			a=5;
			testEquals(a,b,"a is not b");
		};
};

// Entry method of test application
int main( int argc, const char* argv[] )
{
	// init Jameo System
	jm::System::init();
	jm::System::log( "Example Test Suite" , jm::LogLevel::kInformation );

	// init test vector
	jm::TestVector* vec = new jm::TestVector(argc, argv);
	vec->addTest( new ExampleTest() );

	// Execute test vector
	int32 result = static_cast<int32>(vec->execute());

	// Clean up
	delete vec;
	jm::System::quit();

	// Return the number of errors to help calling scripts
	return result;
}
~~~~~

The console output of the app will be something like:

~~~~~
[2023-11-01T12:15:17.768Z] INFO: Example Test Suite
[2023-11-01T12:15:17.768Z] INFO: Execute Example Test...
[2023-11-01T12:15:17.768Z] ERROR: a is not b '2' '5'
[2023-11-01T12:15:17.768Z] INFO: Test finished! 2 Tests, 1 Errors.

Cycle finished! In total 2 tests, 1 errors, duration 0,000 sec.
~~~~~

 */


namespace jm
{

   /*!
    \brief This base class represents a test object. It is used to implement unit tests for any
    code. Typically a set of tests is collected in one derived test class.
    \ingroup test
    */
   class DllExport Test: public Object
   {

      public:

         /*!
          \brief Constructor
          */
         Test() = default;

         /*!
          \brief Destructor
          */
         ~Test() = default;

         /*!
          \brief Returns the name of the test.
          */
         const String& name() const;

         /*!
          \brief Set the name of the text.
          \param name The name.
          */
         void setName(const String& name);

         /*!
          \brief This is the main test method, which must be implemented by every derived test
          class.
          */
         virtual void doTest() = 0;

         /*!
          \brief This method shall be called in the catch clause of an jm::Exception.
         */
         void testUnexpectedException(const String& failmessage) const;

      protected:

         /*!
          \brief Set the error message of this test.
          \param error The error message.
          */
         void setErrorCode(const String& error);

         /*!
          \brief Returns the (last) error message.
          */
         const String& errorCode() const;

         /*!
          \brief Call this method, if you made a test by yourself and this test failed.
          */
         void testFail(const String& message) const;

         /*!
          \brief This method tests, if double \p actual is equal to \p expected under consideration
          of \c RESABS.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(const double actual, const double expected, const String& failmessage) const;

         /*!
          \brief This method tests, if Integer \p actual is equal to \p expected.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(int64 actual, int64 expected, const String& failmessage) const;

         /*!
          \brief This method tests, if Integer \p actual is equal to \p expected.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(int64 actual, int32 expected, const String& failmessage) const;


         /*!
          \brief This method tests, if uint64 \p actual is equal to \p expected.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(uint64 actual, uint64 expected, const String& failmessage) const;

         /*!
          \brief This method tests, if void* \p actual is equal to \p expected.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(void* actual, void* expected, const String& failmessage) const;

         /*!
          \brief This method tests, if uint64 \p actual is equal to \p expected.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(uint64 actual, int32 expected, const String& failmessage) const;

         /*!
          \brief This method tests, if uint64 \p actual is equal to \p expected.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(uint64 actual, uint32 expected, const String& failmessage) const;

         /*!
          \brief This method tests, if int32 \p actual is equal to \p expected.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(int32 actual, int32 expected, const String& failmessage) const;

         /*!
          \brief This method tests, if uint32 \p actual is equal to \p expected.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(uint32 actual, uint32 expected, const String& failmessage) const;

         /*!
          \brief This method tests, if uint32 \p actual is equal to \p expected.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(uint32 actual, int32 expected, const String& failmessage) const;


         /*!
          \brief This method tests, if int32 \p actual is equal to \p expected.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(int32 actual, uint32 expected, const String& failmessage) const;

         /*!
          \brief This method tests, if String \p actual is equal to \p expected.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEquals(const String& actual,
                         const String& expected,
                         const String& failmessage) const;

         /*!
          \brief This method tests, if String \p actual is equal to \p expected ignoring cases.
          \param actual The test value
          \param expected The expected value
          \param failmessage The log message in case of failed test.
          */
         void testEqualsIgnoreCase(const String& actual,
                                   const String& expected,
                                   const String& failmessage) const;

         /*!
          \brief This method tests, if \p actual is \c NULL.
          \param actual The test value
          \param failmessage The log message in case of failed test.
          */
         void testNull(const void* actual, const String& failmessage) const;

         /*!
          \brief This method tests, if \p actual is not \c NULL.
          \param actual The test value
          \param failmessage The log message in case of failed test.
          */
         void testNotNull(const void* actual, const String& failmessage) const;

         /*!
          \brief This method tests, if \p actual is \c true.
          \param actual The test value
          \param failmessage The log message in case of failed test.
          */
         void testTrue(bool actual, const String& failmessage) const;

         /*!
          \brief This method tests, if \p actual is \c false.
          \param actual The test value
          \param failmessage The log message in case of failed test.
          */
         void testFalse(bool actual, const String& failmessage) const;

      private:

         //! The name of the test.
         String mName;

         //! The error message
         String mError;
   };

   /*!
   \brief A TestVector is a collection of several tests and will execute them all and return
   the number of errors on execution.

   This class needs the parameter \p argc and \argv which are typically provides vom the entry
   method int main() on every operating system.

   When passing arguments to the executable from the command line, the argument shall be the
   0 based index of a single test which will be executed. If no argument is provided, all tests
   will be done. With this possibility you can focus on a single test when developing and testing
   test classes by passing the number to the executable.

   \ingroup test
   */
   class DllExport TestVector
   {
      public:

         /*!
          \brief Constructor
          \param argc 1st parameter from int main()
          \param argv 2nd parameter from int maint()
          */
         TestVector(int argc, const char* argv[]);

         /*!
          \brief Destructor
         */
         ~TestVector();

         /*!
          \brief Adds \p test to the test vector.
          \param test The test to be added.
          */
         void addTest(Test* test);

         /*!
          \brief Executes the test vector.
          \return The number or errors. 0, if everything is ok.
          */
         size_t execute();

      private:

         //! \brief The 1st argument from command line (after executable name).
         String mArg;

         //! \brief  The tests to be done.
         std::vector<Test*>* mTests;

         //! \brief  Helper method for single test run.
         //! \param test Test to run.
         void testrun(Test* test) const;

   };

   //! \brief  global error count during single test run.
   //! \ingroup test
   extern "C" size_t gErrorCount;

   //! \brief  global test count during single test run.
   //! \ingroup test
   extern "C" size_t gTestCount;

   //! \brief  global error count over all done tests.
   //! \ingroup test
   extern "C" size_t gTotalErrorCount;

   //! \brief  global test count overall done tests.
   //! \ingroup test
   extern "C" size_t gTotalTestCount;

}
#endif
