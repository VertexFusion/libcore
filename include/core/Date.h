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
			 \brief Konstante gibt die Millisekunden pro Tag zurück
			 */
			static const int64 MS_PER_DAY = 86400000;

			static const int64 HOURS_PER_DAY = 24;
			static const int64 MINUTES_PER_HOUR = 60;
			static const int64 SECONDS_PER_MINUTE = 60;
			static const int64 MS_PER_SECOND = 1000;
			static const int64 MS_PER_MINUTE = 60000;
			static const int64 MS_PER_HOUR = 3600000;

			//Konstanten für die Monate
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

			//Konstanten für Wochentage
			static const int16 SUNDAY = 0;
			static const int16 MONDAY = 1;
			static const int16 TUESDAY = 2;
			static const int16 WEDNESDAY = 3;
			static const int16 THURSDAY = 4;
			static const int16 FRIDAY = 5;
			static const int16 SATURDAY = 6;

			//Konstante für Null
			static const int64 EMPTY = 0x8000000000000000;

			/*!
			 \brief Standardkonstruktor
			 */
			Date();

			/*!
			 \brief Copyconstruktor
			 */
			Date(const Date &other);

			/*!
			 \brief Konstruktor
			 \param milliseconds Absolute Zeit (UTC) in Millisekunden ab dem 01.01.1970 00:00:00.000
			 */
			Date(int64 milliseconds);

			/*!
			 \brief Konstruktor
			 \param year Die Jahreszahl
			 \param month Die Monatszahl (0-11)
			 \param day Die Tageszahl (1-31)
			 */
			Date(uint16 year, uint16 month, uint16 day);

			/*!
			 \brief Konstruktor
			 \param year Die Jahreszahl
			 \param month Die Monatszahl (0-11)
			 \param day Die Tageszahl (1-31)
			 \param hours Die Stunden (0-23)
			 \param minutes Die Minuten (0-59)
			 \param seconds Die Sekunden (0-59)
			 \param millis Die Millisekunden (0-999)
			 */
			Date(uint16 year, uint16 month, uint16 day, uint16 hours, uint16 minutes, uint16 seconds, uint16 millis);

			/*!
			 \brief Destructor
			 */
			~Date();

			/*!
			 \brief Status, ob das Daten leer ist
			*/
			bool IsEmpty() const;

			/*!
			 \brief Gibt die Zeit in Millisekunden seit Mitternacht des 01.01.1970 in UTC zurück
			 */
			int64 GetTime() const;

			/*!
			 \brief Legt die Zeit in Millisekunden seit Mitternach des 01.01.1970 in UTC fest.
			 \param t Neue Zeit in UTC
			 */
			void SetTime(int64 t);

			/*!
			 \brief Gibt das Jahr in lokaler Zeit zurück
			 */
			int64 GetYear() const;

			/*!
			 \brief Gibt das Jahr in UTC-Zeit zurück
			 */
			int64 GetUTCYear() const;

			/*!
			 \brief Gibt den Monat in lokaler Zeit zurück.
			 \note Die Zahl ist im Bereich 0-11
			 */
			int64 GetMonth() const;

			/*!
			 \brief Gibt den Monat in UTC-Zeit zurück
			 */
			int64 GetUTCMonth() const;

			/*!
			 \brief Gibt den Tag im Monat in lokaler Zeit zurück
			 */
			int64 GetDate() const;

			/*!
			 \brief Gibt den Tag im Monat in UTC-Zeit zurück
			 */
			int64 GetUTCDate() const;

			/*!
			 \brief Gibt den Tag in der Woche in lokaler Zeit zurück
			 */
			int64 GetDay() const;

			/*!
			 \brief Gibt den Tag in der Woche in UTC-Zeit zurück
			 */
			int64 GetUTCDay() const;

			/*!
			 \brief Gibt die Stunden des Tages in lokaler Zeit zurück
			 */
			int64 GetHours() const;

			/*!
			 \brief Gibt die Stunden des Tages in UTC-Zeit zurück
			 */
			int64 GetUTCHours() const;

			/*!
			 \brief Gibt die Minuten der Stunde in lokaler Zeit zurück
			 */
			int64 GetMinutes() const;

			/*!
			 \brief Gibt die Minuten der Stunde in UTC-Zeit zurück
			 */
			int64 GetUTCMinutes() const;

			/*!
			 \brief Gibt die Sekunden der Minute in lokaler Zeit zurück
			 */
			int64 GetSeconds() const;

			/*!
			 \brief Gibt den Tag des Jahres zurück
			 */
			int64 GetDayOfYear()const;

			/*!
			 \brief Gibt die Sekunden der Minute in UTC-Zeit zurück
			 */
			int64 GetUTCSeconds() const;

			/*!
			 \brief Gibt die Millisekunden der Sekunde in lokaler Zeit zurück
			 */
			int64 GetMilliseconds() const;

			/*!
			 \brief Gibt die Millisekunden der Sekunde in UTC-Zeit zurück
			 */
			int64 GetUTCMilliseconds() const;

			/*!
			 \brief Gibt das Datum im Standardformat zurück: YYYY-MM-DDThh:mm:ss.sssZ
			 */
			String ToString() const;

			/*!
			 \brief Diese Methode vergleicht die Reihenfolge der Daten.
			 \param another Das Datum, mit der dieses verglichen wird.
			 */
			int32 CompareTo(const Date &another) const;

			/*!
			 \brief Implementierung des Operators <
			*/
			DllExport
			friend bool operator<(Date const &v1, Date const &v2);

			/*!
				\brief Implementierung des Operators >
			  */
			DllExport
			friend bool operator>(Date const &v1, Date const &v2);

			/*!
				\brief Implementierung des Operators <=
			  */
			DllExport
			friend bool operator<=(Date const &v1, Date const &v2);

			/*!
				\brief Implementierung des Operators >=
			  */
			DllExport
			friend bool operator>=(Date const &v1, Date const &v2);

			/*!
			 \brief Implementierung des Operators ==
			 */
			DllExport
			friend bool operator==(Date const &v1, Date const &v2);

			/*!
			 \brief Implementierung des Operators !=
			 */
			DllExport
			friend bool operator!=(Date const &v1, Date const &v2);

		private:

			/*!
			\brief Die absolute Zeit in n Millisekunden ab dem 01.01.1970 0:00 Uhr UTC
			*/
			int64 mTime;

			/*!
			\brief Helfermethode gibt die Tagesnummer zurück. Day(t)=floor(t/msPerDay)
			msPerDay=86400 000
			\param t absolute Zeit.
			*/
			int64 Day(int64 t) const;

			/*!
			\brief Helfermethode berechnet die Millisekungen im aktuellen Tag
			\param t absolute Zeit.
			*/
			int64 TimeWithinDay(int64 t) const;

			/*!
			\brief Helfermethode berechnet die Anzahl der Tage im angebenen Jahr
			\param y Das Jahr.
			*/
			int64 DaysInYear(int64 y) const;

			/*!
			\brief Helfermethode gibt die Tagessnummer des ersten Tages im Jahr zurück
			\param y Das Jahr.
			*/
			int64 DayFromYear(int64 y) const;

			/*!
			\brief Helfermethode gibt den Zeitwert des Jahresbeginns an
			\param y Das Jahr.
			*/
			int64 TimeFromYear(int64 y) const;

			/*!
			\brief Helfermethode gibt das Jahr des angegebenen Zeitwertes an
			\param t absolute Zeit.
			*/
			int64 YearFromTime(int64 t) const;

			/*!
			\brief Helfermethode gibt 0 zurück, wenn man sich in einem normalen Jahr befindet und
			1, wenn man sich in einem Schaltjahr befindet
			\param t absolute Zeit.
			*/
			int16 InLeapYear(int64 t) const;

			/*!
			\brief Helfermethode gibt den Tag innerhalb eines Jahres an
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

			DateFormatter(const String &pattern);

			~DateFormatter();

			String Format(const Date &date)const;

			static String Format(const String &format, const Date &date);

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

				Pattern(const String &value, bool text = false);

				void AppendPattern(String &value, const Date &date) const;
			};

			Pattern* mPatterns;
			Pattern* mLast;

	};

}

#endif
