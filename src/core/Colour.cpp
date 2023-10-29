////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Character.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of Colour
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     08.05.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
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

#ifdef __APPLE__//macOS, iOS
using std::min;
using std::max;
#elif defined __linux__ //Linux
using std::min;
using std::max;
#elif defined _WIN32//Windows
#endif


Colour::Colour()
{
	mMode = kColourModeRGB;
	col.rgb.red = 0;
	col.rgb.green = 0;
	col.rgb.blue = 0;
	mAlpha = 255;
}

Colour::Colour(const Colour &other)
{
	mMode = other.mMode;
	col.cmyk.cyan = other.col.cmyk.cyan;
	col.cmyk.magenta = other.col.cmyk.magenta;
	col.cmyk.yellow = other.col.cmyk.yellow;
	col.cmyk.key = other.col.cmyk.key;
	mAlpha = other.mAlpha;
}

namespace jm
{
	Colour& Colour::operator=(const Colour &other)
	{
		if(this != &other)
		{
			mMode = other.mMode;
			col.cmyk.cyan = other.col.cmyk.cyan;
			col.cmyk.magenta = other.col.cmyk.magenta;
			col.cmyk.yellow = other.col.cmyk.yellow;
			col.cmyk.key = other.col.cmyk.key;
			mAlpha = other.mAlpha;
		}

		return *this;
	}

}

void Colour::ToRGB()
{
	switch(mMode)
	{
		case kColourModeRGB:
			//Keine Umwandlung notwendig.
			break;

		case kColourModeGrey:
		{
			uint8 grey = col.g.grey;
			mMode = kColourModeRGB;
			col.rgb.red = grey;
			col.rgb.green = grey;
			col.rgb.blue = grey;
			break;
		}

		case kColourModeCMYK:
		{
			//Beschreibung nach PDF 1.6-Reference 6.2.4 (S.454)
			mMode = kColourModeRGB;
			uint16 c = col.cmyk.cyan;
			uint16 m = col.cmyk.magenta;
			uint16 y = col.cmyk.yellow;
			uint16 k = col.cmyk.key;
			col.rgb.red = static_cast<uint8>(255 - std::min(255, c + k));
			col.rgb.green = static_cast<uint8>(255 - std::min(255, m + k));
			col.rgb.blue = static_cast<uint8>(255 - std::min(255, y + k));
			break;
		}
	}
}

void Colour::ToGreyScale()
{
	switch(mMode)
	{
		case kColourModeRGB:
		{
			mMode = kColourModeGrey;
			// G = 0.2126 R + 0.7152 G + 0.0722 B.
			float grey = 0.2126f * col.rgb.red +
			             0.7152f * col.rgb.green +
			             0.0733f * col.rgb.blue;
			col.g.grey = std::min(static_cast<int8>(255), static_cast<int8>(grey));
			mAlpha = 255;
			break;
		}

		case kColourModeGrey:
			//Keine Umwandlung notwendig.
			break;

		case kColourModeCMYK:
		{
			//Der "Umweg" über RGB ist nach momentanen Stand der einfachste.
			ToRGB();
			ToGreyScale();
			break;
		}
	}
}

void Colour::ToCMYK()
{
	switch(mMode)
	{
		case kColourModeRGB:
		{
			//The R,G,B values are divided by 255 to change the range from 0..255 to 0..1:
			//R' = R/255
			//G' = G/255
			//B' = B/255
			float r = col.rgb.red / 255.0f;
			float g = col.rgb.green / 255.0f;
			float b = col.rgb.blue / 255.0f;
			//The black key (K) colour is calculated from the red (R'), green (G') and blue (B') colours:
			//K = 1-max(R', G', B')
			float k = 1.0f - std::max(r, std::max(g, b));
			//The cyan colour (C) is calculated from the red (R') and black (K) colours:
			//C = (1-R'-K) / (1-K)
			float c = (1 - r - k) / (1 - k);
			//The magenta colour (M) is calculated from the green (G') and black (K) colours:
			//M = (1-G'-K) / (1-K)
			float m = (1 - g - k) / (1 - k);
			//The yellow colour (Y) is calculated from the blue (B') and black (K) colours:
			//Y = (1-B'-K) / (1-K)
			float y = (1 - b - k) / (1 - k);
			mMode = kColourModeCMYK;
			col.cmyk.cyan = static_cast<uint8>(255.0f * c);
			col.cmyk.magenta = static_cast<uint8>(255.0f * m);
			col.cmyk.yellow = static_cast<uint8>(255.0f * y);
			col.cmyk.key = static_cast<uint8>(255.0f * k);
			mAlpha = 255;
			break;
		}

		case kColourModeGrey:
		{
			uint8 grey = col.g.grey;
			mMode = kColourModeCMYK;
			col.cmyk.cyan = 0;
			col.cmyk.magenta = 0;
			col.cmyk.yellow = 0;
			col.cmyk.key = 255 - grey;
			mAlpha = 255;
			break;
		}

		case kColourModeCMYK:
			//Keine Umwandlung notwendig.
			break;
	}
}

