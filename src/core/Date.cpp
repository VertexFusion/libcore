////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Date.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of Date
//
// Author:      Uwe Runtemund (2014-today)
// Modified by:
// Created:     11.11.2014
//
// Copyright:   (c) 2014 Jameo Software, Germany. https://jameo.de
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


#include "Precompiled.hpp"

using namespace jm;


Date::Date(): Comparable<Date>()
{
   #ifdef __APPLE__
   struct timeval tp;
   gettimeofday(&tp, NULL);
   mTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;
   #elif defined __linux__//Linux
   struct timeval tp;
   gettimeofday(&tp, NULL);
   mTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;
   #elif defined _WIN32
   std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>
                                  (std::chrono::system_clock::now().time_since_epoch());
   mTime = ms.count();
   #endif
}

Date::Date(const Date& other): Comparable<Date>()
{
   mTime = other.mTime;
}

Date::Date(int64 milliseconds): Comparable<Date>()
{
   mTime = milliseconds;
}

Date::Date(uint16 year, uint16 month, uint16 day): Comparable<Date>()
{
   mTime = UTC(MakeDate(MakeDay(year, month, day), 0));
}

Date::Date(uint16 year,
           uint16 month,
           uint16 day,
           uint16 hours,
           uint16 minutes,
           uint16 seconds,
           uint16 millis): Comparable<Date>()
{
   mTime = UTC(MakeDate(MakeDay(year, month, day), MakeTime(hours, minutes, seconds, millis)));
}

Date Date::fromNSDate(double nsdate)
{
   Date d;
   //Milliseconds since 01.01.1970 00:00:00.000.
   d.mTime = 978307200000;
   int64 date = static_cast<int64>(nsdate * 1000.0); //s in ms
   d.mTime += date;

   return d;
}

Date::~Date()
{
   mTime = 0;
}

int64 Date::day(int64 t) const
{
   return divFloor(t, MS_PER_DAY) ;
}

int64 Date::timeWithinDay(int64 t) const
{
   return t % MS_PER_DAY;
}

int64 Date::DaysInYear(int64 y) const
{
   if(y % 4 != 0)return 365;
   if(y % 100 != 0)return 366;
   if(y % 400 != 0)return 365;
   return 366;
}

int64 Date::DayFromYear(int64 y) const
{
   return 365 * (y - 1970)
          + divFloor(y - 1969, 4)
          - divFloor(y - 1901, 100)
          + divFloor(y - 1601, 400);
}

int64 Date::TimeFromYear(int64 y) const
{
   return MS_PER_DAY * DayFromYear(y);
}

int64 Date::YearFromTime(int64 t) const
{
   int64 startYear = 1970;

   if(t >= 0)
   {
      while(TimeFromYear(startYear) <= t)
      {
         startYear++;
      }
      return startYear - 1;
   }
   else
   {
      while(TimeFromYear(startYear) > t)
      {
         startYear--;
      }
      return startYear;
   }
}

int16 Date::InLeapYear(int64 t) const
{
   int64 diy = DaysInYear(YearFromTime(t));
   if(diy == 365)return 0;
   if(diy == 366)return 1;
   return -1;
}

int64 Date::DayWithinYear(int64 t) const
{
   return day(t) - DayFromYear(YearFromTime(t));
}

int64 Date::MonthFromTime(int64 t) const
{
   int64 dwy = DayWithinYear(t);
   int64 ily = InLeapYear(t);

   if(0 <= dwy && dwy < 31) return JANUARY;
   if(31 <= dwy && dwy < 59 + ily) return FEBRUARY;
   if(59 + ily <= dwy && dwy < 90 + ily) return MARCH;
   if(90 + ily <= dwy && dwy < 120 + ily) return APRIL;
   if(120 + ily <= dwy && dwy < 151 + ily) return MAY;
   if(151 + ily <= dwy && dwy < 181 + ily) return JUNE;
   if(181 + ily <= dwy && dwy < 212 + ily) return JULY;
   if(212 + ily <= dwy && dwy < 243 + ily) return AUGUST;
   if(243 + ily <= dwy && dwy < 273 + ily) return SEPTEMBER;
   if(273 + ily <= dwy && dwy < 304 + ily) return OCTOBER;
   if(304 + ily <= dwy && dwy < 334 + ily) return NOVEMBER;
   if(334 + ily <= dwy && dwy < 365 + ily) return DECEMBER;

   return -1;
}

