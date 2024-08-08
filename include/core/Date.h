////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Date.h
// Library:     Jameo Core Library
// Purpose:     Date Operations
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

#ifndef jm_Date_h
#define jm_Date_h

#include "Types.h"
#include "String.h"

namespace jm
{

   /*!
    \brief Date represents a date or time.

    Internally, the time is stored in milliseconds from 01.01.1970 0:00 UTC. This time is referred
    to as absolute time in this context. Leap seconds are ignored.

    The basis of this implementation is the Date object from the ECMA standard.
    The basis is the Gregorian calendar.

    If the value is 0x800000000000 // -9223372036854775808 (minimum), then the date is considered
    "Empty" "Zero" "Nil"
    \ingroup core
    */
   class DllExport Date: public Comparable<Date>
   {
      public:

         /*!
          \brief Constant saves the millisecons of a day.
          */
         static const int64 MS_PER_DAY = 86400000;

         static const int64 HOURS_PER_DAY = 24;
         static const int64 MINUTES_PER_HOUR = 60;
         static const int64 SECONDS_PER_MINUTE = 60;
         static const int64 MS_PER_SECOND = 1000;
         static const int64 MS_PER_MINUTE = 60000;
         static const int64 MS_PER_HOUR = 3600000;

         // Constants for months.
         static const int16 JANUARY = 0;
         static const int16 FEBRUARY = 1;
         static const int16 MARCH = 2;
         static const int16 APRIL = 3;
         static const int16 MAY = 4;
         static const int16 JUNE = 5;
         static const int16 JULY = 6;
         static const int16 AUGUST = 7;
         static const int16 SEPTEMBER = 8;
         static const int16 OCTOBER = 9;
         static const int16 NOVEMBER = 10;
         static const int16 DECEMBER = 11;

         // Constants for week days.
         static const int16 SUNDAY = 0;
         static const int16 MONDAY = 1;
         static const int16 TUESDAY = 2;
         static const int16 WEDNESDAY = 3;
         static const int16 THURSDAY = 4;
         static const int16 FRIDAY = 5;
         static const int16 SATURDAY = 6;

         // Constant for Null.
         static const int64 EMPTY = 0x8000000000000000;

         /*!
          \brief Standard default constructor   ?       Standardkonstruktor
          */
         Date();

         /*!
          \brief Copyconstruktor
          */
         Date(const Date& other);

         /*!
          \brief Constructor 
          \param milliseconds Absolute time (UTC) passed in milliseconds since 01.01.1970 00:00:00.000.
          */
         Date(int64 milliseconds);

         /*!
          \brief Constructor 
          \param year Year
          \param month Month number (0-11)
          \param day Day number (1-31)
          */
         Date(uint16 year, uint16 month, uint16 day);

         /*!
          \brief Constructor 
          \param year Year
          \param month Month number (0-11)
          \param day Day number (1-31)
          \param hours Hours (0-23)
          \param minutes Minutes (0-59)
          \param seconds Seconds (0-59)
          \param millis Milliseconds (0-999)
          */
         Date(uint16 year, uint16 month, uint16 day, uint16 hours, uint16 minutes, uint16 seconds,
              uint16 millis);

         /*!
          \brief Constructor for a Date value given as a NSDate double value (typically on Mac)
          \param nsdate double value, representing the time in seconds relative to 00:00:00 UTC on
          1 January 2001.
          */
         static Date fromNSDate(double nsdate);

         /*!
          \brief Destructor
          */
         ~Date();

         /*!
          \brief Status, whether the data is empty
         */
         bool isEmpty() const;

         /*!
          \brief Returns the time passed in milliseconds, relative to 00:00:00 UTC on 1 January 1970.        
          */
         int64 time() const;

         /*!
          \brief Defines the time passed in milliseconds, relative to 00:00:00 UTC on 1 January 1970.
          \param t New time in UTC.  
          */
         void setTime(int64 t);

         /*!
          \brief Returns the year in local time.
          */
         int64 year() const;

         /*!
          \brief Returns the year in UTC time. 
          */
         int64 utcYear() const;

         /*!
          \brief Returns the month in local time. 
          \note The number ranges between 0 and 11
          */
         int64 month() const;

         /*!
          \brief Returns the month in UTC time 
          */
         int64 utcMonth() const;

         /*!
          \brief Returns the day of the month in local time
          */
         int64 date() const;

