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

StringTokenizerTest::StringTokenizerTest(): Test()
{
   setName("Test StringTokenizer");
}

void StringTokenizerTest::doTest()
{

   //0 Token
   StringTokenizer* st = new StringTokenizer(jm::kEmptyString, " ", false);
   testFalse(st->hasNext(), "StringTokenizer HasMoreTokens fails (1)");
   delete st;

   //1 Token
   st = new StringTokenizer("Hallo", " ", false);
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (2)");
   if(st->hasNext())testEquals(st->next(), "Hallo", "StringTokenizer NextToken fails (3)");
   testFalse(st->hasNext(), "StringTokenizer HasMoreTokens fails (4)");
   delete st;

   //2 Token
   st = new StringTokenizer("Hallo Welt", " ", false);
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (5)");
   if(st->hasNext())testEquals(st->next(), "Hallo", "StringTokenizer NextToken fails (6)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (7)");
   if(st->hasNext())testEquals(st->next(), "Welt", "StringTokenizer NextToken fails (8)");
   testFalse(st->hasNext(), "StringTokenizer HasMoreTokens fails (9)");
   delete st;

   st = new StringTokenizer("Hallo  Welt", " ", false);
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (10)");
   if(st->hasNext())testEquals(st->next(), "Hallo", "StringTokenizer NextToken fails (11)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (12)");
   if(st->hasNext())testEquals(st->next(), "Welt", "StringTokenizer NextToken fails (13)");
   testFalse(st->hasNext(), "StringTokenizer HasMoreTokens fails (14)");
   delete st;

   st = new StringTokenizer("- .,- . ,Hallo -.,-., Welt-., -., ", " -.,", false);
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (15)");
   if(st->hasNext())testEquals(st->next(), "Hallo", "StringTokenizer NextToken fails (16)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (17)");
   if(st->hasNext())testEquals(st->next(), "Welt", "StringTokenizer NextToken fails (18)");
   testFalse(st->hasNext(), "StringTokenizer HasMoreTokens fails (19)");
   delete st;

   //3 Tokens
   st = new StringTokenizer("Hallo Welt", " ", true);
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (20)");
   if(st->hasNext())testEquals(st->next(), "Hallo", "StringTokenizer NextToken fails (21)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (22)");
   if(st->hasNext())testEquals(st->next(), " ", "StringTokenizer NextToken fails (23)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (24)");
   if(st->hasNext())testEquals(st->next(), "Welt", "StringTokenizer NextToken fails (24)");
   testFalse(st->hasNext(), "StringTokenizer HasMoreTokens fails (26)");
   delete st;

   //4 Tokens
   st = new StringTokenizer("Hallo  Welt", " ", true);
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (27)");
   if(st->hasNext())testEquals(st->next(), "Hallo", "StringTokenizer NextToken fails (28)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (29)");
   if(st->hasNext())testEquals(st->next(), " ", "StringTokenizer NextToken fails (30)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (31)");
   if(st->hasNext())testEquals(st->next(), " ", "StringTokenizer NextToken fails (32)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (33)");
   if(st->hasNext())testEquals(st->next(), "Welt", "StringTokenizer NextToken fails (34)");
   testFalse(st->hasNext(), "StringTokenizer HasMoreTokens fails (35)");
   delete st;

   //5 Tokens
   st = new StringTokenizer("Hallo  Welt!", "! ", true);
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (36)");
   if(st->hasNext())testEquals(st->next(), "Hallo", "StringTokenizer NextToken fails (37)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (38)");
   if(st->hasNext())testEquals(st->next(), " ", "StringTokenizer NextToken fails (39)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (40)");
   if(st->hasNext())testEquals(st->next(), " ", "StringTokenizer NextToken fails (41)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (42)");
   if(st->hasNext())testEquals(st->next(), "Welt", "StringTokenizer NextToken fails (43)");
   testTrue(st->hasNext(), "StringTokenizer HasMoreTokens fails (44)");
   if(st->hasNext())testEquals(st->next(), "!", "StringTokenizer NextToken fails (45)");
   testFalse(st->hasNext(), "StringTokenizer HasMoreTokens fails (46)");
   delete st;

}