int64 Date::DateFromTime(int64 t) const
{
   int64 dwy = DayWithinYear(t);
   int64 ily = InLeapYear(t);
   int64 mft = MonthFromTime(t);

   switch(mft)
   {
      case JANUARY:
         return dwy + 1;

      case FEBRUARY:
         return dwy - 30;

      case MARCH:
         return dwy - 58 - ily;

      case APRIL:
         return dwy - 89 - ily;

      case MAY:
         return dwy - 119 - ily;

      case JUNE:
         return dwy - 150 - ily;

      case JULY:
         return dwy - 180 - ily;

      case AUGUST:
         return dwy - 211 - ily;

      case SEPTEMBER:
         return dwy - 242 - ily;

      case OCTOBER:
         return dwy - 272 - ily;

      case NOVEMBER:
         return dwy - 303 - ily;

      case DECEMBER:
         return dwy - 333 - ily;

      default:
         return -1;
   }
}

int64 Date::WeekDay(int64 t) const
{
   //01.01.1970 = Donnerstag (=4)
   return (day(t) + 4) % 7;
}

int64 Date::LocalTimeZoneAdjustment() const
{
   return 0;//\todo
}

int64 Date::DaylightSavingTimeAdjustment() const
{
   return 0;//\todo
}

int64 Date::LocalTime(int64 t) const
{
   return t + LocalTimeZoneAdjustment() + DaylightSavingTimeAdjustment();//\todo
}

int64 Date::UTC(int64 t) const
{
   return t - LocalTimeZoneAdjustment() - DaylightSavingTimeAdjustment();//\todo
}

int64 Date::HourFromTime(int64 t) const
{
   return modFloor(divFloor(t, MS_PER_HOUR), HOURS_PER_DAY);
}

int64 Date::MinuteFromTime(int64 t) const
{
   return modFloor(divFloor(t, MS_PER_MINUTE), MINUTES_PER_HOUR);
}

int64 Date::SecondFromTime(int64 t) const
{
   return modFloor(divFloor(t, MS_PER_SECOND), SECONDS_PER_MINUTE);
}

int64 Date::MilliFromTime(int64 t) const
{
   return modFloor(t, MS_PER_SECOND);
}

int64 Date::MakeTime(int64 hour, int64 minute, int64 second, int64 milli) const
{
   return hour * MS_PER_HOUR + minute * MS_PER_MINUTE + second * MS_PER_SECOND + milli;
}

int64 Date::MakeDay(int64 year, int64 month, int64 date) const
{
   int64 theYear = year + divFloor(month, 12);
   int64 theMonth = month % 12;

   //Find t with: (==r7)
   //YearFromTime(t) == r5
   //MonthFromTime(t) == r6
   //DateFromTime(t) ==1

   //Reverse YearFromTime
   int64 tfy = TimeFromYear(theYear);

   //Reverse MonthFromTime
   int64 ily = InLeapYear(tfy);
   int64 tfm = 0;
   switch(theMonth)
   {
      case JANUARY:
         tfm = 0 * MS_PER_DAY;
         break;

      case FEBRUARY:
         tfm = 31 * MS_PER_DAY;
         break;

      case MARCH:
         tfm = (59 + ily) * MS_PER_DAY;
         break;

      case APRIL:
         tfm = (90 + ily) * MS_PER_DAY;
         break;

      case MAY:
         tfm = (120 + ily) * MS_PER_DAY;
         break;

      case JUNE:
         tfm = (151 + ily) * MS_PER_DAY;
         break;

      case JULY:
         tfm = (181 + ily) * MS_PER_DAY;
         break;

      case AUGUST:
         tfm = (212 + ily) * MS_PER_DAY;
         break;

      case SEPTEMBER:
         tfm = (243 + ily) * MS_PER_DAY;
         break;

      case OCTOBER:
         tfm = (273 + ily) * MS_PER_DAY;
         break;

      case NOVEMBER:
         tfm = (304 + ily) * MS_PER_DAY;
         break;

      case DECEMBER:
         tfm = (334 + ily) * MS_PER_DAY;
         break;

      default:
         tfm = 0xFFFFFFFFFFFFFFFFLL;
         break;
   }

   int64 r7 = tfy + tfm;

   return day(r7) + date - 1;
}

