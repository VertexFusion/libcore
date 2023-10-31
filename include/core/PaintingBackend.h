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
#include "Colour.h"

#include "Transform.h"
#include "Nurbs.h"
//#include "dwg/DwgLineType.h"

namespace jm
{

	/*!
	 \brief Interne Enumeration umd BufferElement genauer zu beschreiben
	 */
	enum BufferMode
	{
		kBmMoveTo,
		kBmLineTo,
		kBmBlindTo
	};

	/*!
	 \brief Struktut speichert die Zeicheninformationen
	 */
	struct DllExport BufferElement
	{
		Vertex3 point;
		BufferMode mode; //0=move-To 1=line-To 2=Blind-To
		BufferElement(Vertex3 point, BufferMode mode)
		{
			this->point = point;
			this->mode = mode;
		}
	};

	/*!
	 \brief Dies Klasse stellt die Vaterklasse für die Grafikausgabe zur Verfügung. Diese Klasse
	 zeichnet.
	 */
	class DllExport PaintingBackend: public Object
	{
		public:

			/*!
			 \brief Konstruktor
			 */
			PaintingBackend();

			/*!
			 \brief Destructor
			 */
			~PaintingBackend();


			/*!
			 \brief Wenn diese Methode aufgerufen wird, wird die Arbeit des Zeichnenden Threads
			 sobald wie möglich unterbrochen.
			 */
			void CancelProcess(bool status);

			/*!
			 \brief Diese Methode legt eine neue Transformation auf dem Transformationsstapel ab.
			 */
			void PushTransform(const Transform &t);

			/*!
			 \brief Diese Methode löscht das obere Element auf dem Transformationsstapel.
			 */
			void PopTransform();

			/*!
			 \brief Diese Methode wechselt auf dem Zielkontext die Farbe mit der gezeichnet wird
			 \param colour Die RGB-Farbe, mit der gezeichnet wird.
			 */
			virtual void SetColour(Colour colour) = 0;

			virtual Colour GetColour() const = 0;

			/*!
			 \brief Diese Methode legt die Strichstärke fest, mit der die Objekte gezeichnet werden
			 \param lineweight Die Strichstärke.
			 */
			virtual void SetLineWeight(Double lineweight) = 0;

			virtual double GetLineWeight() const = 0;

			/*!
			 \brief Diese Methode bewegt den Stift von der aktuellen Position zur neuen Position,
			 ohne etwas zu zeichnen.
			 \param pt Die neue Position im WKS.
			 */
			void MoveTo(const Vertex3 &pt);

			/*!
			 \brief Diese Methode "zeichnet" eine unsichtbare Linie zum neuen Punkt. Das ist
			 notwendig, weil z.B. bei Schraffuren das Linienmuster positionsabhängig ist und Linien
			 ggf. unterbrochen gezeichnet werden. Hier wird also "nur" der Offset im Linienmuster
			 verändert.
			 \param pt Die neue Position im WKS.
			 */
			void BlindTo(const Vertex3 &pt);

			/*!
			 \brief Diese Methode bewegt den Stift von der aktuellen Position zur neuen Position,
			 und zeichnet dabei eine gerade Linie.
			 \param pt Die neue Position im WKS.
			 */
			void LineTo(const Vertex3 &pt);

			/*!
			 \brief Diese Methode schließt den aktuellen Pfad, zeichnet Ihn und öffnet einen neuen
			 Pfad implizit.
			 */
			void Stroke();

			/*!
			 \brief Diese Methode schließt den aktuellen Pfad, füllt die umschließende Fläche mit
			 der aktuellen Farbe aus und öffnet einen neuen Pfad implizit.
			 */
			virtual void Fill() = 0;

			/*!
			 \brief Diese Methode schließt den aktuellen Pfad, füllt die umschließende Fläche,
			 zeichnet Ihn und öffnet einen neuen Pfad implizit.
			 */
			virtual void FillAndStroke() = 0;

			/*!
			 \brief Diese Methode dient dazu, zum aktuellen Pfad das Grafikprimitiv Kreisbogen
			 hinzuzufügen.
			 \discussion Wenn der Endwinkel größer als der Startwinkel ist, wird entgegen des
			 Uhrzeigersinns gezeichnet, wenn der Endwinkel kleiner dem Startwinkel ist, wird in
			 Uhrzeigerrichtung gezeichnet
			 \param center Der Kreismittelpunkt in globalen WCS-Koordinaten
			 \param normal Der resultierende Richtungsvektor der Kreisebene.
			 \param radius Der skalierte Kreisradius.
			 \param startAngle Der Startwinkel im Gradmaß
			 \param endAngle Der Endwinkel im Gradmaß
			 */
			void Arc(const Vertex3 &center,
			         const Vertex3 &normal,
				Double radius,
				Double startAngle,
				Double endAngle);

