//
//  Character.cpp
//  jameo
//
//  Created by Uwe Runtemund on 17.01.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "Precompiled.h"


bool jm::CharacterIsWhitespace(uint16 input)
{
	switch(input)
	{
		case ' ':
		case '\r':
		case '\n':
		case '\t':
		case '\b':
		case '\f':
			return true;

		default:
			return false;
	}
}


bool jm::CharacterIsDigit(uint16 input)
{
	if(input >= '0' && input <= '9')return true;
	return false;
}

uint16 jm::CharacterToLowerCase(uint16 input)
{
	//Kodierung ist Unicode

	switch(input)
	{
		case 'A':
			return 'a';
		case 'B':
			return 'b';
		case 'C':
			return 'c';
		case 'D':
			return 'd';
		case 'E':
			return 'e';
		case 'F':
			return 'f';
		case 'G':
			return 'g';
		case 'H':
			return 'h';
		case 'I':
			return 'i';
		case 'J':
			return 'j';
		case 'K':
			return 'k';
		case 'L':
			return 'l';
		case 'M':
			return 'm';
		case 'N':
			return 'n';
		case 'O':
			return 'o';
		case 'P':
			return 'p';
		case 'Q':
			return 'q';
		case 'R':
			return 'r';
		case 'S':
			return 's';
		case 'T':
			return 't';
		case 'U':
			return 'u';
		case 'V':
			return 'v';
		case 'W':
			return 'w';
		case 'X':
			return 'x';
		case 'Y':
			return 'y';
		case 'Z':
			return 'z';

		case 0x00C4://Ä
			return 0x00E4;//ä

		case 0x00D6://Ö
			return 0x00F6;//ö

		case 0x00DC://Ü
			return 0x00FC;//ü

		default:
			return input;
	}
}

uint16 jm::CharacterToUpperCase(uint16 input)
{
	//Kodierung ist Unicode

	switch(input)
	{
		case 'a':
			return 'A';
		case 'b':
			return 'B';
		case 'c':
			return 'C';
		case 'd':
			return 'D';
		case 'e':
			return 'E';
		case 'f':
			return 'F';
		case 'g':
			return 'G';
		case 'h':
			return 'H';
		case 'i':
			return 'I';
		case 'j':
			return 'J';
		case 'k':
			return 'K';
		case 'l':
			return 'L';
		case 'm':
			return 'M';
		case 'n':
			return 'N';
		case 'o':
			return 'O';
		case 'p':
			return 'P';
		case 'q':
			return 'Q';
		case 'r':
			return 'R';
		case 's':
			return 'S';
		case 't':
			return 'T';
		case 'u':
			return 'U';
		case 'v':
			return 'V';
		case 'w':
			return 'W';
		case 'x':
			return 'X';
		case 'y':
			return 'Y';
		case 'z':
			return 'Z';

		case 0x00E4://ä
			return 0x00C4;//Ä

		case 0x00F6://ö
			return 0x00D6;//Ö

		case 0x00FC://ü
			return 0x00DC;//Ü

		default:
			return input;
	}
}