         /*!
          \brief Returns the day of the month in UTC time
          */
         int64 utcDate() const;

         /*!
          \brief Returns the day of the week in local time
          */
         int64 day() const;

         /*!
          \brief Returns the day of the week in UTC time
          */
         int64 utcDay() const;

         /*!
          \brief Returns the hours of the day in local time 
          */
         int64 hours() const;

         /*!
          \brief Returns the hours of the day in UTC time
          */
         int64 utcHours() const;

         /*!
          \brief Returns the minutes of the hour in local time 
          */
         int64 minutes() const;

         /*!
          \brief Returns the minutes of the hour in UTC time
          */
         int64 utcMinutes() const;

         /*!
          \brief Returns the seconds of the minute in local time
          */
         int64 seconds() const;

         /*!
          \brief Returns the day of the year
          */
         int64 dayOfYear()const;

         /*!
          \brief Returns the seconds of the minute in UTC time
          */
         int64 utcSeconds() const;

         /*!
          \brief Returns the milliseconds of the second in local time
          */
         int64 milliseconds() const;

         /*!
          \brief Returns the milliseconds of the second in UTC time
          */
         int64 utcMilliseconds() const;

         /*!
          \brief Returns the date in the default date format: YYYY-MM-DDThh:mm:ss.sssZ
          */
         String toString() const;

         /*!
          \brief This method compares the order of the data. 
          \param another The date used for the comparison. 
          */
         int32 compareTo(const Date& another) const;

         /*!
          \brief Implementing the operator <
         */
         DllExport
         friend bool operator<(Date const& v1, Date const& v2);

         /*!
         	\brief Implementing the operator >
           */
         DllExport
         friend bool operator>(Date const& v1, Date const& v2);

         /*!
         	\brief Implementing the operator <=
           */
         DllExport
         friend bool operator<=(Date const& v1, Date const& v2);

         /*!
         	\brief Implementing the operator >=
           */
         DllExport
         friend bool operator>=(Date const& v1, Date const& v2);

         /*!
          \brief Implementing the operator ==
          */
         DllExport
         friend bool operator==(Date const& v1, Date const& v2);

         /*!
          \brief Implementing the operator !=
          */
         DllExport
         friend bool operator!=(Date const& v1, Date const& v2);

      private:

         /*!
         \brief The absolute time passed in n milliseconds, relative to 00:00:00 UTC on 1 January 1970
         */
         int64 mTime;

         /*!
         \brief The helper method returns the day number. Day(t)=floor(t/msPerDay)
         msPerDay=86400 000
         \param t absolute time.
         */
         int64 day(int64 t) const;

         /*!
         \brief The helper method calculates the milliseconds in the current day 
         \param t absolute time.
         */
         int64 timeWithinDay(int64 t) const;

         /*!
         \brief The helper method calculates the number of days in the given year.
         \param y The year.
         */
         int64 DaysInYear(int64 y) const;

         /*!
         \brief The helper method returns the number of the first day of the year
         \param y The year.
         */
         int64 DayFromYear(int64 y) const;

         /*!
         \brief The helper method indicates the time value at the beginning of the year  
         \param y The year.
         */
         int64 TimeFromYear(int64 y) const;

         /*!
         \brief The helper method specifies the year to the given time value 
         \param t absolute time.
         */
         int64 YearFromTime(int64 t) const;

         /*!
         \brief The helper method returns 0 if the year is a non-leap year and a 1 if it is a leap year.
         \param t absolute time.
         */
         int16 InLeapYear(int64 t) const;

         /*!
         \brief The helper method Helfermethode gibt den Tag innerhalb eines Jahres an
         \param t absolute Zeit.
         */
         int64 DayWithinYear(int64 t) const;

         /*!
         \brief Helfermethode gibt den Monat der angegebenen Zeit zurück
         \param t absolute Zeit.
         \return Eine Zahl zwischen (einschließlich) 0 und (einschließlich) 11 (0 = Januar, 11=Dezember)
         */
         int64 MonthFromTime(int64 t) const;

         /*!
         \brief Helfermethode gibt den Tag in einem Monat zurück.
         \param t absolute Zeit.
         \return Eine Zahl zwischen (einschließlich) 1 und (einschließlich) 31
         */
         int64 DateFromTime(int64 t) const;

