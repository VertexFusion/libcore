//
//  Testcase.cpp
//  jameo
//
//  Created by Uwe Runtemund on 17.01.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "core/Core.h"
#include "StringTest.h"

using namespace jm;

StringTest::StringTest(): Test()
{
   setName("Test String");
}

void StringTest::doTest()
{
   testEquals((int)sizeof(Char), 2, "Size of jm::Char must be 2");
   testTrue(Char('0').isDigit(), "Char('0').IsDigit() fails");
   testFalse(Char('A').isDigit(), "Char('A').IsDigit() fails");

   String str1 = String("abc");
   String str2 = String("abc");
   String str3 = String("ABC");
   String str4 = String("Ich mag das abc");
   String str5 = String("ÄÖÜ");
   String str6 = String("äöü");
   String str7 = String("abcabc");
   String str8 = String("äöüabc");

   //Teste UTF-8 Charakter
   testEquals(str5.charAt(0).unicode(), 0x00C4, "A-Umlaut fails");
   testEquals(str5.charAt(1).unicode(), 0x00D6, "O-Umlaut fails");
   testEquals(str5.charAt(2).unicode(), 0x00DC, "U-Umlaut fails");

   //Length
   testEquals((int)str1.size(), (int)str6.size(), "String.Length fails");

   //Equals
   testTrue(str1.equals(str2), "String.Equals fails");
   testFalse(str1.equals(str3), "String.Equals fails");
   testFalse(str1.equals(str4), "String.Equals fails");
   testFalse(str4.equals(str1), "String.Equals fails");
   testTrue(str1 == str2, "String.Equals fails");
   testTrue(str1 != str3, "String.Equals fails");
   testFalse(str1 == str4, "String.Equals fails");
   testFalse(str4 == str1, "String.Equals fails");

   //EqualsIgnoreCase
   testTrue(str1.equalsIgnoreCase(str3), "String.EqualsIgnoreCase fails");
   testFalse(str1.equalsIgnoreCase(str4), "String.EqualsIgnoreCase fails");
   testFalse(str4.equalsIgnoreCase(str1), "String.EqualsIgnoreCase fails");
   testTrue(str5.equalsIgnoreCase(str6), "String.EqualsIgnoreCase fails");
   testTrue(str6.equalsIgnoreCase(str5), "String.EqualsIgnoreCase fails");

   //Value Of
   testEquals(String::valueOf(1234567), "1234567", "String.valueOf fails");
   testEquals(String::valueOf(-234567), "-234567", "String.valueOf fails");

   //Teste Operator
   testEquals(str1 + str2, str7, "+ fails");
   testEquals(str1 + "abc", str7, "+ fails");
   testEquals("abc" + str2, str7, "+ fails");
   testEquals(str1 + str2, str7, "+ fails");
   testEquals(str6 + "abc", str8, "+ fails");
   testEquals("äöü" + str2, str8, "+ fails");

   //Teste trim
   str1 = "   123   ";
   str2 = "123";
   str3 = jm::kEmptyString;
   str4 = "    ";
   str5 = "     1";
   str6 = "1";
   testEquals(str1.trim(), str2, "String.trim() fails");
   testEquals(str3.trim(), str3, "String.trim() fails");
   testEquals(str4.trim(), str3, "String.trim() fails");
   testEquals(str5.trim(), str6, "String.trim() fails");

   //Hash
   str1 = "This is a Java string";
   str2 = "What the heck?";
   testEquals(str1.hashCode(), 586653468, "String.hashCode() fails");
   testEquals(str2.hashCode(), 277800975, "String.hashCode() fails");

   //lastIndexOf
   testEquals(str1.indexOf('i'), 2, "String.indexOf() fails");
   testEquals(str1.lastIndexOf('i'), 18, "String.lastIndexOf() fails");

   //substring
   str1 = "abc123def";
   str2 = "123";
   str3 = "def";
   testEquals(str1.substring(3, 6), str2, "String.Substtring() fails");
   testEquals(str1.substring(6), str3, "String.Substtring() fails");

   //Teste Index Of
   str1 = "franz jagt im komplett verwahrlosten taxi quer durch bayern. Dabei schauen wir zu.";
   str2 = "en";

   testEquals(str1.indexOf('a'), 2, "String.indexOf() fails. (1)");
   testEquals(str1.indexOf(' '), 5, "String.indexOf() fails. (2)");
   testEquals(str1.indexOf('A'), -1, "String.indexOf() fails. (3)");
   testEquals(str1.indexOf('a', 4), 7, "String.indexOf() fails. (4)");
   testEquals(str1.indexOf("im"), 11, "String.indexOf() fails. (5)");
   testEquals(str1.indexOf("en"), 34, "String.indexOf() fails. (6)");
   testEquals(str1.indexOf("en", 35), 72, "String.indexOf() fails. (7)");
   testEquals(str1.indexOf("im", 11), 11, "String.indexOf() fails. (8)");
   testEquals(str1.indexOf("im", 15), -1, "String.indexOf() fails. (8)");

   //Teste lastIndexOf
   testEquals(str1.lastIndexOf('a'), 70, "String.lastIndexOf() fails. (1)");
   testEquals(str1.lastIndexOf(' '), 78, "String.lastIndexOf() fails. (2)");
   testEquals(str1.lastIndexOf('A'), -1, "String.lastIndexOf() fails. (3)");
   testEquals(str1.lastIndexOf("im"), 11, "String.lastIndexOf() fails. (4)");
   testEquals(str1.lastIndexOf("en"), 72, "String.lastIndexOf() fails. (5)");

   // Teste to lower/upper case
   str1 = "alles ok.äöü";
   str2 = "ALLES OK.ÄÖÜ";
   testEquals(str1.toUpperCase(), str2, "String.toUpperCase() fails.");
   testEquals(str2.toLowerCase(), str1, "String.ToLowerCase() fails.");

   // Test arg Integer
   int64 i = 25;
   str1 = String("The number is %1!").arg(i);
   str2 = String("The number is 25!");
   testEquals(str1, str2, "String.arg(Integer) fails. (1)");

   str1 = String("[%1]").arg(i, 8);
   str2 = String("[      25]");
   testEquals(str1, str2, "String.arg(Integer) fails. (2)");

   str1 = String("[%1]").arg(i, -8);
   str2 = String("[25      ]");
   testEquals(str1, str2, "String.arg(Integer) fails. (3)");

   // Test arg Double
   double d = 24.6666;
   str1 = String("The number is %1!").arg(d);
   str2 = String("The number is 24,6666!");
   testEquals(str1, str2, "String.arg(Double) fails. (1)");

   str1 = String("[%1]").arg(d, 8);
   str2 = String("[ 24,6666]");
   testEquals(str1, str2, "String.arg(Double) fails. (2)");

   str1 = String("[%1]").arg(d, -8);
   str2 = String("[24,6666 ]");
   testEquals(str1, str2, "String.arg(Double) fails. (3)");

   str1 = String("[%1]").arg(d, 8, 2);
   str2 = String("[   24,67]");
   testEquals(str1, str2, "String.arg(Double) fails. (4)");

   str1 = String("[%1]").arg(d, -8, 2);
   str2 = String("[24,67   ]");
   testEquals(str1, str2, "String.arg(Double) fails. (5)");

   str1 = String("[%1]").arg(d, 8, 3, '.');
   str2 = String("[..24,667]");
   testEquals(str1, str2, "String.arg(Double) fails. (6)");

   str1 = String("[%1]").arg(d, -8, 3, '.');
   str2 = String("[24,667..]");
   testEquals(str1, str2, "String.arg(Double) fails. (7)");


   // Test startsWith
   str1 = "abcdef";
   testTrue(str1.startsWith("ab"), "String.startsWith() fails. (1)");
   testFalse(str1.startsWith("bc"), "String.startsWith() fails. (2)");

   // Test endsWith
   testTrue(str1.endsWith("ef"), "String.endsWith() fails. (1)");
   testFalse(str1.endsWith("de"), "String.endsWith() fails. (2)");

   // Test clear
   str1.clear();
   testTrue(str1.size() == 0, "String.clear() fails");

   // Test reverse
   str1 = "abcdef";
   str1 = str1.reverse();
   testEquals(str1, String("fedcba"), "String.reverse() fails");

   // Test insert
   str1 = "abcdef";
   str1.insert(3, "123");
   testEquals(str1, String("abc123def"), "String.insert(String) fails");

   str1.insert(6, Char('4'));
   testEquals(str1, String("abc1234def"), "String.insert(Char) fails");

   str1.clear();
   str1.insert(0, "123");
   testEquals(str1, String("123"), "String.insert(String) fails");

   str1.clear();
   str1.insert(0, Char('x'));
   testEquals(str1, String("x"), "String.insert(Char) fails");

   // Test deleteCharRangeAt
   str1 = "abcdef";
   str1.deleteCharRangeAt(2, 3);
   testEquals(str1, String("abf"), "String.deleteCharRangeAt() fails");

   str1 = "abcdef";
   str1.deleteCharRangeAt(0, 3);
   testEquals(str1, String("def"), "String.deleteCharRangeAt() fails");

   str1 = "abcdef";
   str1.deleteCharRangeAt(3, 3);
   testEquals(str1, String("abc"), "String.deleteCharRangeAt() fails");

   str1 = "abcdef";
   str1.deleteCharRangeAt(0, 6);
   testEquals(str1, String(""), "String.deleteCharRangeAt() fails");

   str1 = "abcdef";
   str1.deleteCharRangeAt(6, 0);
   testEquals(str1, String("abcdef"), "String.deleteCharRangeAt() fails");

   // Test deleteCharAt
   str1 = "abcdef";
   str1.deleteCharAt(2);
   testEquals(str1, String("abdef"), "String.deleteCharAt(2) fails");

   str1 = "abcdef";
   str1.deleteCharAt(0);
   testEquals(str1, String("bcdef"), "String.deleteCharAt(0) fails");

   str1 = "abcdef";
   str1.deleteCharAt(5);
   testEquals(str1, String("abcde"), "String.deleteCharAt(5) fails");

   // Test replace
   str1 = "abcdef";
   str1 = str1.replace('c', 'd');
   testEquals(str1, String("abddef"), "String.replace() fails");

   str1 = "abcdef";
   str1 = str1.replace("cd", "xy");
   testEquals(str1, String("abxyef"), "String.replace() fails");

   str1 = "abcdef";
   str1 = str1.replace("cd", "x");
   testEquals(str1, String("abxef"), "String.replace() fails");

   str1 = "abcdef";
   str1 = str1.replace("cd", "");
   testEquals(str1, String("abef"), "String.replace() fails");

   isEmpty();
   compareFancy();
   constructors();
}