uint8 Colour::Alpha() const
{
	return mAlpha;
}

uint8 Colour::Red() const
{
	return col.rgb.red;
}

uint8 Colour::Green() const
{
	return col.rgb.green;
}

uint8 Colour::Blue() const
{
	return col.rgb.blue;
}

uint8 Colour::Grey() const
{
	return col.g.grey;
}

uint8 Colour::Cyan() const
{
	return col.cmyk.cyan;
}

uint8 Colour::Magenta() const
{
	return col.cmyk.magenta;
}

uint8 Colour::Yellow() const
{
	return col.cmyk.yellow;
}

uint8 Colour::Key() const
{
	return col.cmyk.key;
}

ColourMode Colour::Mode() const
{
	return mMode;
}


bool Colour::IsWhite() const
{
	switch(mMode)
	{
		case kColourModeRGB:
			return col.rgb.red == 255 && col.rgb.green == 255 && col.rgb.blue == 255;

		case kColourModeGrey:
			return col.g.grey == 255;

		case kColourModeCMYK:
			return col.cmyk.cyan == 0 && col.cmyk.magenta == 0 && col.cmyk.yellow == 0 && col.cmyk.key == 0;
	}

	return false;
}

void Colour::GetHSVModel(float &hue, float &saturation, float &value) const
{
	Colour tmp = *this;
	tmp.ToRGB();

	uint8 MAX = std::max(std::max(tmp.Red(), tmp.Green()), tmp.Blue());
	uint8 MIN = std::min(std::min(tmp.Red(), tmp.Green()), tmp.Blue());

	float MAX_MIN = static_cast<float>(MAX - MIN);

	//
	// HUE
	//
	if(MAX == MIN)hue = 0.0;
	else if(MAX == tmp.Red())hue = 60.0f * static_cast<float>(tmp.Green() - tmp.Blue()) / MAX_MIN;
	else if(MAX == tmp.Green())hue = 60.0f * (2.0f + static_cast<float>(tmp.Blue() - tmp.Red()) / MAX_MIN);
	else if(MAX == tmp.Blue())hue = 60.0f * (4.0f + static_cast<float>(tmp.Red() - tmp.Green()) / MAX_MIN);

	if(hue < 0.0)hue += 360.0f;

	//
	// SATURATION
	//
	if(MAX == MIN)saturation = 0.0f;
	else saturation = MAX_MIN / MAX;

	//
	// VALUE
	//
	value = static_cast<float>(MAX) / 255.0f;

}

void Colour::SetMode(ColourMode mode)
{
	mMode = mode;
}

void Colour::SetAlpha(uint8 alpha)
{
	mAlpha = alpha;
}

void Colour::SetRed(uint8 red)
{
	col.rgb.red = red;
}

void Colour::SetGreen(uint8 green)
{
	col.rgb.green = green;
}

void Colour::SetBlue(uint8 blue)
{
	col.rgb.blue = blue;
}

void Colour::SetGrey(uint8 grey)
{
	col.g.grey = grey;
}

void Colour::SetCyan(uint8 cyan)
{
	col.cmyk.cyan = cyan;
}

void Colour::SetMagenta(uint8 magenta)
{
	col.cmyk.magenta = magenta;
}

void Colour::SetYellow(uint8 yellow)
{
	col.cmyk.yellow = yellow;
}

void Colour::SetKey(uint8 key)
{
	col.cmyk.key = key;
}

