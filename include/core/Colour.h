////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Colour.h
// Library:     Jameo Core Library
// Purpose:     Colour models
//
// Author:      Uwe Runtemund (2017-today)
// Modified by:
// Created:     21.07.2017
//
// Copyright:   (c) 2017 Jameo Software, Germany. https://jameo.de
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

#ifndef jm_Colour_h
#define jm_Colour_h

namespace jm
{
   struct Colour;

   /*!
    \brief Enumeration of available colour modes for \c Colour
    \note Compile with -fshort-enums
    \ingroup core
    */
   enum ColourMode
   {
      kColourModeGrey = 0, /*!< Grey Scale */
      kColourModeRGB = 1, /*!< RGB Color Space */
      kColourModeCMYK = 2 /*!< CMYK Color Space */
   };

   /*!
    \brief A class as a colour representation is so fundamental for us that it is used as a basic
    data type. The storage is as universal as possible. The special thing about this data type is
    that it stores the values "differently" depending on the mode. The data type is extremely
    space-saving. It only requires 6 bytes
    \ingroup core
    */
   struct DllExport Colour
   {
         /*!
          \brief Constructor
          */
         Colour();

         /*!
          \brief Copy construktur
          \param other The colour we became a copy of.
          */
         Colour(const Colour &other);

         Colour &operator=(const Colour &other);

         /*!
          \brief Converts the colour to the RGB colour space.
          */
         void ToRGB();

         /*!
          \brief Converts the colour to the CMYK colour space.
          */
         void ToCMYK();

         /*!
          \brief  Converts the colour to the greyscale colour space.

          The following algorithm is used:
          G = 0.2126 R + 0.7152 G + 0.0722 B.
          */
         void ToGreyScale();

         /*!
          \brief Returns alpha component directly. 0 = transparent, 255 = opaque.

          Value is colour space independent.
          */
         uint8 Alpha() const;

         /*!
          \brief Returns red component directly.
          \note Value only has a meaning in RGB mode
          */
         uint8 Red() const;

         /*!
          \brief Returns green component directly.
          \note Value only has a meaning in RGB mode
          */
         uint8 Green() const;

         /*!
          \brief Returns blue component directly.
          \note Value only has a meaning in RGB mode
          */
         uint8 Blue() const;

         /*!
          \brief Returns grey component directly.
          \note Value only has meaning in greyscale mode.
          */
         uint8 Grey() const;

         /*!
          \brief Returns cyan component directly.
           \note Value only has meaning in CMYK mode
          */
         uint8 Cyan() const;

         /*!
          \brief Returns magenta component directly.
           \note Value only has meaning in CMYK mode
          */
         uint8 Magenta() const;

         /*!
          \brief Returns yellow component directly.
           \note Value only has meaning in CMYK mode
          */
         uint8 Yellow() const;

         /*!
          \brief Returns key (black) component directly.
           \note Value only has meaning in CMYK mode
          */
         uint8 Key() const;

         /*!
          \brief Returns the colour mode.
          */
         ColourMode Mode() const;

         /*!
          \brief Is the colour white?
          */
         bool IsWhite() const;

         /*!
          \brief Returns the HSV values of this colour. If the colour is not created in the RGB colour
          space, this method first temporarily converts the colour to the RFB colour space.
          \param hue Output filled in with the hue value.
          \param saturation Output filled in with the saturation value.
          \param value Output filled in with the brightness value.
          */
         void GetHSVModel(float &hue, float &saturation, float &value) const;

         /*!
          \brief Sets the colour space directly.
          \note There is no conversion of values.
          */
         void SetMode(ColourMode mode);

         /*!
          \brief Directly sets the transparency. 0 = transparent, 255 = opaque.
          */
         void SetAlpha(uint8 alpha);

         /*!
          \brief Sets the red component directly.
          \note Value only has a meaning in RGB mode. In other colour spaces, the colour is changed
          incorrectly.
          */
         void SetRed(uint8 red);

