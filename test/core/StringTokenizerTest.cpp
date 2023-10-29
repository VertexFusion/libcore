//
//  StringTokenizerTest.cpp
//  jameo
//
//  Created by Uwe Runtemund on 17.03.14.
//  Copyright (c) 2014 Jameo Software. All rights reserved.
//

#include "core/Core.h"
#include "StringTokenizerTest.h"

using namespace jm;

StringTokenizerTest::StringTokenizerTest(bool debug):Test(debug)
{
	SetName("Test StringTokenizer");
}

void StringTokenizerTest::DoTest()
{
	
	//0 Token
	StringTokenizer* st = new StringTokenizer(""," ",false);
	TestFalse(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (1)");
	delete st;
	
	//1 Token
	st = new StringTokenizer("Hallo"," ",false);
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (2)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Hallo","StringTokenizer NextToken fails (3)");
	TestFalse(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (4)");
	delete st;
	
	//2 Token
	st = new StringTokenizer("Hallo Welt"," ",false);
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (5)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Hallo","StringTokenizer NextToken fails (6)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (7)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Welt","StringTokenizer NextToken fails (8)");
	TestFalse(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (9)");
	delete st;
	
	st = new StringTokenizer("Hallo  Welt"," ",false);
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (10)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Hallo","StringTokenizer NextToken fails (11)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (12)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Welt","StringTokenizer NextToken fails (13)");
	TestFalse(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (14)");
	delete st;

	st = new StringTokenizer("- .,- . ,Hallo -.,-., Welt-., -., "," -.,",false);
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (15)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Hallo","StringTokenizer NextToken fails (16)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (17)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Welt","StringTokenizer NextToken fails (18)");
	TestFalse(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (19)");
	delete st;
	
	//3 Tokens
	st = new StringTokenizer("Hallo Welt"," ",true);
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (20)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Hallo","StringTokenizer NextToken fails (21)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (22)");
	if(st->HasMoreTokens())TestEquals(st->NextToken()," ","StringTokenizer NextToken fails (23)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (24)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Welt","StringTokenizer NextToken fails (24)");
	TestFalse(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (26)");
	delete st;

	//4 Tokens
	st = new StringTokenizer("Hallo  Welt"," ",true);
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (27)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Hallo","StringTokenizer NextToken fails (28)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (29)");
	if(st->HasMoreTokens())TestEquals(st->NextToken()," ","StringTokenizer NextToken fails (30)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (31)");
	if(st->HasMoreTokens())TestEquals(st->NextToken()," ","StringTokenizer NextToken fails (32)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (33)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Welt","StringTokenizer NextToken fails (34)");
	TestFalse(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (35)");
	delete st;
	
	//5 Tokens
	st = new StringTokenizer("Hallo  Welt!","! ",true);
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (36)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Hallo","StringTokenizer NextToken fails (37)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (38)");
	if(st->HasMoreTokens())TestEquals(st->NextToken()," ","StringTokenizer NextToken fails (39)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (40)");
	if(st->HasMoreTokens())TestEquals(st->NextToken()," ","StringTokenizer NextToken fails (41)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (42)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"Welt","StringTokenizer NextToken fails (43)");
	TestTrue(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (44)");
	if(st->HasMoreTokens())TestEquals(st->NextToken(),"!","StringTokenizer NextToken fails (45)");
	TestFalse(st->HasMoreTokens(), "StringTokenizer HasMoreTokens fails (46)");
	delete st;

}