Colour Colour::FromGrey(uint8 grey, uint8 alpha)
{
	Colour c;

	c.mMode = kColourModeGrey;
	c.col.g.grey = grey;
	c.mAlpha = alpha;

	return c;
}

Colour Colour::FromRGB(uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
	Colour c;

	c.mMode = kColourModeRGB;
	c.col.rgb.red = red;
	c.col.rgb.green = green;
	c.col.rgb.blue = blue;
	c.mAlpha = alpha;

	return c;
}

Colour Colour::FromCMYK(uint8 cyan, uint8 magenta, uint8 yellow, uint8 key, uint8 alpha)
{
	Colour c;

	c.mMode = kColourModeCMYK;
	c.col.cmyk.cyan = cyan;
	c.col.cmyk.magenta = magenta;
	c.col.cmyk.yellow = yellow;
	c.col.cmyk.key = key;
	c.mAlpha = alpha;

	return c;
}

Colour Colour::FromHSV(float hue, float saturation, float value, float alpha)
{
	Colour c;

	//Siehe: https://de.wikipedia.org/wiki/HSV-Farbraum

	int hi = static_cast<int>(floor(hue / 60.0f));
	float f = (hue / 60.0f) - hi;
	float p = value * (1.0f - saturation);
	float q = value * (1.0f - saturation * f);
	float t = value * (1.0f - saturation * (1.0f - f));

	switch(hi)
	{
		case 0:
		case 6:
			c = FromRGB(static_cast<uint8>(value * 255), static_cast<uint8>(t * 255), static_cast<uint8>(p * 255));
			break;

		case 1:
			c = FromRGB(static_cast<uint8>(q * 255), static_cast<uint8>(value * 255), static_cast<uint8>(p * 255));
			break;

		case 2:
			c = FromRGB(static_cast<uint8>(p * 255), static_cast<uint8>(value * 255), static_cast<uint8>(t * 255));
			break;

		case 3:
			c = FromRGB(static_cast<uint8>(p * 255), static_cast<uint8>(q * 255), static_cast<uint8>(value * 255));
			break;

		case 4:
			c = FromRGB(static_cast<uint8>(t * 255), static_cast<uint8>(p * 255), static_cast<uint8>(value * 255));
			break;

		case 5:
			c = FromRGB(static_cast<uint8>(value * 255), static_cast<uint8>(p * 255), static_cast<uint8>(q * 255));
			break;
	}

	c.SetAlpha(static_cast<uint8>(alpha * 255));

	return c;
}

//Alpha-Blending nach  Porter Duff Algorithmus
uint8 PorterDuffAlpha(uint8 alphaBackground, uint8 alphaForeground);
uint8 PorterDuffAlpha(uint8 alphaBackground, uint8 alphaForeground)
{
	int32 alphaA = alphaForeground;
	int32 alphaB = alphaBackground;

	int32 alphaC = alphaA + ((255 - alphaA) * alphaB) / 255;

	return (uint8) alphaC;
}

uint8 PorterDuffColour(uint8 colourBackground, uint8 alphaBackground, uint8 colourForeground, uint8 alphaForeground);
uint8 PorterDuffColour(uint8 colourBackground, uint8 alphaBackground, uint8 colourForeground, uint8 alphaForeground)
{
	float alphaA = alphaForeground / 255.0f;
	float alphaB = alphaBackground / 255.0f;
	float A = colourForeground / 255.0f;
	float B = colourBackground / 255.0f;
	float alphaC = PorterDuffAlpha(alphaBackground, alphaForeground) / 255.0f;

	float C = (alphaA * A + (1 - alphaA) * alphaB * B) / alphaC;

	return (uint8)(C * 255);
}

Colour jm::Blend(Colour background, Colour foreground, uint8 alpha)
{
	//Einfaches Alpha-Blendung für Nicht-Transparente Farben
	if(background.mAlpha == 255 && foreground.mAlpha == 255)
	{
		Colour ret;
		ret.col.rgb.red = (alpha * foreground.col.rgb.red + (255 - alpha) * background.col.rgb.red) / 255;
		ret.col.rgb.green = (alpha * foreground.col.rgb.green + (255 - alpha) * background.col.rgb.green) / 255;
		ret.col.rgb.blue = (alpha * foreground.col.rgb.blue + (255 - alpha) * background.col.rgb.blue) / 255;
		return ret;
	}

	//Blending nach Porter Duff Algorithmus
	Colour ret;
	ret.col.rgb.red = PorterDuffColour(background.col.rgb.red, background.mAlpha, foreground.col.rgb.red, foreground.mAlpha);
	ret.col.rgb.green = PorterDuffColour(background.col.rgb.green, background.mAlpha, foreground.col.rgb.green, foreground.mAlpha);
	ret.col.rgb.blue = PorterDuffColour(background.col.rgb.blue, background.mAlpha, foreground.col.rgb.blue, foreground.mAlpha);
	ret.mAlpha = PorterDuffAlpha(background.mAlpha, foreground.mAlpha);
	return ret;
}

