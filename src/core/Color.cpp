////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Character.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of Color
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

#include "PrecompiledCore.hpp"

using namespace jm;

Color::Color()
{
   mMode = ColorMode::kRgb;
   col.rgb.red = 0;
   col.rgb.green = 0;
   col.rgb.blue = 0;
   mAlpha = 255;
}

Color::Color(const Color& other)
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
   Color& Color::operator=(const Color& other)
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

const Color& Color::toRgb()
{
   switch(mMode)
   {
      case ColorMode::kRgb:
         // No conversion necessary.
         break;

      case ColorMode::kGrey:
      {
         uint8 grey = col.g.grey;
         mMode = ColorMode::kRgb;
         col.rgb.red = grey;
         col.rgb.green = grey;
         col.rgb.blue = grey;
         break;
      }

      case ColorMode::kCmyk:
      {
         // Description acc. to PDF 1.6-Reference 6.2.4 (S.454)
         mMode = ColorMode::kRgb;
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

   return *this;
}

void Color::toGreyScale()
{
   switch(mMode)
   {
      case ColorMode::kRgb:
      {
         mMode = ColorMode::kGrey;
         // G = 0.2126 R + 0.7152 G + 0.0722 B.
         float grey = 0.2126f * col.rgb.red +
                      0.7152f * col.rgb.green +
                      0.0733f * col.rgb.blue;
         col.g.grey = std::min(static_cast<uint8>(255), static_cast<uint8>(grey));
         mAlpha = 255;
         break;
      }

      case ColorMode::kGrey:
         // No conversion necessary.
         break;

      case ColorMode::kCmyk:
      {
         // The "detour" via RGB is currently the simplest.
         toRgb();
         toGreyScale();
         break;
      }
   }
}

void Color::toCmyk()
{
   switch(mMode)
   {
      case ColorMode::kRgb:
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
         float k = 1.0f - std::max({r, g, b});
         //The cyan colour (C) is calculated from the red (R') and black (K) colours:
         //C = (1-R'-K) / (1-K)
         float c = (1 - r - k) / (1 - k);
         //The magenta colour (M) is calculated from the green (G') and black (K) colours:
         //M = (1-G'-K) / (1-K)
         float m = (1 - g - k) / (1 - k);
         //The yellow colour (Y) is calculated from the blue (B') and black (K) colours:
         //Y = (1-B'-K) / (1-K)
         float y = (1 - b - k) / (1 - k);
         mMode = ColorMode::kCmyk;
         col.cmyk.cyan = static_cast<uint8>(255.0f * c);
         col.cmyk.magenta = static_cast<uint8>(255.0f * m);
         col.cmyk.yellow = static_cast<uint8>(255.0f * y);
         col.cmyk.key = static_cast<uint8>(255.0f * k);
         mAlpha = 255;
         break;
      }

      case ColorMode::kGrey:
      {
         uint8 grey = col.g.grey;
         mMode = ColorMode::kCmyk;
         col.cmyk.cyan = 0;
         col.cmyk.magenta = 0;
         col.cmyk.yellow = 0;
         col.cmyk.key = 255 - grey;
         mAlpha = 255;
         break;
      }

      case ColorMode::kCmyk:
         //Keine Umwandlung notwendig.
         break;
   }
}

uint8 Color::alpha() const
{
   return mAlpha;
}

uint8 Color::red() const
{
   return col.rgb.red;
}

uint8 Color::green() const
{
   return col.rgb.green;
}

uint8 Color::blue() const
{
   return col.rgb.blue;
}

uint8 Color::grey() const
{
   return col.g.grey;
}

uint8 Color::cyan() const
{
   return col.cmyk.cyan;
}

uint8 Color::magenta() const
{
   return col.cmyk.magenta;
}

uint8 Color::yellow() const
{
   return col.cmyk.yellow;
}

uint8 Color::key() const
{
   return col.cmyk.key;
}

ColorMode Color::mode() const
{
   return mMode;
}


bool Color::isWhite() const
{
   switch(mMode)
   {
      case ColorMode::kRgb:
         return col.rgb.red == 255 && col.rgb.green == 255 && col.rgb.blue == 255;

      case ColorMode::kGrey:
         return col.g.grey == 255;

      case ColorMode::kCmyk:
         return col.cmyk.cyan == 0 && col.cmyk.magenta == 0 && col.cmyk.yellow == 0 && col.cmyk.key == 0;
   }

   return false;
}

void Color::hsvModel(float& hue, float& saturation, float& value) const
{
   Color tmp = *this;
   tmp.toRgb();

   uint8 MAX = std::max({tmp.red(), tmp.green(), tmp.blue()});
   uint8 MIN = std::min({tmp.red(), tmp.green(), tmp.blue()});

   float MAX_MIN = static_cast<float>(MAX - MIN);

   //
   // HUE
   //
   if(MAX == MIN)hue = 0.0;
   else if(MAX == tmp.red())hue = 60.0f * static_cast<float>(tmp.green() - tmp.blue()) / MAX_MIN;
   else if(MAX == tmp.green())hue = 60.0f * (2.0f + static_cast<float>(tmp.blue() - tmp.red()) /
                                       MAX_MIN);
   else if(MAX == tmp.blue())hue = 60.0f * (4.0f + static_cast<float>(tmp.red() - tmp.green()) /
                                      MAX_MIN);

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

void Color::setMode(ColorMode mode)
{
   mMode = mode;
}

void Color::setAlpha(uint8 alpha)
{
   mAlpha = alpha;
}

void Color::setRed(uint8 red)
{
   col.rgb.red = red;
}

void Color::setGreen(uint8 green)
{
   col.rgb.green = green;
}

void Color::setBlue(uint8 blue)
{
   col.rgb.blue = blue;
}

void Color::setGrey(uint8 grey)
{
   col.g.grey = grey;
}

void Color::setCyan(uint8 cyan)
{
   col.cmyk.cyan = cyan;
}

void Color::setMagenta(uint8 magenta)
{
   col.cmyk.magenta = magenta;
}

void Color::setYellow(uint8 yellow)
{
   col.cmyk.yellow = yellow;
}

void Color::setKey(uint8 key)
{
   col.cmyk.key = key;
}

Color Color::fromGrey(uint8 grey, uint8 alpha)
{
   Color c;

   c.mMode = ColorMode::kGrey;
   c.col.g.grey = grey;
   c.mAlpha = alpha;

   return c;
}

Color Color::fromRgb(uint8 red, uint8 green, uint8 blue, uint8 alpha)
{
   Color c;

   c.mMode = ColorMode::kRgb;
   c.col.rgb.red = red;
   c.col.rgb.green = green;
   c.col.rgb.blue = blue;
   c.mAlpha = alpha;

   return c;
}

Color Color::fromCmyk(uint8 cyan, uint8 magenta, uint8 yellow, uint8 key, uint8 alpha)
{
   Color c;

   c.mMode = ColorMode::kCmyk;
   c.col.cmyk.cyan = cyan;
   c.col.cmyk.magenta = magenta;
   c.col.cmyk.yellow = yellow;
   c.col.cmyk.key = key;
   c.mAlpha = alpha;

   return c;
}

Color Color::FromHsv(float hue, float saturation, float value, float alpha)
{
   Color c;

   //Siehe: https://de.wikipedia.org/wiki/HSV-Farbraum

   float fhi = std::floor(hue / 60.0f);
   int hi = static_cast<int>(fhi);
   float f = (hue / 60.0f) - fhi;
   float p = value * (1.0f - saturation);
   float q = value * (1.0f - saturation * f);
   float t = value * (1.0f - saturation * (1.0f - f));

   switch(hi)
   {
      case 0:
      case 6:
         c = fromRgb(static_cast<uint8>(value * 255), static_cast<uint8>(t * 255),
                     static_cast<uint8>(p * 255));
         break;

      case 1:
         c = fromRgb(static_cast<uint8>(q * 255), static_cast<uint8>(value * 255),
                     static_cast<uint8>(p * 255));
         break;

      case 2:
         c = fromRgb(static_cast<uint8>(p * 255), static_cast<uint8>(value * 255),
                     static_cast<uint8>(t * 255));
         break;

      case 3:
         c = fromRgb(static_cast<uint8>(p * 255), static_cast<uint8>(q * 255),
                     static_cast<uint8>(value * 255));
         break;

      case 4:
         c = fromRgb(static_cast<uint8>(t * 255), static_cast<uint8>(p * 255),
                     static_cast<uint8>(value * 255));
         break;

      case 5:
         c = fromRgb(static_cast<uint8>(value * 255), static_cast<uint8>(p * 255),
                     static_cast<uint8>(q * 255));
         break;
   }

   c.setAlpha(static_cast<uint8>(alpha * 255));

   return c;
}

//Alpha-Blending acc. to Porter Duff Algorithm
uint8 PorterDuffAlpha(uint8 alphaBackground, uint8 alphaForeground);
uint8 PorterDuffAlpha(uint8 alphaBackground, uint8 alphaForeground)
{
   int32 alphaA = alphaForeground;
   int32 alphaB = alphaBackground;

   int32 alphaC = alphaA + ((255 - alphaA) * alphaB) / 255;

   return static_cast<uint8>(alphaC);
}

uint8 PorterDuffColour(uint8 colourBackground, uint8 alphaBackground, uint8 colourForeground,
                       uint8 alphaForeground);
uint8 PorterDuffColour(uint8 colourBackground, uint8 alphaBackground, uint8 colourForeground,
                       uint8 alphaForeground)
{
   float alphaA = alphaForeground / 255.0f;
   float alphaB = alphaBackground / 255.0f;
   float A = colourForeground / 255.0f;
   float B = colourBackground / 255.0f;
   float alphaC = PorterDuffAlpha(alphaBackground, alphaForeground) / 255.0f;

   float C = (alphaA * A + (1 - alphaA) * alphaB * B) / alphaC;

   return static_cast<uint8>(C * 255);
}

Color jm::blend(Color background, Color foreground, uint8 alpha)
{
   //Simple Alpha-Blendung for non transparent color
   if(background.mAlpha == 255 && foreground.mAlpha == 255)
   {
      Color ret;
      ret.col.rgb.red = (alpha * foreground.col.rgb.red + (255 - alpha) * background.col.rgb.red) / 255;
      ret.col.rgb.green = (alpha * foreground.col.rgb.green + (255 - alpha) * background.col.rgb.green) /
                          255;
      ret.col.rgb.blue = (alpha * foreground.col.rgb.blue + (255 - alpha) * background.col.rgb.blue) /
                         255;
      return ret;
   }

   //Blending acc. to Porter Duff Algorithm
   Color ret;
   ret.col.rgb.red = PorterDuffColour(background.col.rgb.red, background.mAlpha,
                                      foreground.col.rgb.red, foreground.mAlpha);
   ret.col.rgb.green = PorterDuffColour(background.col.rgb.green, background.mAlpha,
                                        foreground.col.rgb.green, foreground.mAlpha);
   ret.col.rgb.blue = PorterDuffColour(background.col.rgb.blue, background.mAlpha,
                                       foreground.col.rgb.blue, foreground.mAlpha);
   ret.mAlpha = PorterDuffAlpha(background.mAlpha, foreground.mAlpha);
   return ret;
}

Color jm::interpolate(Color colour1, Color colour2, float percent)
{
   Color ret;
   ret.col.rgb.red = static_cast<uint8>(colour1.col.rgb.red + (colour2.col.rgb.red -
                                        colour1.col.rgb.red) * percent);
   ret.col.rgb.green = static_cast<uint8>(colour1.col.rgb.green + (colour2.col.rgb.green -
                                          colour1.col.rgb.green) * percent);
   ret.col.rgb.blue = static_cast<uint8>(colour1.col.rgb.blue + (colour2.col.rgb.blue -
                                         colour1.col.rgb.blue) * percent);
   ret.mAlpha = static_cast<uint8>(colour1.mAlpha + (colour2.mAlpha - colour1.mAlpha) * percent);
   return ret;
}


bool jm::operator==(Color const& c1, Color const& c2)
{
   if(c1.mMode != c2.mMode) return false;

   switch(c1.mMode)
   {
      case ColorMode::kGrey:
         if(c1.col.g.grey != c2.col.g.grey)return false;
         break;

      case ColorMode::kRgb:
         if(c1.col.rgb.red != c2.col.rgb.red)return false;
         if(c1.col.rgb.green != c2.col.rgb.green)return false;
         if(c1.col.rgb.blue != c2.col.rgb.blue)return false;
         break;

      case ColorMode::kCmyk:
         if(c1.col.cmyk.cyan != c2.col.cmyk.cyan)return false;
         if(c1.col.cmyk.magenta != c2.col.cmyk.magenta)return false;
         if(c1.col.cmyk.yellow != c2.col.cmyk.yellow)return false;
         if(c1.col.cmyk.key != c2.col.cmyk.key)return false;
         break;
   }

   if(c1.mAlpha != c2.mAlpha)return false;

   return true;
}

bool jm::operator!=(Color const& c1, Color const& c2)
{
   return !(c1 == c2);
}

Color jm::operator-(Color const& c1, Color const& c2)
{
   Color ret = c1;
   switch(c1.mMode)
   {
      case ColorMode::kGrey:
         ret.col.g.grey -= c2.col.g.grey;
         break;

      case ColorMode::kRgb:
         ret.col.rgb.red -= c2.col.rgb.red;
         ret.col.rgb.green -= c2.col.rgb.green;
         ret.col.rgb.blue -= c2.col.rgb.blue;
         break;

      case ColorMode::kCmyk:
         ret.col.cmyk.cyan -= c2.col.cmyk.cyan;
         ret.col.cmyk.magenta -= c2.col.cmyk.magenta;
         ret.col.cmyk.yellow -= c2.col.cmyk.yellow;
         ret.col.cmyk.key -= c2.col.cmyk.key;
         break;
   }

   ret.mAlpha -= c2.mAlpha;
   return ret;
}

Color jm::operator+(Color const& c1, Color const& c2)
{
   Color ret = c1;
   switch(c1.mMode)
   {
      case ColorMode::kGrey:
         ret.col.g.grey += c2.col.g.grey;
         break;

      case ColorMode::kRgb:
         ret.col.rgb.red += c2.col.rgb.red;
         ret.col.rgb.green += c2.col.rgb.green;
         ret.col.rgb.blue += c2.col.rgb.blue;
         break;

      case ColorMode::kCmyk:
         ret.col.cmyk.cyan += c2.col.cmyk.cyan;
         ret.col.cmyk.magenta += c2.col.cmyk.magenta;
         ret.col.cmyk.yellow += c2.col.cmyk.yellow;
         ret.col.cmyk.key += c2.col.cmyk.key;
         break;
   }

   ret.mAlpha += c2.mAlpha;

   return ret;
}