         /*!
         \brief Helfermethode gibt den Wochentag der Zeit zurück
         \param t absolute Zeit.
         \return Eine Zahl zwischen (einschließlich) 0 und (einschließlich) 6 (0=Sonntag, 6=Sammstag)
         */
         int64 WeekDay(int64 t) const;

         /*!
         \brief Diese Helfermethode gibt die lokale Zeitzonenjustierung zurück
         \return Differenz in ms
         */
         int64 LocalTimeZoneAdjustment() const;

         /*!
         \brief Diese Helfermethode gibt die Justierung durch Winter-/Sommerzeit zurück
         */
         int64 DaylightSavingTimeAdjustment() const;

         /*!
         \brief Helfermethode wandelt die abolute Zeit (UTC) in lokale Zeit um
         \param t absolute Zeit.
         */
         int64 LocalTime(int64 t) const;

         /*!
         \brief Helfermethode berechnet die absolute Zeit (UTC) aus lokaler ZEit
         \param t lokale Zeit.
         */
         int64 UTC(int64 t) const;

         /*!
         \brief Helfermethode berechnet die Stunde der Zeit
         \param t absolute Zeit.
         */
         int64 HourFromTime(int64 t) const;

         /*!
         \brief Helfermethode berechnet die Minute der Zeit
         \param t absolute Zeit.
         */
         int64 MinuteFromTime(int64 t) const;

         /*!
         \brief Helfermethode berechnet die Sekunde der Zeit
         \param t absolute Zeit.
         */
         int64 SecondFromTime(int64 t) const;

         /*!
         \brief Helfermethode berechnet die Millisekunde der Zeit
         \param t absolute Zeit.
         */
         int64 MilliFromTime(int64 t) const;

         /*!
         \brief Helfermethode berechnet die Zeit in Millisekunden aus ihren Argumenten
         */
         int64 MakeTime(int64 hour, int64 minute, int64 second, int64 milli) const;

         /*!
         \brief Helfermethode berechnet die Anzahl der Tage aus ihren Argumenten
         */
         int64 MakeDay(int64 year, int64 month, int64 date) const;

         /*!
         \brief Die Helfermethode berechnet die Anzahl der Millisekunden aus ihren Argumenten
         */
         int64 MakeDate(int64 day, int64 millis) const;


   };

   /*!
    \brief Gibt das Datum in einem formatierten String zurück. Dabei gibt es folgende Platzhalter:
    y : Jahr : 2015; 15
    M : Monat : Juli; Jul; 07; 7
    w: Kalenderwoche : 42
    W: Woche im Monat: 1
    D: Tag im Jahr: 142
    d: Tag im Monat: 24
    F: Wochentag im Monat: 2
    E: Wochentag: Dienstag; Di, D
    a: AM/PM-Markierung: AM;
    H: Stunde (0-23)
    K: Stunde (0-11)
    h: Stunde (1-12)
    k: Stunde (1-24)
    m: Minute der Stunde
    s: Sekunde der Minute
    S: Millisekunde
    z: Zeitzone

    Ergänzungen:
    Text: Wenn 4 oder mehr Buchstaben, Lange Form wird benutzt, andernfalls eine Kürze
    Jahr: Wenn Pattern = yy, dann ist

    Text kann durch ' ' markiert werden.
    */
   class DllExport DateFormatter: public Object
   {

      public:

         DateFormatter(const String& pattern);

         ~DateFormatter();

         String Format(const Date& date)const;

         static String Format(const String& format, const Date& date);

      private:

         enum PatternType
         {
            kEmpty,//Platzhalter
            kText,
            kYear,
            kMonthInYear,
            kWeekInYear,
            kDayInYear,
            kDayInMonth,
            kDayOfWeekInMonth,
            kDayInWeek,
            kAmPmMarker,
            kHourInDay0,
            kHourInDay1,
            kHourInAmPm0,
            kHourInAmPm1,
            kMinute,
            kSecond,
            kMillisecond,
            kTimezone
         };

         struct Pattern
         {
            //Verkettete Liste
            Pattern* next;

            //Pattern-Typ
            PatternType type;

            //Länge der Pattern
            uint8 length;

            //Text (Wenn Text)
            String text;

            Pattern();

            Pattern(const String& value, bool text = false);

            void AppendPattern(String& value, const Date& date) const;
         };

         Pattern* mPatterns;
         Pattern* mLast;

   };

}

#endif
