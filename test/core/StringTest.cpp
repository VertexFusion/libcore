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
   SetName("Test String");
}

void StringTest::DoTest()
{
   TestEquals((int)sizeof(Char),2, "Size of jm::Char must be 2");
   TestTrue(Char('0').isDigit(), "Char('0').IsDigit() fails");
   TestFalse(Char('A').isDigit(), "Char('A').IsDigit() fails");

   String str1 = String("abc");
   String str2 = String("abc");
   String str3 = String("ABC");
   String str4 = String("Ich mag das abc");
   String str5 = String("ÄÖÜ");
   String str6 = String("äöü");
   String str7 = String("abcabc");
   String str8 = String("äöüabc");

   //Teste UTF-8 Charakter
   TestEquals(str5.charAt(0).unicode(), 0x00C4, "A-Umlaut fails");
   TestEquals(str5.charAt(1).unicode(), 0x00D6, "O-Umlaut fails");
   TestEquals(str5.charAt(2).unicode(), 0x00DC, "U-Umlaut fails");

   //Length
   TestEquals((int)str1.size(), (int)str6.size(), "String.Length fails");

   //Equals
   TestTrue(str1.equals(str2), "String.Equals fails");
   TestFalse(str1.equals(str3), "String.Equals fails");
   TestFalse(str1.equals(str4), "String.Equals fails");
   TestFalse(str4.equals(str1), "String.Equals fails");
   TestTrue(str1==str2, "String.Equals fails");
   TestTrue(str1!=str3, "String.Equals fails");
   TestFalse(str1==str4, "String.Equals fails");
   TestFalse(str4==str1, "String.Equals fails");

   //EqualsIgnoreCase
   TestTrue(str1.equalsIgnoreCase(str3), "String.EqualsIgnoreCase fails");
   TestFalse(str1.equalsIgnoreCase(str4), "String.EqualsIgnoreCase fails");
   TestFalse(str4.equalsIgnoreCase(str1), "String.EqualsIgnoreCase fails");
   TestTrue(str5.equalsIgnoreCase(str6), "String.EqualsIgnoreCase fails");
   TestTrue(str6.equalsIgnoreCase(str5), "String.EqualsIgnoreCase fails");

   //Value Of
   TestEquals(String::valueOf(1234567), "1234567", "String.valueOf fails");
   TestEquals(String::valueOf(-234567), "-234567", "String.valueOf fails");

   //Teste Operator
   TestEquals(str1 + str2, str7, "+ fails");
   TestEquals(str1 + "abc", str7, "+ fails");
   TestEquals("abc" + str2, str7, "+ fails");
   TestEquals(str1 + str2, str7, "+ fails");
   TestEquals(str6 + "abc", str8, "+ fails");
   TestEquals("äöü" + str2, str8, "+ fails");

   //Teste trim
   str1 = "   123   ";
   str2 = "123";
   str3 = jm::kEmptyString;
   str4 = "    ";
   str5 = "     1";
   str6 = "1";
   TestEquals(str1.trim(), str2, "String.trim() fails");
   TestEquals(str3.trim(), str3, "String.trim() fails");
   TestEquals(str4.trim(), str3, "String.trim() fails");
   TestEquals(str5.trim(), str6, "String.trim() fails");

   //Hash
   str1 = "This is a Java string";
   str2 = "What the heck?";
   TestEquals(str1.hashCode(), 586653468, "String.hashCode() fails");
   TestEquals(str2.hashCode(), 277800975, "String.hashCode() fails");

   //lastIndexOf
   TestEquals(str1.indexOf('i'), 2, "String.indexOf() fails");
   TestEquals(str1.lastIndexOf('i'), 18, "String.lastIndexOf() fails");

   //substring
   str1 = "abc123def";
   str2 = "123";
   str3 = "def";
   TestEquals(str1.substring(3, 6), str2, "String.Substtring() fails");
   TestEquals(str1.substring(6), str3, "String.Substtring() fails");

   //Teste Index Of
   str1 = "franz jagt im komplett verwahrlosten taxi quer durch bayern. Dabei schauen wir zu.";
   str2 = "en";

   TestEquals(str1.indexOf('a'), 2, "String.indexOf() fails. (1)");
   TestEquals(str1.indexOf(' '), 5, "String.indexOf() fails. (2)");
   TestEquals(str1.indexOf('A'), -1, "String.indexOf() fails. (3)");
   TestEquals(str1.indexOf('a', 4), 7, "String.indexOf() fails. (4)");
   TestEquals(str1.indexOf("im"), 11, "String.indexOf() fails. (5)");
   TestEquals(str1.indexOf("en"), 34, "String.indexOf() fails. (6)");
   TestEquals(str1.indexOf("en", 35), 72, "String.indexOf() fails. (7)");
   TestEquals(str1.indexOf("im", 11), 11, "String.indexOf() fails. (8)");
   TestEquals(str1.indexOf("im", 15), -1, "String.indexOf() fails. (8)");

   //Teste lastIndexOf
   TestEquals(str1.lastIndexOf('a'), 70, "String.lastIndexOf() fails. (1)");
   TestEquals(str1.lastIndexOf(' '), 78, "String.lastIndexOf() fails. (2)");
   TestEquals(str1.lastIndexOf('A'), -1, "String.lastIndexOf() fails. (3)");
   TestEquals(str1.lastIndexOf("im"), 11, "String.lastIndexOf() fails. (4)");
   TestEquals(str1.lastIndexOf("en"), 72, "String.lastIndexOf() fails. (5)");

   // Teste to lower/upper case
   str1="alles ok.äöü";
   str2="ALLES OK.ÄÖÜ";
   TestEquals(str1.toUpperCase(),str2, "String.toUpperCase() fails.");
   TestEquals(str2.toLowerCase(),str1, "String.ToLowerCase() fails.");

   // Test arg Integer
   Integer i=25;
   str1=String("The number is %1!").arg(i);
   str2=String("The number is 25!");
   TestEquals(str1,str2, "String.arg(Integer) fails. (1)");

   str1=String("[%1]").arg(i,8);
   str2=String("[      25]");
   TestEquals(str1,str2, "String.arg(Integer) fails. (2)");

   str1=String("[%1]").arg(i,-8);
   str2=String("[25      ]");
   TestEquals(str1,str2, "String.arg(Integer) fails. (3)");

   // Test arg Double
   Double d=24.6666;
   str1=String("The number is %1!").arg(d);
   str2=String("The number is 24,6666!");
   TestEquals(str1,str2, "String.arg(Double) fails. (1)");

   str1=String("[%1]").arg(d,8);
   str2=String("[ 24,6666]");
   TestEquals(str1,str2, "String.arg(Double) fails. (2)");

   str1=String("[%1]").arg(d,-8);
   str2=String("[24,6666 ]");
   TestEquals(str1,str2, "String.arg(Double) fails. (3)");

   str1=String("[%1]").arg(d,8,2);
   str2=String("[   24,67]");
   TestEquals(str1,str2, "String.arg(Double) fails. (4)");

   str1=String("[%1]").arg(d,-8,2);
   str2=String("[24,67   ]");
   TestEquals(str1,str2, "String.arg(Double) fails. (5)");

   str1=String("[%1]").arg(d,8,3,'.');
   str2=String("[..24,667]");
   TestEquals(str1,str2, "String.arg(Double) fails. (6)");

   str1=String("[%1]").arg(d,-8,3,'.');
   str2=String("[24,667..]");
   TestEquals(str1,str2, "String.arg(Double) fails. (7)");

}