void StringTest::constructors()
{
   const char* str = "abc";

   String str1(str, 3);
   testEquals(str1, String("abc"), "String() fails (1)");

   String str2(str, 3, jm::Charset::getDefault());
   testEquals(str2, String("abc"), "String() fails (2)");

   String str3((const char*)nullptr);
   testEquals(str3, kEmptyString, "String() fails (3)");

   String str4(str);
   testEquals(str4, String("abc"), "String() fails (4)");

   const uint16 str16[] = {0x0061, 0x0062, 0x0063, 0x0000};

   String str5(str16, 3);
   testEquals(str5, String("abc"), "String() fails (5)");

   String str6(str, jm::Charset::getDefault());
   testEquals(str6, String("abc"), "String() fails (6)");

   jm::ByteArray byteArray = str6.toCString();
   String str7(byteArray, jm::Charset::getDefault());
   testEquals(str7, String("abc"), "String() fails (7)");
}


void StringTest::isEmpty()
{
   String str1 = "";
   testTrue(str1.isEmpty(), "String.isEmpty() fails. (1)");

   str1 = " ";
   testFalse(str1.isEmpty(), "String.isEmpty() fails. (2)");
}

void StringTest::compareFancy()
{
   // Test case: Both strings are equal
   String str1("abc123");
   String str2("abc123");
   testEquals(str1.compareFancyTo(str2), 0, "String.compareFancyTo() fails (1)");

   // Test case: First string is less than the second string
   String str3("abc123");
   String str4("abc124");
   testEquals(str3.compareFancyTo(str4), -1, "String.compareFancyTo() fails (2)");

   // Test case: First string is greater than the second string
   String str5("abc125");
   String str6("abc124");
   testEquals(str5.compareFancyTo(str6), 1, "String.compareFancyTo() fails (3)");

   // Test case: First string is shorter than the second string
   String str7("abc12");
   String str8("abc123");
   testEquals(str7.compareFancyTo(str8), -1, "String.compareFancyTo() fails (4)");

   // Test case: First string is longer than the second string
   String str9("abc1234");
   String str10("abc123");
   testEquals(str9.compareFancyTo(str10), 1, "String.compareFancyTo() fails (5)");

   // Test case: Strings with different characters
   String str11("abc");
   String str12("abd");
   testEquals(str11.compareFancyTo(str12), -1, "String.compareFancyTo() fails (6)");

   // Test case: Strings with digits and characters
   String str13("a1b2c3");
   String str14("a1b2c4");
   testEquals(str13.compareFancyTo(str14), -1, "String.compareFancyTo() fails (7)");

   // Test case: Strings with leading zeros in digits
   String str15("a001");
   String str16("a1");
   testEquals(str15.compareFancyTo(str16), 0, "String.compareFancyTo() fails (8)");

   // Test case: Strings with only digits
   String str17("123");
   String str18("124");
   testEquals(str17.compareFancyTo(str18), -1, "String.compareFancyTo() fails (9)");

   // Test case: Empty strings
   String str19("");
   String str20("");
   testEquals(str19.compareFancyTo(str20), 0, "String.compareFancyTo() fails (10)");

   // Test case: One empty string and one non-empty string
   String str21("");
   String str22("abc");
   testEquals(str21.compareFancyTo(str22), -1, "String.compareFancyTo() fails (11)");
}