Colour jm::Interpolate(Colour colour1, Colour colour2, float percent)
{
	Colour ret;
	ret.col.rgb.red = static_cast<uint8>(colour1.col.rgb.red + (colour2.col.rgb.red - colour1.col.rgb.red) * percent);
	ret.col.rgb.green = static_cast<uint8>(colour1.col.rgb.green + (colour2.col.rgb.green - colour1.col.rgb.green) * percent);
	ret.col.rgb.blue = static_cast<uint8>(colour1.col.rgb.blue + (colour2.col.rgb.blue - colour1.col.rgb.blue) * percent);
	ret.mAlpha = static_cast<uint8>(colour1.mAlpha + (colour2.mAlpha - colour1.mAlpha) * percent);
	return ret;
}


bool jm::operator==(Colour const &c1, Colour const &c2)
{
	if(c1.mMode != c2.mMode) return false;

	switch(c1.mMode)
	{
		case kColourModeGrey:
			if(c1.col.g.grey != c2.col.g.grey)return false;
			break;

		case kColourModeRGB:
			if(c1.col.rgb.red != c2.col.rgb.red)return false;
			if(c1.col.rgb.green != c2.col.rgb.green)return false;
			if(c1.col.rgb.blue != c2.col.rgb.blue)return false;
			break;

		case kColourModeCMYK:
			if(c1.col.cmyk.cyan != c2.col.cmyk.cyan)return false;
			if(c1.col.cmyk.magenta != c2.col.cmyk.magenta)return false;
			if(c1.col.cmyk.yellow != c2.col.cmyk.yellow)return false;
			if(c1.col.cmyk.key != c2.col.cmyk.key)return false;
			break;
	}

	if(c1.mAlpha != c2.mAlpha)return false;

	return true;
}

bool jm::operator!=(Colour const &c1, Colour const &c2)
{
	return !(c1 == c2);
}

const Colour jm::operator-(Colour const &c1, Colour const &c2)
{
	Colour ret = c1;
	switch(c1.mMode)
	{
		case kColourModeGrey:
			ret.col.g.grey -= c2.col.g.grey;
			break;

		case kColourModeRGB:
			ret.col.rgb.red -= c2.col.rgb.red;
			ret.col.rgb.green -= c2.col.rgb.green;
			ret.col.rgb.blue -= c2.col.rgb.blue;
			break;

		case kColourModeCMYK:
			ret.col.cmyk.cyan -= c2.col.cmyk.cyan;
			ret.col.cmyk.magenta -= c2.col.cmyk.magenta;
			ret.col.cmyk.yellow -= c2.col.cmyk.yellow;
			ret.col.cmyk.key -= c2.col.cmyk.key;
			break;
	}

	ret.mAlpha -= c2.mAlpha;
	return ret;
}

const Colour jm::operator+(Colour const &c1, Colour const &c2)
{
	Colour ret = c1;
	switch(c1.mMode)
	{
		case kColourModeGrey:
			ret.col.g.grey += c2.col.g.grey;
			break;

		case kColourModeRGB:
			ret.col.rgb.red += c2.col.rgb.red;
			ret.col.rgb.green += c2.col.rgb.green;
			ret.col.rgb.blue += c2.col.rgb.blue;
			break;

		case kColourModeCMYK:
			ret.col.cmyk.cyan += c2.col.cmyk.cyan;
			ret.col.cmyk.magenta += c2.col.cmyk.magenta;
			ret.col.cmyk.yellow += c2.col.cmyk.yellow;
			ret.col.cmyk.key += c2.col.cmyk.key;
			break;
	}

	ret.mAlpha += c2.mAlpha;

	return ret;
}

