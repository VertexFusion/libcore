////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        PaintingBackend.h
// Library:     Jameo Core Library
// Purpose:     Drawing Interface for draw CAD drawings to different targets (Backends)
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

#ifndef jm_Painter_h
#define jm_Painter_h

#include "Object.h"
#include "Color.h"

#include "Transform.h"
#include "Nurbs.h"

namespace jm
{

   /*!
    \brief Internal enumeration to provide a more detailed description of BufferElement
    */
   enum class BufferMode
   {
      kBmMoveTo,   // Move the pen to a new position
      kBmLineTo,   // Draw a line to a new position
      kBmBlindTo   // Move the pen to a new position without drawing
   };

   /*!
    \brief This struct stores the drawing information.
    */
   struct DllExport BufferElement
   {
      Vertex3 point; // The point to be drawn
      BufferMode mode; // The mode of drawing (move-to, line-to, blind-to)

      /*!
       \brief Constructor
       \param point The point to be drawn
       \param mode The mode of drawing
       */
      BufferElement(Vertex3 point, BufferMode mode)
      {
         this->point = point;
         this->mode = mode;
      }
   };

   /*!
    \brief This class provides the parent class for the graphic output. This class draws.
    */
   class DllExport PaintingBackend: public Object
   {
      public:

         /*!
          \brief Constructor
          */
         PaintingBackend();

         /*!
          \brief Destructor
          */
         virtual ~PaintingBackend();

          /*!
           \brief This method is called to interrupt the work of the drawing thread as soon as possible.
           \param status The status of the cancellation. If "true", the drawing thread should be interrupted.
           */
         void cancelProcess(bool status);

          /*!
           \brief This method pushes a new transformation onto the transformation stack.
           \param t The transformation to be pushed onto the stack.
           */
         void pushTransform(const Transform& t);

          /*!
           \brief This method removes the top element from the transformation stack.
           */
         void popTransform();

          /*!
           \brief This method changes the color used for drawing on the target context.
           \param color The RGB color used for drawing.
           */
         virtual void setColor(Color color) = 0;

         /*!
         \brief Returns the current color used for drawing on the target context.
         */
         virtual Color color() const = 0;

          /*!
           \brief This method sets the line weight used for drawing the objects.
           \param lineweight The line weight.
           */
         virtual void setLineWeight(double lineweight) = 0;

         /*!
          /brief  Returns the current line weight used for drawing on the target context.
          */
         virtual double lineWeight() const = 0;

          /*!
           \brief This method moves the pen from the current position to the new position,
           without drawing anything.
           \param pt The new position in the WCS.
           */
         void moveTo(const Vertex3& pt);

          /*!
           \brief This method "draws" an invisible line to the new point. This is necessary because, for example, in hatching, the line pattern depends on the position and lines may be interrupted. Here, only the offset in the line pattern is changed.
           \param pt The new position in the WCS.
           */
         void blindTo(const Vertex3& pt);

          /*!
           \brief This method moves the pen from the current position to the new position,
           and draws a straight line in the process.
           \param pt The new position in the WCS.
           */
         void lineTo(const Vertex3& pt);

          /*!
           \brief This method closes the current path, draws it, and implicitly opens a new path.
           */
         void stroke();

          /*!
           \brief This method closes the current path, fills the enclosed area with the current color, and implicitly opens a new path.
           */
         virtual void fill() = 0;

          /*!
           \brief This method closes the current path, fills the enclosed area with the current color, draws it, and implicitly opens a new path.
           */
         virtual void fillAndStroke() = 0;

          /*!
           \brief This method is used to add the graphics primitive Arc to the current path.
           \details If the end angle is greater than the start angle, the arc is drawn in a counter-clockwise direction. If the end angle is less than the start angle, the arc is drawn in a clockwise direction.
           \param center The center of the arc in global WCS coordinates.
           \param normal The resulting direction vector of the arc plane.
           \param radius The scaled radius of the arc.
           \param startAngle The start angle in degrees.
           \param endAngle The end angle in degrees.
           */
         void arc(const Vertex3& center,
                  const Vertex3& normal,
                  double radius,
                  double startAngle,
                  double endAngle);

          /*!
           \brief This method is used to add the graphics primitive Elliptic to the current path.
           \param center The center of the ellipse in global WCS coordinates.
           \param majorAxis The major axis of the ellipse.
           \param minorAxis The minor axis of the ellipse.
           \param startAngle The start angle in radians.
           \param endAngle The end angle in radians.
           */
         void elliptic(const Vertex3& center,
                       const Vertex3& majorAxis,
                       const Vertex3& minorAxis,
                       double startAngle,
                       double endAngle);

          /*!
           \brief This method draws a NURBS (Non-Uniform Rational Basis-Spline) curve.
           \param nurbs The object describing the curve.
           */
         void nurbs(Nurbs* nurbs);

          /*!
           \brief This method draws a straight line between two points in the target context.
           \param start The starting point of the line.
           \param end The ending point of the line.
           */
         virtual void drawLineSegment(const Vertex3& start, const Vertex3& end) = 0;

         virtual void finishStroke() = 0;

          /*!
           \brief This method draws a point on the target context.
           \param point The point to be drawn.
           */
         virtual void drawPoint(const Vertex3& point) = 0;

          /*!
           \brief This method resets the line pattern for drawing, so that when starting
           a new line, the pattern starts from the beginning. This is particularly important
           for hatching.
           */
         virtual void resetLinePatternOffset() = 0;

         bool wantCancel();

      protected:

         void blindLine(const Vertex3& p1, const Vertex3& p2);

         void putLine(const Vertex3& p1, const Vertex3& p2, bool pendown);

      private:

          /*!
           \brief The stack of transformation settings... necessary for inserts.
           */
         std::vector<Transform>* mTransformstack;

          /*!
           \brief The current line style used for drawing lines, or NULL if a solid line is being drawn.
           \discussion All different line styles are manually drawn using strokes.
           */
         //dwg::LineType* mCurLineType;

          /*!
           \brief The current scaling factor of the line pattern.
           \details All different line styles are manually drawn using strokes.
           */
         double mCurLineTypeScale;

          /*!
           \brief Current position within the line pattern, relative to the beginning of the pattern.
           IN PATTERN SCALE (without curLineTypeScale).
           \details All different line styles are manually drawn using strokes.
           */
         double mLinePatternOffset;

          /*!
           \brief The position within the current element, relative to the beginning of the element.
           IN PATTERN SCALE (without curLineTypeScale).
           \details All different line styles are manually drawn using strokes.
           */
         double mLinePatternSubOffset;

          /*!
           \brief Zero-based index of the current element.
           \details All different line styles are manually drawn using strokes.
           */
         int32 mLinePatternIndex;

          /*!
           \brief This variable stores a flag indicating whether processing should be canceled or not.
           By default, this value is "false". However, if this value is set to "true" externally,
           the Painter must abort its work as soon as possible and return. This is useful for multi-threaded applications.
           */
         bool mCancel;

          /*!
           \brief The total transformation matrix. Needs to be recalculated after each Push and Pop operation on the transformation stack.
           */
         Transform mTrans;

          /*!
           \brief Buffer for storing the points that need to be drawn in a path.
           */
         std::vector<BufferElement>* mBuffer;

          /*!
           \brief This method updates the transformation matrix.
           */
         void updateTrans();

          /*!
           \brief This method transposes a point in OCS coordinates to the global WCS coordinates of the drawing, taking into account the current transformation settings.
           \details The main reason for changing the transformation settings is block references and nested block references.
           */
         Vertex3 trans(const Vertex3& pt) const;

   };

}

#endif