         /*!
          \brief Sets the green component directly.
          \note Value only has a meaning in RGB mode. In other colour spaces, the colour is changed
          incorrectly.
          */
         void SetGreen(uint8 green);

         /*!
          \brief Sets the blue component directly.
          \note Value only has a meaning in RGB mode. In other colour spaces, the colour is changed
          incorrectly.
          */
         void SetBlue(uint8 blue);

         /*!
          \brief Sets the grey component directly.
          \note Value only has a meaning in grey scale mode. In other colour spaces, the colour is
          changed incorrectly.
          */
         void SetGrey(uint8 grey);

         /*!
          \brief Sets the cyan component directly.
          \note Value only has a meaning in CMYK mode. In other colour spaces, the colour is changed
          incorrectly.
          */
         void SetCyan(uint8 cyan);

         /*!
          \brief Sets the magenta component directly.
          \note Value only has a meaning in CMYK mode. In other colour spaces, the colour is changed
          incorrectly.
          */
         void SetMagenta(uint8 magenta);

         /*!
          \brief Sets the yellow component directly.
          \note Value only has a meaning in CMYK mode. In other colour spaces, the colour is changed
          incorrectly.
          */
         void SetYellow(uint8 yellow);

         /*!
          \brief Sets the key (black) component directly.
          \note Value only has a meaning in CMYK mode. In other colour spaces, the colour is changed
          incorrectly.
          */
         void SetKey(uint8 key);

         /*!
          \brief This method creates a colour in the colour space "greyscale".
          0 means black, 255 means white
          */
         static Colour FromGrey(uint8 grey, uint8 alpha = 255);

         /*!
          \brief This method creates a colour in the colour space "RGB".
          0 means black/dark/no colour, 255 means white/light/full colour
          */
         static Colour FromRGB(uint8 red, uint8 green, uint8 blue, uint8 alpha = 255);

         /*!
          \brief This method creates a colour in the colour space "CMYK".
          0 means no colour (white on paper), 255 means full colour (dark on paper)
          */
         static Colour FromCMYK(uint8 cyan, uint8 magenta, uint8 yellow, uint8 key, uint8 alpha = 255);

         /*!
          \brief This method creates a colour in the colour space "RGB" using the HSV model.
          All specifications in the space from 0.0-1.0
          */
         static Colour FromHSV(float hue, float saturation, float value, float alpha = 1.0);

      private:

         //Color space of this color
         ColourMode mMode;


         union
         {
            //Mode = grey;
            struct
            {
               uint8 grey;
            } g;

            //Mode = rgb
            struct
            {
               uint8 red;
               uint8 green;
               uint8 blue;
            } rgb;

            //Mode = cmyk;
            struct
            {
               uint8 cyan;
               uint8 magenta;
               uint8 yellow;
               uint8 key;
            } cmyk;

         } col;

         uint8 mAlpha;

         DllExport friend bool operator==(Colour const &c1, Colour const &c2);
         DllExport friend bool operator!=(Colour const& c1, Colour const& c2);
         DllExport friend const Colour operator-(Colour const &c1, Colour const &c2);
         DllExport friend const Colour operator+(Colour const &c1, Colour const &c2);
         DllExport friend Colour Blend(Colour background, Colour foreground, uint8 alpha);
         DllExport friend Colour Interpolate(Colour colour1, Colour colour2, float percent);
   };

   // Under windows we do not need that, under macOS it is required
   #if defined __APPLE__ || defined __linux__
   DllExport
   Colour Blend(Colour background, Colour foreground, uint8 alpha);

   DllExport
   Colour Interpolate(Colour colour1, Colour colour2, float percent);

   DllExport
   bool operator==(Colour const& c1, Colour const& c2);

   DllExport
   bool operator!=(Colour const& c1, Colour const& c2);

   DllExport
   const Colour operator-(Colour const& c1, Colour const& c2);

   DllExport
   const Colour operator+(Colour const& c1, Colour const& c2);
   #endif

}

#endif
