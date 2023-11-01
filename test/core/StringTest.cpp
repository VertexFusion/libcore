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
using std::cout;
using std::endl;

StringTest::StringTest():Test()
{
	SetName("Test String");
}

void StringTest::DoTest()
{
	String str1=String("abc");
	String str2=String("abc");
	String str3=String("ABC");
	String str4=String("Ich mag das abc");
	String str5=String("ÄÖÜ");
	String str6=String("äöü");
	String str7=String("abcabc");
	String str8=String("äöüabc");
	
	//Teste UTF-8 Charakter
	TestEquals(str5.CharAt(0),0x00C4,"A-Umlaut fails");
	TestEquals(str5.CharAt(1),0x00D6,"O-Umlaut fails");
	TestEquals(str5.CharAt(2),0x00DC,"U-Umlaut fails");
	
	//Length
	TestEquals((int)str1.Length(),(int)str6.Length(), "String.Length fails");
	
	//Equals
	TestTrue(str1.Equals(str2),"String.Equals fails");
	TestFalse(str1.Equals(str3),"String.Equals fails");
	TestFalse(str1.Equals(str4),"String.Equals fails");
	TestFalse(str4.Equals(str1),"String.Equals fails");
	
	//EqualsIgnoreCase
	TestTrue(str1.EqualsIgnoreCase(str3),"String.EqualsIgnoreCase fails");
	TestFalse(str1.EqualsIgnoreCase(str4),"String.EqualsIgnoreCase fails");
	TestFalse(str4.EqualsIgnoreCase(str1),"String.EqualsIgnoreCase fails");
	TestTrue(str5.EqualsIgnoreCase(str6),"String.EqualsIgnoreCase fails");
	TestTrue(str6.EqualsIgnoreCase(str5),"String.EqualsIgnoreCase fails");

	//Value Of
	TestEquals(String::ValueOf(1234567),"1234567", "String.ValueOf fails");
	TestEquals(String::ValueOf(-234567),"-234567", "String.ValueOf fails");
	
	//Teste Operator
	TestEquals(str1+str2,str7, "+ fails");
	TestEquals(str1+"abc",str7, "+ fails");
	TestEquals("abc"+str2,str7, "+ fails");
	TestEquals(str1+str2,str7, "+ fails");
	TestEquals(str6+"abc",str8, "+ fails");
	TestEquals("äöü"+str2,str8, "+ fails");
	
	//Teste Trim
	str1="   123   ";
	str2="123";
	str3="";
	str4="    ";
	str5="     1";
	str6="1";
	TestEquals(str1.Trim(),str2, "String.Trim() fails");
	TestEquals(str3.Trim(),str3, "String.Trim() fails");
	TestEquals(str4.Trim(),str3, "String.Trim() fails");
	TestEquals(str5.Trim(),str6, "String.Trim() fails");
	
	//Hash
	str1="This is a Java string";
	str2="What the heck?";
	TestEquals(str1.HashCode(),586653468, "String.HashCode() fails");
	TestEquals(str2.HashCode(),277800975, "String.HashCode() fails");
	
	//LastIndexOf
	TestEquals(str1.IndexOf('i'),2, "String.IndexOf() fails");
	TestEquals(str1.LastIndexOf('i'),18, "String.LastIndexOf() fails");
	
	//Substring
	str1="abc123def";
	str2="123";
	str3="def";
	TestEquals(str1.Substring(3, 6),str2, "String.Substtring() fails");
	TestEquals(str1.Substring(6),str3, "String.Substtring() fails");
		
	//Teste Index Of
	str1="franz jagt im komplett verwahrlosten taxi quer durch bayern. Dabei schauen wir zu.";
	str2="en";

	TestEquals(str1.IndexOf('a'),2,"String.IndexOf() fails. (1)");
	TestEquals(str1.IndexOf(' '),5,"String.IndexOf() fails. (2)");
	TestEquals(str1.IndexOf('A'),-1,"String.IndexOf() fails. (3)");
	TestEquals(str1.IndexOf('a',4),7,"String.IndexOf() fails. (4)");
	TestEquals(str1.IndexOf("im"),11,"String.IndexOf() fails. (5)");
	TestEquals(str1.IndexOf("en"),34,"String.IndexOf() fails. (6)");
	TestEquals(str1.IndexOf("en",35),72,"String.IndexOf() fails. (7)");
	TestEquals(str1.IndexOf("im",11),11,"String.IndexOf() fails. (8)");
	TestEquals(str1.IndexOf("im",15),-1,"String.IndexOf() fails. (8)");
	
	//Teste LastIndexOf
	TestEquals(str1.LastIndexOf('a'),70,"String.LastIndexOf() fails. (1)");
	TestEquals(str1.LastIndexOf(' '),78,"String.LastIndexOf() fails. (2)");
	TestEquals(str1.LastIndexOf('A'),-1,"String.LastIndexOf() fails. (3)");
	TestEquals(str1.LastIndexOf("im"),11,"String.LastIndexOf() fails. (4)");
	TestEquals(str1.LastIndexOf("en"),72,"String.LastIndexOf() fails. (5)");
	
}