			/*!
			 \brief Diese Methode dient dazu, zum aktuellen Pfad das Grafikprimitiv Ellipsenbogen
			 hinzuzufügen.
			 \param center Der Kreismittelpunkt in globalen WCS-Koordinaten
			 \param majorAxis Hauptachse der Ellipse
			 \param minorAxis Nebenachse der Ellipse
			 \param startAngle Der Startwinkel im Bogenmaß
			 \param endAngle Der Endwinkel im BOgenmaß
			 */
			void Elliptic(const Vertex3 &center,
			              const Vertex3 &majorAxis,
			              const Vertex3 &minorAxis,
				Double startAngle,
				Double endAngle);

			/*!
			 \brief Diese Methode zeichnet eine NURBS (Non-Uniform Rational Basis-Spline).
			 \param nurbs Das beschreibende Objekt für die Kurve.
			 */
			void Nurbs(Nurbs* nurbs);

			/*!
			 \brief Diese Methode zeichnet eine gerade Linie zwischen zwei Punkten im Zielkontext
			 */
			virtual void DrawLineSegment(const Vertex3 &start, const Vertex3 &end) = 0;

			virtual void FinishStroke() = 0;

			/*!
			 \brief Punkt zeichnen
			 */
			virtual void DrawPoint(const Vertex3 &point) = 0;

			/*!
			 \brief Diese Methode setzt das Linienmuster zum Zeichnen zurück, damit beim Beginn
			 einer neuen Linie das Muster von vorne startet. Dies ist insbesondere bei Schraffuren
			 wichtig.
			 */
			virtual void ResetLinePatternOffset() = 0;

			bool WantCancel();

		protected:

			void BlindLine(const Vertex3 &p1, const Vertex3 &p2);

			void PutLine(const Vertex3 &p1, const Vertex3 &p2, bool pendown);

		private:

			/*!
			 \brief Der Stack mit den Transformationseinstellungen... Notwendig bei Inserts
			 */
			std::vector<Transform>* transformstack;

			/*!
			 \brief Der aktuelle Linienstil, mit dem Linien gezeichnet werden, oder NULL,
			 wenn eine durchgehende Linie gezeichnet wird.
			 \discussion Alle verschiedenen Linienstile werden manuell aus Strichen gezeichnet.
			 */
			//dwg::LineType* curLineType;

			/*!
			 \brief Die aktuelle Skalierung des Linienmusters.
			 \discussion Alle verschiedenen Linienstile werden manuell aus Strichen gezeichnet.
			 */
			Double curLineTypeScale;

			/*!
			 \brief Position im gesamten Pattern, an dem man gerade steht (vom Anfang des Pattern).
			 IN PATTERNSKALIERUNG (also ohne curLineTypeScale)
			 \discussion Alle verschiedenen Linienstile werden manuell aus Strichen gezeichnet.
			 */
			Double linePatternOffset;

			/*!
			 \brief Position im aktuellen Element, an dem man gerade steht (vom Anfang des Elements)
			 IN PATTERNSKALIERUNG (also ohne curLineTypeScale)
			 \discussion Alle verschiedenen Linienstile werden manuell aus Strichen gezeichnet.
			 */
			Double linePatternSubOffset;

			/*!
			 \brief 0-basierter Index des aktuellen Elementes
			 \discussion Alle verschiedenen Linienstile werden manuell aus Strichen gezeichnet.
			 */
			int linePatternIndex;

			/*!
			 \brief Diese Variable speichert einen Flag, ob das Verarbeiten abgebrochen werden soll,
			 oder nicht. Standardmäßig ist dieser Wert "Falsch". Wenn aber extern dieser Wert auf
			 "Wahr" gesetzt wird, muss der Painter so schnell wie möglich seine Arbeit abbrechen und
			 zurückkehren. Das ist eine Hilfe für Multi-Thread-Anwendungen.
			 */
			bool cancel;

			/*!
			 \brief Die Gesamte Transformationsmatrix. Muss nach jedem Push und Pop vom
			 Transformationsstack neu berechnet werden.
			 */
			Transform trans;

			/*!
			 \brief Zwischenspeicher für die Punkte, die in einem Pfad gezeichnet werden müssen.
			 */
			std::vector<BufferElement>* buffer;

			/*!
			 \brief Aktualisiert die Transofrmationsmatrix
			 */
			void UpdateTrans();

			/*!
			 \brief Diese Methode dient dazu, einen Punkt in OCS-Koordinaten unter Berücksichtigung
			 der aktuellen Transformationseinstellungen in die globalen WCS-Koordinaten der Zeichnung
			 zu transponieren.
			 \discussion Wesentlicher Grund für die Veränderung der Transformationseinstellungen sind
			 Blockreferenzen und verschachtelte Blockreferenzen.
			 */
			Vertex3 Trans(const Vertex3 &pt) const;

	};

}

#endif /* CADPainter_h */
