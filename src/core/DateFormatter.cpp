////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        DateFormatter.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of DateFormatter
//
// Author:      Uwe Runtemund (2015-today)
// Modified by:
// Created:     28.22.2015
//
// Copyright:   (c) 2015 Jameo Software, Germany. https://jameo.de
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

#include "Precompiled.h"

using namespace jm;

DateFormatter::DateFormatter(const String &pattern): Object()
{
   mPatterns = new Pattern();
   mPatterns->type = kEmpty;
   mLast = mPatterns;

   if(pattern.size() < 1)return;

   String token;
   bool inText = false;
   bool isText = false;

   for(uint32 a = 0; a < pattern.size(); a++)
   {
      Char c = pattern.charAt(a);

      if(c == '\'')
      {
         inText = !inText;
         if(inText)isText = true;
         else if(isText)
         {
            Pattern* tpattern = new Pattern(token, true);
            mLast->next = tpattern;
            mLast = tpattern;
            token.clear();
            isText = false;
         }
      }
      else if(inText)
      {
         token.append(c);
      }
      else
      {
         Char l = c;
         if(token.size() > 0)l = token.charAt(0);

         if(c != l)
         {
            Pattern* tpattern = new Pattern(token);
            mLast->next = tpattern;
            mLast = tpattern;

            token.clear();
            token.append(c);
         }
         else token.append(c);
      }
   }

   if(token.size() > 0)
   {
      Pattern* tpattern = new Pattern(token);
      mLast->next = tpattern;
      mLast = tpattern;
   }
}

DateFormatter::~DateFormatter()
{
   Pattern* p = mPatterns;
   while(p != NULL)
   {
      Pattern* tmp = p;
      p = p->next;
      delete tmp;
   }
}

String DateFormatter::Format(const Date &date) const
{
   String value;

   Pattern* p = mPatterns;
   while(p != NULL)
   {
      p->AppendPattern(value, date);
      p = p->next;
   }

   return value;
}


String DateFormatter::Format(const String& format, const Date& date)
{
   DateFormatter df = DateFormatter(format);
   return df.Format(date);
}


DateFormatter::Pattern::Pattern()
{
   next = NULL;
}

DateFormatter::Pattern::Pattern(const String &value, bool isText)
{
   next = NULL;

   if(isText)
   {
      text = value;
      type = kText;
   }
   else
   {
      length = (uint8)value.size();

      switch(value.charAt(0).unicode())
      {
         case 'y':
            type = kYear;
            break;

         case 'm':
            type = kMinute;
            break;

         case 'M':
            type = kMonthInYear;
            break;

         case 'd':
            type = kDayInMonth;
            break;

         case 'H':
            type = kHourInDay0;
            break;

         case 'E':
            type = kDayInWeek;
            break;

         case 's':
            type = kSecond;
            break;

         case 'S':
            type = kMillisecond;
            break;

         default:
            type = kText;
            text = value;
            break;
      }
   }
}