int64 Date::MakeDate(int64 day, int64 millis) const
{
   return day * MS_PER_DAY + millis;
}

bool Date::isEmpty() const
{
   return mTime == EMPTY;
}

int64 Date::time() const
{
   return mTime;
}

void Date::setTime(int64 t)
{
   mTime = t;
}

int64 Date::year() const
{
   return YearFromTime(LocalTime(mTime));
}

int64 Date::utcYear() const
{
   return YearFromTime(mTime);
}

int64 Date::month() const
{
   return MonthFromTime(LocalTime(mTime));
}

int64 Date::utcMonth() const
{
   return MonthFromTime(mTime);
}

int64 Date::date() const
{
   return DateFromTime(LocalTime(mTime));
}

int64 Date::utcDate() const
{
   return DateFromTime(mTime);
}

int64 Date::day() const
{
   return WeekDay(LocalTime(mTime));
}

int64 Date::dayOfYear()const
{
   return DayWithinYear(LocalTime(mTime));
}

int64 Date::utcDay() const
{
   return WeekDay(mTime);
}

int64 Date::hours() const
{
   return HourFromTime(LocalTime(mTime));
}

int64 Date::utcHours() const
{
   return HourFromTime(mTime);
}

int64 Date::minutes() const
{
   return MinuteFromTime(LocalTime(mTime));
}

int64 Date::utcMinutes() const
{
   return MinuteFromTime(mTime);
}

int64 Date::seconds() const
{
   return SecondFromTime(LocalTime(mTime));
}

int64 Date::utcSeconds() const
{
   return SecondFromTime(mTime);
}

int64 Date::milliseconds() const
{
   return MilliFromTime(LocalTime(mTime));
}

int64 Date::utcMilliseconds() const
{
   return MilliFromTime(mTime);
}

String Date::toString() const
{
   char pre[] = "0000-00-00T00:00:00.000Z\0";

   int year = utcYear() % 10000;
   pre[0] = static_cast<char>('0' + year / 1000);
   year = year % 1000;
   pre[1] = static_cast<char>('0' + year / 100);
   year = year % 100;
   pre[2] = static_cast<char>('0' + year / 10);
   pre[3] = static_cast<char>('0' + year % 10);

   int month = 1 + utcMonth() % 100;
   pre[5] = static_cast<char>('0' + month / 10);
   pre[6] = static_cast<char>('0' + month % 10);

   int day = utcDate() % 100;
   pre[8] = static_cast<char>('0' + day / 10);
   pre[9] = static_cast<char>('0' + day % 10);

   int hour = utcHours() % 100;
   pre[11] = static_cast<char>('0' + hour / 10);
   pre[12] = static_cast<char>('0' + hour % 10);

   int minute = utcMinutes() % 100;
   pre[14] = static_cast<char>('0' + minute / 10);
   pre[15] = static_cast<char>('0' + minute % 10);

   int second = utcSeconds() % 100;
   pre[17] = static_cast<char>('0' + second / 10);
   pre[18] = static_cast<char>('0' + second % 10);

   int millis = utcMilliseconds() % 1000;
   pre[20] = static_cast<char>('0' + millis / 100);
   millis = millis % 100;
   pre[21] = static_cast<char>('0' + millis / 10);
   pre[22] = static_cast<char>('0' + millis % 10);

   return String(pre);
}

int32 Date::compareTo(const Date& another) const
{
   if(mTime < another.mTime)return -1;
   if(mTime > another.mTime)return 1;
   return 0;
}

bool jm::operator<(Date const& v1, Date const& v2)
{
   return v1.mTime < v2.mTime;
}

bool jm::operator<=(Date const& v1, Date const& v2)
{
   return v1.mTime <= v2.mTime;
}

bool jm::operator>(Date const& v1, Date const& v2)
{
   return v1.mTime > v2.mTime;
}

bool jm::operator>=(Date const& v1, Date const& v2)
{
   return v1.mTime >= v2.mTime;
}

bool jm::operator!=(Date const& v1, Date const& v2)
{
   return v1.mTime != v2.mTime;
}


bool jm::operator==(Date const& v1, Date const& v2)
{
   return v1.mTime == v2.mTime;
}
