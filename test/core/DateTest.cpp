//
//  DateTest.cpp
//  test
//
//  Created by Uwe Runtemund on 07.05.22.
//  Copyright © 2022 Jameo Software. All rights reserved.
//

#include "DateTest.h"
#include "core/Date.h"

using namespace jm;

DateTest::DateTest(): Test()
{
   SetName("Test Date");
}

void DateTest::doTest()
{
   /*
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
    */

   // 01.01.1970 00:00:00.000
   Date d = Date(0);
   DateFormatter df1 = DateFormatter("dd.MM.yyyy HH:mm:ss.SSS");

   TestEquals(d.time(), (int64)0L, "jm::Date::Time() fails");
   TestEquals(d.toString(), "1970-01-01T00:00:00.000Z", "jm::Date::ToString() fails [1]");
   TestEquals(df1.Format(d), "01.01.1970 00:00:00.000", "jm::DateFormatter::Format() fails [1]");

   // 01.01.1970 00:00:00.001
   d = Date(1);
   TestEquals(d.time(), (int64)1L, "jm::Date::Time() fails");
   TestEquals(d.toString(), "1970-01-01T00:00:00.001Z", "jm::Date::ToString() fails [2]");
   TestEquals(df1.Format(d), "01.01.1970 00:00:00.001", "jm::DateFormatter::Format() fails [2]");

   // 01.01.1970 00:00:00.002
   d = Date(2);
   TestEquals(d.time(), (int64)2L, "jm::Date::Time() fails");
   TestEquals(d.toString(), "1970-01-01T00:00:00.002Z", "jm::Date::ToString() fails [3]");
   TestEquals(df1.Format(d), "01.01.1970 00:00:00.002", "jm::DateFormatter::Format() fails [3]");

   // 31.12.1969 23:59:59.999
   d = Date(-1);
   TestEquals(d.time(), (int64) - 1L, "jm::Date::Time() fails");
   TestEquals(d.toString(), "1969-12-31T23:59:59.999Z", "jm::Date::ToString() fails [4]");
   TestEquals(df1.Format(d), "31.12.1969 23:59:59.999", "jm::DateFormatter::Format() fails [4]");

   // 31.12.1969 23:59:59.998
   d = Date(-2);
   TestEquals(d.time(), (int64) - 2L, "jm::Date::Time() fails");
   TestEquals(d.toString(), "1969-12-31T23:59:59.998Z", "jm::Date::ToString() fails [5]");
   TestEquals(df1.Format(d), "31.12.1969 23:59:59.998", "jm::DateFormatter::Format() fails [5]");

   // 1. Jan. 1970   18:12:16
   d = Date(65536000);
   TestEquals(d.time(), (int64)65536000L, "jm::Date::Time() fails");
   TestEquals(d.toString(), "1970-01-01T18:12:16.000Z", "jm::Date::ToString() fails [6]");
   TestEquals(df1.Format(d), "01.01.1970 18:12:16.000", "jm::DateFormatter::Format() fails [6]");

   // 30. Juni 1961   02:35:44
   d = Date(-268435456000L);
   TestEquals(d.time(), -268435456000L, "jm::Date::Time() fails");
   TestEquals(d.toString(), "1961-06-30T02:35:44.000Z", "jm::Date::ToString() fails [7]");
   TestEquals(df1.Format(d), "30.06.1961 02:35:44.000", "jm::DateFormatter::Format() fails [7]");

   //01.01.1979
   d = Date(283996800000L);
   TestEquals(d.time(), 283996800000L, "jm::Date::Time() fails");
   TestEquals(d.toString(), "1979-01-01T00:00:00.000Z", "jm::Date::ToString() fails [8]");
   TestEquals(df1.Format(d), "01.01.1979 00:00:00.000", "jm::DateFormatter::Format() fails [8]");

   //01.08.1979
   d = Date(302313600000L);
   TestEquals(d.time(), 302313600000L, "jm::Date::Time() fails");
   TestEquals(d.toString(), "1979-08-01T00:00:00.000Z", "jm::Date::ToString() fails [9]");
   TestEquals(df1.Format(d), "01.08.1979 00:00:00.000", "jm::DateFormatter::Format() fails [9]");

   //24.08.1979
   d = Date(1979, Date::AUGUST, 24);
   TestEquals(d.toString(), "1979-08-24T00:00:00.000Z", "jm::Date::ToString() fails [10]");
   TestEquals(df1.Format(d), "24.08.1979 00:00:00.000", "jm::DateFormatter::Format() fails [10]");

   //#warning TODO Diese Funktion testen
   d = Date();
   std::cout << d.toString() << std::endl;
}
