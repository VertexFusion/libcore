//
//  DateFormatter.cpp
//  jameo
//
//  Created by Uwe Runtemund on 17.11.15.
//  Copyright © 2015 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

DateFormatter::DateFormatter(const String &pattern): Object()
{
	mPatterns = new Pattern();
	mPatterns->type = kEmpty;
	mLast = mPatterns;

	if(pattern.Length() < 1)return;

	String token;
	bool inText = false;
	bool isText = false;

	for(uint32 a = 0; a < pattern.Length(); a++)
	{
		uint16 c = pattern.CharAt(a);

		if(c == '\'')
		{
			inText = !inText;
			if(inText)isText = true;
			else if(isText)
			{
				Pattern* tpattern = new Pattern(token, true);
				mLast->next = tpattern;
				mLast = tpattern;
				token.Clear();
				isText = false;
			}
		}
		else if(inText)
		{
			token.Append(c);
		}
		else
		{
			uint16 l = c;
			if(token.Length() > 0)l = token.CharAt(0);

			if(c != l)
			{
				Pattern* tpattern = new Pattern(token);
				mLast->next = tpattern;
				mLast = tpattern;

				token.Clear();
				token.Append(c);
			}
			else token.Append(c);
		}
	}

	if(token.Length() > 0)
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
		length = (uint8)value.Length();

		switch(value.CharAt(0))
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
			value.Append(text);
			return;

		case kYear:
			if(length == 2)
			{
				int64 y = date.GetYear() % 100;
				if(y < 10)value.Append('0');
				value.Append(String::ValueOf(y));
			}
			else value.Append(String::ValueOf(date.GetYear()));
			return;

		case kHourInDay0:
			if(length == 2)
			{
				int64 d = date.GetHours();
				if(d < 10)value.Append('0');
				value.Append(String::ValueOf(d));
			}
			else value.Append(String::ValueOf(date.GetHours()));
			return;

		case kMinute:
			if(length == 2)
			{
				int64 d = date.GetMinutes();
				if(d < 0)d = 0;
				if(d < 10)value.Append('0');
				value.Append(String::ValueOf(d));
			}
			else value.Append(String::ValueOf(date.GetMinutes()));
			return;

		case kSecond:
			if(length == 2)
			{
				int64 s = date.GetSeconds();
				if(s < 10)value.Append('0');
				value.Append(String::ValueOf(s));
			}
			else value.Append(String::ValueOf(date.GetSeconds()));
			return;

		case kMillisecond:
			if(length > 1)
			{
				int64 s = date.GetMilliseconds() ;
				if(s < 10)value.Append('0');
				if(s < 100)value.Append('0');
				value.Append(String::ValueOf(s));
			}
			else value.Append(String::ValueOf(date.GetMilliseconds()));
			return;

		case kDayInMonth:
			if(length == 2)
			{
				int64 d = date.GetDate();
				if(d < 0)d = 0;
				if(d < 10)value.Append('0');
				value.Append(String::ValueOf(d));
			}
			else value.Append(String::ValueOf(date.GetDate()));
			return;

		case kDayInWeek:
			if(length == 1)
			{
				switch(date.GetDay())
				{
					case Date::MONDAY:
						value.Append("M");
						return;

					case Date::TUESDAY:
						value.Append("D");
						return;

					case Date::WEDNESDAY:
						value.Append("M");
						return;

					case Date::THURSDAY:
						value.Append("D");
						return;

					case Date::FRIDAY:
						value.Append("F");
						return;

					case Date::SATURDAY:
						value.Append("S");
						return;

					case Date::SUNDAY:
						value.Append("S");
						return;
				}
			}
			else if(length == 2)
			{
				switch(date.GetDay())
				{
					case Date::MONDAY:
						value.Append("Mo");
						return;

					case Date::TUESDAY:
						value.Append("Di");
						return;

					case Date::WEDNESDAY:
						value.Append("Mi");
						return;

					case Date::THURSDAY:
						value.Append("Do");
						return;

					case Date::FRIDAY:
						value.Append("Fr");
						return;

					case Date::SATURDAY:
						value.Append("Sa");
						return;

					case Date::SUNDAY:
						value.Append("So");
						return;
				}
			}
			else
			{
				switch(date.GetDay())
				{
					case Date::MONDAY:
						value.Append("Montag");
						return;

					case Date::TUESDAY:
						value.Append("Dienstag");
						return;

					case Date::WEDNESDAY:
						value.Append("Mittwoch");
						return;

					case Date::THURSDAY:
						value.Append("Donnerstag");
						return;

					case Date::FRIDAY:
						value.Append("Freitag");
						return;

					case Date::SATURDAY:
						value.Append("Samstag");
						return;

					case Date::SUNDAY:
						value.Append("Sonntag");
						return;
				}
			}
			return;

		case kMonthInYear:
			if(length == 1)
			{
				value.Append(String::ValueOf(date.GetMonth() + 1));
			}
			else if(length == 2)
			{
				int64 m = date.GetMonth() + 1;
				if(m < 10)value.Append('0');
				value.Append(String::ValueOf(m));
			}
			else if(length == 3)
			{
				switch(date.GetMonth())
				{
					case Date::JANUARY:
						value.Append("Jan");
						return;

					case Date::FEBRUARY:
						value.Append("Feb");
						return;

					case Date::MARCH:
						value.Append("Mrz");
						return;

					case Date::APRIL:
						value.Append("Apr");
						return;

					case Date::MAY:
						value.Append("Mai");
						return;

					case Date::JUNE:
						value.Append("Jun");
						return;

					case Date::JULY:
						value.Append("Jul");
						return;

					case Date::AUGUST:
						value.Append("Aug");
						return;

					case Date::SEPTEMBER:
						value.Append("Sep");
						return;

					case Date::OCTOBER:
						value.Append("Okt");
						return;

					case Date::NOVEMBER:
						value.Append("Nov");
						return;

					case Date::DECEMBER:
						value.Append("Dez");
						return;
				}
			}
			else
			{
				switch(date.GetMonth())
				{
					case Date::JANUARY:
						value.Append("Januar");
						return;

					case Date::FEBRUARY:
						value.Append("Februar");
						return;

					case Date::MARCH:
						value.Append("März");
						return;

					case Date::APRIL:
						value.Append("April");
						return;

					case Date::MAY:
						value.Append("Mai");
						return;

					case Date::JUNE:
						value.Append("Juni");
						return;

					case Date::JULY:
						value.Append("Juli");
						return;

					case Date::AUGUST:
						value.Append("August");
						return;

					case Date::SEPTEMBER:
						value.Append("Septemper");
						return;

					case Date::OCTOBER:
						value.Append("Oktober");
						return;

					case Date::NOVEMBER:
						value.Append("November");
						return;

					case Date::DECEMBER:
						value.Append("Dezember");
						return;
				}
			}
			return;

		case kDayInYear:
			value.Append(String::ValueOf(date.GetDayOfYear() + 1));
			return;
	}

}
