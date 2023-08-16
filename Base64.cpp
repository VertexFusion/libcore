//
//  Base64.cpp
//  jameo
//
//  Created by Uwe Runtemund on 28.12.20.
//  Copyright © 2020 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;


const uint8 gBase64fillchar = '=';
const uint8 gBase64cvt[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const uint8 gBase64rcvt[] =
{
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66, //0
	64, 66, 66, 66, 66, 66, 66, 66, 66, 66,
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
	66, 66, 66, 62, 66, 66, 66, 63, 52, 53,

	54, 55, 56, 57, 58, 59, 60, 61, 66, 66, //50
	66, 65, 66, 66, 66, 0, 1, 2, 3, 4,
	5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 66, 66, 66, 66, 66, 66, 26, 27, 28,

	29, 30, 31, 32, 33, 34, 35, 36, 37, 38, //100
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 66, 66, 66, 66, 66, 66, 66,
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,

	66, 66, 66, 66, 66, 66, 66, 66, 66, 66, //150
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,

	66, 66, 66, 66, 66, 66, 66, 66, 66, 66, //200
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
	66, 66, 66, 66, 66, 66, 66, 66, 66, 66,

	66, 66, 66, 66, 66, 66
};//250

uint8* Base64::Encode(const uint8* data, uint32 &length)
{
	uint8 c1 = 0, c2 = 0, c3 = 0, c4 = 0, b1, b2, b3;
	uint32 len = length;
	uint32 lenb64 = ((len / 3) + 1) * 4;

	uint8* ret = new uint8[lenb64];

	uint32 index = 0;

	for(uint32 i = 0; i < len; i += 3)
	{
		b1 = data[i];
		b2 = data[i + 1];
		b3 = data[i + 2];

		//1. Buchstabe
		c1 = (b1 >> 2) & 0x3f; //mask 00111111

		//2. Buchstabe
		c2 = (b1 << 4) & 0x3f; //mask 00111111
		if(i + 1 < len)
		{
			c2 |= (b2 >> 4) & 0x0f;//mask 00001111

			//3. Buchstabe 00111100
			c3 = (b2 << 2) & 0x3f;//mask 00111111
			if(i + 2 < len)
			{
				c3 |= (b3 >> 6) & 0x03;//mask 00000011

				//4. Buchstabe
				c4 = b3 & 0x3f;//mask 00111111
			}
		}

		ret[index++] = gBase64cvt[c1];
		ret[index++] = gBase64cvt[c2];
		ret[index++] = (i + 1 < len) ? gBase64cvt[c3] : gBase64fillchar;
		ret[index++] = (i + 2 < len) ? gBase64cvt[c4] : gBase64fillchar;

	}
	length = index;
	if(index > lenb64)throw new Exception("Array overflow! Algorithm wrong");
	return ret;
}

uint8* Base64::Decode(const uint8* data, uint32 &length)
{
	uint8 c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	uint8 b1 = 0, b2 = 0, b3 = 0;
	int len = length;

	uint32 lenb64 = (len * 3) / 4 ;

	uint8* ret = new uint8[lenb64];
	uint32 index = 0;
	bool brk = false;

	for(int32 i = 0; i < len; i = i + 4)
	{
		c1 = gBase64rcvt[data[i]];
		c2 = gBase64rcvt[data[i + 1]];
		c3 = gBase64rcvt[data[i + 2]];
		c4 = gBase64rcvt[data[i + 3]];

		if(c2 >= 65)
		{
			c2 = 0;
			brk = true;
		}
		b1 = ((c1 << 2) | ((c2 >> 4) & 0x3));
		ret[index++] = b1;
		if(brk)break;


		if(c3 >= 65)
		{
			c3 = 0;
			brk = true;
		}
		b2 = ((c2 << 4) & 0xf0) | ((c3 >> 2) & 0xf);
		ret[index++] = b2;
		if(brk)break;

		if(c4 >= 65)
		{
			c4 = 0;
			brk = true;
		}
		b3 = ((c3 << 6) & 0xc0) | c4;
		ret[index++] = b3;
		if(brk)break;

	}
	length = index;
	return ret;
}