void DateFormatter::Pattern::AppendPattern(String &value, const Date &date) const
{
   switch(type)
   {
      case kEmpty:
         //Hier kommt nichts dazu...
         return;

      case kText:
         value.append(text);
         return;

      case kYear:
         if(length == 2)
         {
            int64 y = date.year() % 100;
            if(y < 10)value.append('0');
            value.append(String::valueOf(y));
         }
         else value.append(String::valueOf(date.year()));
         return;

      case kHourInDay0:
         if(length == 2)
         {
            int64 d = date.hours();
            if(d < 10)value.append('0');
            value.append(String::valueOf(d));
         }
         else value.append(String::valueOf(date.hours()));
         return;

      case kMinute:
         if(length == 2)
         {
            int64 d = date.minutes();
            if(d < 0)d = 0;
            if(d < 10)value.append('0');
            value.append(String::valueOf(d));
         }
         else value.append(String::valueOf(date.minutes()));
         return;

      case kSecond:
         if(length == 2)
         {
            int64 s = date.seconds();
            if(s < 10)value.append('0');
            value.append(String::valueOf(s));
         }
         else value.append(String::valueOf(date.seconds()));
         return;

      case kMillisecond:
         if(length > 1)
         {
            int64 s = date.milliseconds() ;
            if(s < 10)value.append('0');
            if(s < 100)value.append('0');
            value.append(String::valueOf(s));
         }
         else value.append(String::valueOf(date.milliseconds()));
         return;

      case kDayInMonth:
         if(length == 2)
         {
            int64 d = date.date();
            if(d < 0)d = 0;
            if(d < 10)value.append('0');
            value.append(String::valueOf(d));
         }
         else value.append(String::valueOf(date.date()));
         return;

      case kDayInWeek:
         if(length == 1)
         {
            switch(date.day())
            {
               case Date::MONDAY:
                  value.append("M");
                  return;

               case Date::TUESDAY:
                  value.append("D");
                  return;

               case Date::WEDNESDAY:
                  value.append("M");
                  return;

               case Date::THURSDAY:
                  value.append("D");
                  return;

               case Date::FRIDAY:
                  value.append("F");
                  return;

               case Date::SATURDAY:
                  value.append("S");
                  return;

               case Date::SUNDAY:
                  value.append("S");
                  return;
            }
         }
         else if(length == 2)
         {
            switch(date.day())
            {
               case Date::MONDAY:
                  value.append("Mo");
                  return;

               case Date::TUESDAY:
                  value.append("Di");
                  return;

               case Date::WEDNESDAY:
                  value.append("Mi");
                  return;

               case Date::THURSDAY:
                  value.append("Do");
                  return;

               case Date::FRIDAY:
                  value.append("Fr");
                  return;

               case Date::SATURDAY:
                  value.append("Sa");
                  return;

               case Date::SUNDAY:
                  value.append("So");
                  return;
            }
         }
         else
         {
            switch(date.day())
            {
               case Date::MONDAY:
                  value.append("Montag");
                  return;

               case Date::TUESDAY:
                  value.append("Dienstag");
                  return;

               case Date::WEDNESDAY:
                  value.append("Mittwoch");
                  return;

               case Date::THURSDAY:
                  value.append("Donnerstag");
                  return;

               case Date::FRIDAY:
                  value.append("Freitag");
                  return;

               case Date::SATURDAY:
                  value.append("Samstag");
                  return;

               case Date::SUNDAY:
                  value.append("Sonntag");
                  return;
            }
         }
         return;

      case kMonthInYear:
         if(length == 1)
         {
            value.append(String::valueOf(date.month() + 1));
         }
         else if(length == 2)
         {
            int64 m = date.month() + 1;
            if(m < 10)value.append('0');
            value.append(String::valueOf(m));
         }
         else if(length == 3)
         {
            switch(date.month())
            {
               case Date::JANUARY:
                  value.append("Jan");
                  return;

               case Date::FEBRUARY:
                  value.append("Feb");
                  return;

               case Date::MARCH:
                  value.append("Mrz");
                  return;

               case Date::APRIL:
                  value.append("Apr");
                  return;

               case Date::MAY:
                  value.append("Mai");
                  return;

               case Date::JUNE:
                  value.append("Jun");
                  return;

               case Date::JULY:
                  value.append("Jul");
                  return;

               case Date::AUGUST:
                  value.append("Aug");
                  return;

               case Date::SEPTEMBER:
                  value.append("Sep");
                  return;

               case Date::OCTOBER:
                  value.append("Okt");
                  return;

               case Date::NOVEMBER:
                  value.append("Nov");
                  return;

               case Date::DECEMBER:
                  value.append("Dez");
                  return;
            }
         }
         else
         {
            switch(date.month())
            {
               case Date::JANUARY:
                  value.append("Januar");
                  return;

               case Date::FEBRUARY:
                  value.append("Februar");
                  return;

               case Date::MARCH:
                  value.append("März");
                  return;

               case Date::APRIL:
                  value.append("April");
                  return;

               case Date::MAY:
                  value.append("Mai");
                  return;

               case Date::JUNE:
                  value.append("Juni");
                  return;

               case Date::JULY:
                  value.append("Juli");
                  return;

               case Date::AUGUST:
                  value.append(Tr("August"));
                  return;

               case Date::SEPTEMBER:
                  value.append("Septemper");
                  return;

               case Date::OCTOBER:
                  value.append("Oktober");
                  return;

               case Date::NOVEMBER:
                  value.append("November");
                  return;

               case Date::DECEMBER:
                  value.append("Dezember");
                  return;
            }
         }
         return;

      case kDayInYear:
         value.append(String::valueOf(date.dayOfYear() + 1));
         return;

      case kWeekInYear:
         break;

      case kDayOfWeekInMonth:
         break;

      case kAmPmMarker:
         break;

      case kHourInDay1:
         break;

      case kHourInAmPm0:
         break;

      case kHourInAmPm1:
         break;

      case kTimezone:
         break;
   }

}
