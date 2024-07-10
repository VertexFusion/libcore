////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Diff.cpp
// Library:     Jameo Core Library
// Purpose:     Implementation of dif algorithm
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     17.12.2013
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

DiffInfo::DiffInfo()
{

}

DiffInfo::DiffInfo(const DiffInfo &another)
{
   mOperation = another.mOperation;
}

void DiffInfo::Print(DiffOperation operation,
                     Integer obj1,
                     Integer obj2,
                     const String& label)
{
   switch(operation)
   {
      case kDiffAdd:
      case kDiffDelete:
         std::cout << "  " << label << ": " << obj1 << std::endl;
         break;

      case kDiffModified:
         if(obj1 != obj2)
         {
            std::cout << "  " << label << ": " << obj1 << " -> " << obj2 << " delta: " << (obj2 - obj1) << std::endl;
         }
         break;

      default:
         break;
   }
}

void DiffInfo::Print(DiffOperation operation,
                     double obj1,
                     double obj2,
                     const String &label)
{
   switch(operation)
   {
      case kDiffAdd:
      case kDiffDelete:
         std::cout << "  " << label << ": " << obj1 << std::endl;
         break;

      case kDiffModified:
         if(IsNotEqual(obj1, obj2))
         {
            std::cout << "  " << label << ": " << obj1 << " -> " << obj2 << " delta: " << (obj2 - obj1) << std::endl;
         }
         break;

      default:
         break;
   }
}

void DiffInfo::Print(DiffOperation operation,
                     const String &obj1,
                     const String &obj2,
                     const String &label)
{
   switch(operation)
   {
      case kDiffAdd:
      case kDiffDelete:
         std::cout << "  " << label << ": " << obj1 << std::endl;
         break;

      case kDiffModified:
         if(!obj1.equals(obj2))
         {
            std::cout << "  " << label << ": " << obj1 << " -> " << obj2 << std::endl;
         }
         break;

      default:
         break;
   }
}

void DiffInfo::PrintIC(DiffOperation operation,
                       const String &obj1,
                       const String &obj2,
                       const String &label)
{
   switch(operation)
   {
      case kDiffAdd:
      case kDiffDelete:
         std::cout << "  " << label << ": " << obj1 << std::endl;
         break;

      case kDiffModified:
         if(!obj1.equalsIgnoreCase(obj2))
         {
            std::cout << "  " << label << ": " << obj1 << " -> " << obj2 << std::endl;
         }
         break;

      default:
         break;
   }
}

void DiffInfo::Print(DiffOperation operation,
                     const Vertex2 &obj1,
                     const Vertex2 &obj2,
                     const String &label)
{
   switch(operation)
   {
      case kDiffAdd:
      case kDiffDelete:
         std::cout << "  " << label << ": ";
         std::cout << obj1 << std::endl;
         break;

      case kDiffModified:
         if(obj1 != obj2)
         {
            std::cout << "  " << label << ": ";
            std::cout << obj1 << " -> " << obj2 << std::endl;
         }
         break;

      default:
         break;
   }
}

void DiffInfo::Print(DiffOperation operation,
                     const Vertex3 &obj1,
                     const Vertex3 &obj2,
                     const String &label)
{
   switch(operation)
   {
      case kDiffAdd:
      case kDiffDelete:
         std::cout << "  " << label << ": ";
         std::cout << obj1 << std::endl;
         break;

      case kDiffModified:
         if(obj1 != obj2)
         {
            std::cout << "  " << label << ": ";
            std::cout << obj1 << " -> " << obj2 << std::endl;
         }
         break;

      default:
         break;
   }
}

/*

void DiffInfo::Print( dxf::DwgAppId* obj1, dxf::DwgAppId* obj2 )
{
	Print( obj1 != NULL ? obj1->applicationName : "", obj2 != NULL ? obj2->applicationName : "", "applicationName" );
	Print( obj1 != NULL ? obj1->flag : 0, obj2 != NULL ? obj2->flag : 0, "flag" );
}

void DiffInfo::Print( dxf::Arc* obj1, dxf::Arc* obj2 )
{
	Print( ( dxf::DwgCircle* )obj1, ( dxf::DwgCircle* )obj2 );
	Print( obj1 != NULL ? obj1->GetStartAngle() : 0, obj2 != NULL ? obj2->GetStartAngle() : 0, "startAngle" );
	Print( obj1 != NULL ? obj1->EndAngle() : 0, obj2 != NULL ? obj2->EndAngle() : 0 , "endAngle" );
}

void DiffInfo::Print( dxf::DwgCircle* obj1, dxf::DwgCircle* obj2 )
{
	Print( ( dxf::DwgEntity* )obj1, ( dxf::DwgEntity* )obj2 );
	Print( obj1 != NULL ? obj1->GetCenterPoint() : Vertex3(), obj2 != NULL ? obj2->GetCenterPoint() : Vertex3(), "centerPoint" );
	Print( obj1 != NULL ? obj1->GetRadius() : 0, obj2 != NULL ? obj2->GetRadius() : 0, "radius" );
	Print( obj1 != NULL ? obj1->GetExtrusionDirection() : Vertex3(), obj2 != NULL ? obj2->GetExtrusionDirection() : Vertex3(), "extrusionDirection" );
}

void DiffInfo::Print( dxf::Class* obj1, dxf::Class* obj2 )
{
	Print( obj1 != NULL ? obj1->dxfRecordName : "", obj2 != NULL ? obj2->dxfRecordName : "", "dxfRecordName" );
	Print( obj1 != NULL ? obj1->cppClassName : "", obj2 != NULL ? obj2->cppClassName : "", "cppClassName" );
	Print( obj1 != NULL ? obj1->appName : "", obj2 != NULL ? obj2->appName : "", "appName" );
	Print( obj1 != NULL ? obj1->handle : 0, obj2 != NULL ? obj2->handle : 0, "handle" );
	Print( obj1 != NULL ? obj1->proxyFlag : 0, obj2 != NULL ? obj2->proxyFlag : 0, "proxyFlag" );
	Print( obj1 != NULL ? obj1->instanceCount : 0, obj2 != NULL ? obj2->instanceCount : 0, "instanceCount" );
	Print( obj1 != NULL ? obj1->wasAProxyFlag : 0, obj2 != NULL ? obj2->wasAProxyFlag : 0, "wasAProxyFlag" );
	Print( obj1 != NULL ? obj1->isAnEntityFlag : 0, obj2 != NULL ? obj2->isAnEntityFlag : 0, "isAnEntityFlag" );
}

void DiffInfo::Print( dxf::DictionaryVar* obj1, dxf::DictionaryVar* obj2 )
{
	Print( obj1 != NULL ? obj1->objectSchemaNumber : 0, obj2 != NULL ? obj2->objectSchemaNumber : 0, "objectSchemaNumber" );
	Print( obj1 != NULL ? obj1->value : "", obj2 != NULL ? obj2->value : "", "value" );
}

void DiffInfo::Print( dxf::DwgEllipse* obj1, dxf::DwgEllipse* obj2 )
{
	Print( ( dxf::DwgEntity* )obj1, ( dxf::DwgEntity* )obj2 );
	Print( obj1 != NULL ? obj1->GetCenterPoint() : Vertex3(), obj2 != NULL ? obj2->GetCenterPoint() : Vertex3(), "centerPoint" );
	Print( obj1 != NULL ? obj1->GetMajorAxis() : Vertex3(), obj2 != NULL ? obj2->GetMajorAxis() : Vertex3(), "majorAxis" );
	Print( obj1 != NULL ? obj1->GetExtrusionDirection() : Vertex3(), obj2 != NULL ? obj2->GetExtrusionDirection() : Vertex3(), "extrusionDirection" );
	Print( obj1 != NULL ? obj1->GetMinorAxis() : Vertex3(), obj2 != NULL ? obj2->GetMinorAxis() : Vertex3(), "minorAxis" );
	Print( obj1 != NULL ? obj1->GetStartPoint() : 0, obj2 != NULL ? obj2->GetStartPoint() : 0, "linetypeScale" );
	Print( obj1 != NULL ? obj1->GetEndPoint() : 0, obj2 != NULL ? obj2->GetEndPoint() : 0, "linetypeScale" );
}

void DiffInfo::Print( dxf::DwgFace3d* obj1, dxf::DwgFace3d* obj2 )
{
	Print( ( dxf::DwgEntity* )obj1, ( dxf::DwgEntity* )obj2 );
	Print( obj1 != NULL ? obj1->corner1 : Vertex3(), obj2 != NULL ? obj2->corner1 : Vertex3(), "corner1" );
	Print( obj1 != NULL ? obj1->corner2 : Vertex3(), obj2 != NULL ? obj2->corner2 : Vertex3(), "corner2" );
	Print( obj1 != NULL ? obj1->corner3 : Vertex3(), obj2 != NULL ? obj2->corner3 : Vertex3(), "corner3" );
	Print( obj1 != NULL ? obj1->corner4 : Vertex3(), obj2 != NULL ? obj2->corner4 : Vertex3(), "corner4" );
	Print( obj1 != NULL ? obj1->invisibleFlag : 0, obj2 != NULL ? obj2->invisibleFlag : 0, "invisibleFlag" );
}

void DiffInfo::Print( dxf::LineType* obj1, dxf::LineType* obj2 )
{
	Print( obj1 != NULL ? obj1->GetElementCount() : 0, obj2 != NULL ? obj2->GetElementCount() : 0, "elementCount" );
	Print( obj1 != NULL ? obj1->flags : 0, obj2 != NULL ? obj2->flags : 0, "flags" );
	Print( obj1 != NULL ? obj1->GetAlignmentCode() : 0, obj2 != NULL ? obj2->GetAlignmentCode() : 0, "alignmentCode" );
	Print( obj1 != NULL ? obj1->name() : "", obj2 != NULL ? obj2->name() : "", "lineTypeName" );
	Print( obj1 != NULL ? obj1->description : "", obj2 != NULL ? obj2->description : "", "description" );
	Print( obj1 != NULL ? obj1->totalPatternLength : 0, obj2 != NULL ? obj2->totalPatternLength : 0, "totalPatternLength" );


	int o1ec = obj1 != NULL ? obj1->GetElementCount() : 0;
	int o2ec = obj2 != NULL ? obj2->GetElementCount() : 0;

	int cmin = std::min( o1ec, o2ec );
	int cmax = std::max( o1ec, o2ec );
	for( int a = 0; a < cmax; a++ )
	{
		if( a < cmin )
		{
			LTypeElement e1 = obj1->GetElement( a );
			LTypeElement e2 = obj2->GetElement( a );
			Print( e1.ddsLength, e2.ddsLength, "ddsLength" );
			Print( e1.elementType, e2.elementType, "elementType" );
		}
		else if( o1ec > a )std::cout << "D  LTypeElement\n";
		else std::cout << "A LTypeElement\n";
	}

}

void DiffInfo::Print( dxf::Material* obj1, dxf::Material* obj2 )
{
	Print( obj1 != NULL ? obj1->name : "", obj2 != NULL ? obj2->name : "", "name" );
	Print( obj1 != NULL ? obj1->description : "", obj2 != NULL ? obj2->description : "", "description" );

	String name;
	String description;
	int diffuseMapSource;
	int specularMapSource;
	int reflectionMapSource;
	int opacityMapSource;
	int bumpmapSource;
	int projectionMethodDiffuseMapper;
	int projectionMethodSpecularMapper;
	int projectionMethodReflectionMapper;
	int projectionMethodOpacityMapper;
	int projectionMethodBumpmapMapper;
	int projectionMethodRefractionMapper;
	double diffuseMapTransformMatrix[16];
	int diffuseIdx;
	double specularMapTransformMatrix[16];
	int specularIdx;
	double reflectionMapTransformMatrix[16];
	int reflectionIdx;
	double opacityMapTransformMatrix[16];
	int opacityIdx;
	double bumpmapMapTransformMatrix[16];
	int bumpmapIdx;
	double refractionMapTransformMatrix[16];
	int refractionIdx;

}

void DiffInfo::Print( dxf::MultiText* obj1, dxf::MultiText* obj2 )
{
	Print( ( dxf::DwgEntity* )obj1, ( dxf::DwgEntity* )obj2 );
	Print( obj1 != NULL ? obj1->GetText() : "", obj2 != NULL ? obj2->GetText() : "", "text" );
	Print( obj1 != NULL ? obj1->insertionPoint : Vertex3(), obj2 != NULL ? obj2->insertionPoint : Vertex3(), "insertionPoint" );
	Print( obj1 != NULL ? obj1->directionVector : Vertex3(), obj2 != NULL ? obj2->directionVector : Vertex3(), "directionVector" );
	Print( obj1 != NULL ? obj1->lineSpacingFactor : 0, obj2 != NULL ? obj2->lineSpacingFactor : 0, "lineSpacingFactor" );
	Print( obj1 != NULL ? obj1->height : 0, obj2 != NULL ? obj2->height : 0, "height" );
	Print( obj1 != NULL ? obj1->refRectWidth : 0, obj2 != NULL ? obj2->refRectWidth : 0, "refRectWidth" );
	Print( obj1 != NULL ? obj1->rotation : 0, obj2 != NULL ? obj2->rotation : 0, "rotation" );
	Print( obj1 != NULL ? obj1->styleName : "", obj2 != NULL ? obj2->styleName : "", "styleName" );
	Print( obj1 != NULL ? obj1->attachmentPoint : 0, obj2 != NULL ? obj2->attachmentPoint : 0, "attachmentPoint" );
	Print( obj1 != NULL ? obj1->drawingDirection : 0, obj2 != NULL ? obj2->drawingDirection : 0, "drawingDirection" );
	Print( obj1 != NULL ? obj1->lineSpacingStyle : 0, obj2 != NULL ? obj2->lineSpacingStyle : 0, "lineSpacingStyle" );
	Print( obj1 != NULL ? obj1->backgroundFillSetting : 0, obj2 != NULL ? obj2->backgroundFillSetting : 0, "backgroundFillSetting" );
	Print( obj1 != NULL ? obj1->backgroundFillColour : 0, obj2 != NULL ? obj2->backgroundFillColour : 0, "backgroundFillColour" );
	Print( obj1 != NULL ? obj1->transparencyOfBackgroundFillColour : 0, obj2 != NULL ? obj2->transparencyOfBackgroundFillColour : 0, "transparencyOfBackgroundFillColour" );
	Print( obj1 != NULL ? obj1->fillBoxScale : 0, obj2 != NULL ? obj2->fillBoxScale : 0, "fillBoxScale" );

	for( int a = 0; a < 10; a++ )Print( obj1 != NULL ? obj1->backgroundColour[a] : 0, obj2 != NULL ? obj2->backgroundColour[a] : 0, "backgroundColour" );

}

void DiffInfo::Print( dxf::Point* obj1, dxf::Point* obj2 )
{
	Print( ( dxf::DwgEntity* )obj1, ( dxf::DwgEntity* )obj2 );
	Print( obj1 != NULL ? obj1->position() : Vertex3(), obj2 != NULL ? obj2->position() : Vertex3(), "position" );
	Print( obj1 != NULL ? obj1->GetXAxisAngle() : 0, obj2 != NULL ? obj2->GetXAxisAngle() : 0, "xAxixAngle" );
	Print( obj1 != NULL ? obj1->GetExtrusionDirection() : Vertex3(), obj2 != NULL ? obj2->GetExtrusionDirection() : Vertex3(), "extrusiondirection" );
}

void DiffInfo::Print( dxf::Scale* obj1, dxf::Scale* obj2 )
{
	Print( obj1 != NULL ? obj1->name : "", obj2 != NULL ? obj2->name : "", "name" );
	Print( obj1 != NULL ? obj1->paperUnits : 0, obj2 != NULL ? obj2->paperUnits : 0, "paperUnits" );
	Print( obj1 != NULL ? obj1->drawingUnits : 0, obj2 != NULL ? obj2->drawingUnits : 0, "drawingUnits" );
	Print( obj1 != NULL ? obj1->hasUnitScale : 0, obj2 != NULL ? obj2->hasUnitScale : 0, "hasUnitScale" );
	Print( obj1 != NULL ? obj1->flags : 0, obj2 != NULL ? obj2->flags : 0, "flags" );
}

void DiffInfo::Print( dxf::Style* obj1, dxf::Style* obj2 )
{
	Print( obj1 != NULL ? obj1->name() : "", obj2 != NULL ? obj2->name() : "", "styleName" );
	Print( obj1 != NULL ? obj1->primaryFontFileName : "", obj2 != NULL ? obj2->primaryFontFileName : "", "primaryFontFileName" );
	Print( obj1 != NULL ? obj1->bigFontFileName : "", obj2 != NULL ? obj2->bigFontFileName : "", "bigFontFileName" );
	Print( obj1 != NULL ? obj1->fixedTextHeight : 0, obj2 != NULL ? obj2->fixedTextHeight : 0, "fixedTextHeight" );
	Print( obj1 != NULL ? obj1->widthFactor : 0, obj2 != NULL ? obj2->widthFactor : 0, "widthFactor" );
	Print( obj1 != NULL ? obj1->lastHeightUsed : 0, obj2 != NULL ? obj2->lastHeightUsed : 0, "lastHeightUsed" );
	Print( obj1 != NULL ? obj1->obliqueAngle : 0, obj2 != NULL ? obj2->obliqueAngle : 0, "obliqueAngle" );
	Print( obj1 != NULL ? obj1->flags : 0, obj2 != NULL ? obj2->flags : 0, "flags" );
	Print( obj1 != NULL ? obj1->textGenerationFlags : 0, obj2 != NULL ? obj2->textGenerationFlags : 0, "textGenerationFlags" );
}

void DiffInfo::Print( dxf::DwgTrace* obj1, dxf::DwgTrace* obj2 )
{
	Print( ( dxf::DwgEntity* )obj1, ( dxf::DwgEntity* )obj2 );
	Print( obj1 != NULL ? obj1->corner1 : Vertex3(), obj2 != NULL ? obj2->corner1 : Vertex3(), "corner1" );
	Print( obj1 != NULL ? obj1->corner2 : Vertex3(), obj2 != NULL ? obj2->corner2 : Vertex3(), "corner2" );
	Print( obj1 != NULL ? obj1->corner3 : Vertex3(), obj2 != NULL ? obj2->corner3 : Vertex3(), "corner3" );
	Print( obj1 != NULL ? obj1->corner4 : Vertex3(), obj2 != NULL ? obj2->corner4 : Vertex3(), "corner4" );
	Print( obj1 != NULL ? obj1->extrusionDirection : Vertex3(), obj2 != NULL ? obj2->extrusionDirection : Vertex3(), "extrusionDirection" );
}

void DiffInfo::Print( dxf::DwgViewport* obj1, dxf::DwgViewport* obj2 )
{
	Print( obj1 != NULL ? obj1->centerPoint : 0, obj2 != NULL ? obj2->centerPoint : 0, "centerPoint" );
	Print( obj1 != NULL ? obj1->paperWidth : 0, obj2 != NULL ? obj2->paperWidth : 0, "paperWidth" );
	Print( obj1 != NULL ? obj1->paperHeight : 0, obj2 != NULL ? obj2->paperHeight : 0, "paperHeight" );
	Print( obj1 != NULL ? obj1->viewportStatus : 0, obj2 != NULL ? obj2->viewportStatus : 0, "viewportStatus" );
	Print( obj1 != NULL ? obj1->viewportID : 0, obj2 != NULL ? obj2->viewportID : 0, "viewportID" );
	Print( obj1 != NULL ? obj1->viewCenterPoint : Vertex2(), obj2 != NULL ? obj2->viewCenterPoint : Vertex2(), "viewCenterPoint" );
	Print( obj1 != NULL ? obj1->snapBasePoint : Vertex2(), obj2 != NULL ? obj2->snapBasePoint : Vertex2(), "snapBasePoint" );
	Print( obj1 != NULL ? obj1->snapSpacing : Vertex2(), obj2 != NULL ? obj2->snapSpacing : Vertex2(), "snapSpacing" );
	Print( obj1 != NULL ? obj1->gridSpacing : Vertex2(), obj2 != NULL ? obj2->gridSpacing : Vertex2(), "gridSpacing" );
	Print( obj1 != NULL ? obj1->viewDirectionVector : 0, obj2 != NULL ? obj2->viewDirectionVector : 0, "viewDirectionVector" );
	Print( obj1 != NULL ? obj1->viewTargetPoint : 0, obj2 != NULL ? obj2->viewTargetPoint : 0, "viewTargetPoint" );

	Print( obj1 != NULL ? obj1->perspectiveLensLength : 0, obj2 != NULL ? obj2->perspectiveLensLength : 0, "perspectiveLensLength" );
	Print( obj1 != NULL ? obj1->frontClipZValue : 0, obj2 != NULL ? obj2->frontClipZValue : 0, "frontClipZValue" );
	Print( obj1 != NULL ? obj1->backClickZValue : 0, obj2 != NULL ? obj2->backClickZValue : 0, "backClickZValue" );
	Print( obj1 != NULL ? obj1->viewHeight : 0, obj2 != NULL ? obj2->viewHeight : 0, "viewHeight" );
	Print( obj1 != NULL ? obj1->snapAngle : 0, obj2 != NULL ? obj2->snapAngle : 0, "snapAngle" );
	Print( obj1 != NULL ? obj1->viewTwistAngle : 0, obj2 != NULL ? obj2->viewTwistAngle : 0, "viewTwistAngle" );
	Print( obj1 != NULL ? obj1->circleZoomPercent : 0, obj2 != NULL ? obj2->circleZoomPercent : 0, "circleZoomPercent" );
	Print( obj1 != NULL ? obj1->viewportStatusFlag : 0, obj2 != NULL ? obj2->viewportStatusFlag : 0, "viewportStatusFlag" );
	Print( obj1 != NULL ? obj1->plotStyleSheetName : 0, obj2 != NULL ? obj2->plotStyleSheetName : 0, "plotStyleSheetName" );
	Print( obj1 != NULL ? obj1->renderMode : 0, obj2 != NULL ? obj2->renderMode : 0, "renderMode" );
	Print( obj1 != NULL ? obj1->ucsViewportFlag : 0, obj2 != NULL ? obj2->ucsViewportFlag : 0, "ucsViewportFlag" );
	Print( obj1 != NULL ? obj1->ucsIconOriginFlag : 0, obj2 != NULL ? obj2->ucsIconOriginFlag : 0, "ucsIconOriginFlag" );
	Print( obj1 != NULL ? obj1->ucsOrigin : 0, obj2 != NULL ? obj2->ucsOrigin : 0, "ucsOrigin" );
	Print( obj1 != NULL ? obj1->ucsXAxis : 0, obj2 != NULL ? obj2->ucsXAxis : 0, "ucsXAxis" );
	Print( obj1 != NULL ? obj1->ucsYAxis : 0, obj2 != NULL ? obj2->ucsYAxis : 0, "ucsYAxis" );
	Print( obj1 != NULL ? obj1->orthograficUCSType : 0, obj2 != NULL ? obj2->orthograficUCSType : 0, "orthograficUCSType" );
	Print( obj1 != NULL ? obj1->elevation : 0, obj2 != NULL ? obj2->elevation : 0, "elevation" );
	Print( obj1 != NULL ? obj1->shadePlotMode : 0, obj2 != NULL ? obj2->shadePlotMode : 0, "shadePlotMode" );
	Print( obj1 != NULL ? obj1->clippindBoundary : 0, obj2 != NULL ? obj2->clippindBoundary : 0, "clippindBoundary" );


	unsigned long o1ec = obj1 != NULL ? obj1->frozenLayerObjects.size() : 0;
	unsigned long o2ec = obj2 != NULL ? obj2->frozenLayerObjects.size() : 0;

	unsigned long cmin = std::min( o1ec, o2ec );
	unsigned long cmax = std::max( o1ec, o2ec );
	for( unsigned long a = 0; a < cmax; a++ )
	{
		if( a < cmin )
		{
			Print( obj1 != NULL ? obj1->frozenLayerObjects[a] : 0, obj2 != NULL ? obj2->frozenLayerObjects[a] : 0, "frozenLayerObjects" );
		}
		else if( o1ec > a )std::cout << "D  frozenLayerObject " << std::endl ;
		else std::cout << "A frozenLayerObjects\n";
	}


	vector<Handle>frozenLayerObjects;

}

void DiffInfo::Print( dxf::DwgXRecord* obj1, dxf::DwgXRecord* obj2 )
{
	Print( obj1 != NULL ? obj1->duplicateCloningFlag : 0, obj2 != NULL ? obj2->duplicateCloningFlag : 0, "duplicateCloningFlag" );
	Print( obj1 != NULL ? ( int )obj1->groupCode.size() : 0, obj2 != NULL ? ( int )obj2->groupCode.size() : 0, "entryCount" );

	int o1ec = obj1 != NULL ? obj1->value.size() : 0;
	int o2ec = obj2 != NULL ? obj2->value.size() : 0;

	int cmin = ( int )std::min( o1ec, o2ec );
	int cmax = ( int )std::max( o1ec, o2ec );
	for( int a = 0; a < cmax; a++ )
	{
		if( a < cmin )
		{
			Print( obj1 != NULL ? obj1->groupCode[a] : 0, obj2 != NULL ? obj2->groupCode[a] : 0, "groupCode" );
			Print( obj1 != NULL ? obj1->value[a] : "", obj2 != NULL ? obj2->value[a] : "", "value" );
		}
		else if( o1ec > a )std::cout << "D  Entry: " << obj1->groupCode[a] << " " << obj1->value[a] << std::endl ;
		else std::cout << "A Entry\n";
	}

}
*/

void DiffInfo::Print(DiffOperation operation, Object* obj1, Object* obj2)
{

   mOperation = operation;

   //Wenn beide Objekte NULL sind, gab es keine Änderungen
   if(obj1 == NULL && obj2 == NULL)
   {
      return;
   }

   //Beide Objekte müssen vom identischen Typ sein.

   //Object wurde durch ein anderes ersetzt
   if(obj1 != NULL &&
         obj2 != NULL &&
         typeid(*obj1) != typeid(*obj2) &&
         operation == kDiffModified)
   {
      std::cout << "R " << obj1->displayName() << " -> " << obj2->displayName() << ":" << std::endl;
      return;
   }

   if(obj1 == NULL)
   {
      std::cout << "<NULL_PROBLEM>"  << std::endl;
      return;
   }

   //Gib Überschrift aus:
   if(operation == kDiffAdd)
   {
      std::cout << "A " << obj1->displayName() << std::endl;
   }
   else if(operation == kDiffDelete)
   {
      std::cout << "D " << obj1->displayName() << std::endl;
   }
   else if(operation == kDiffModified)
   {
      std::cout << "M " << obj1->displayName() << std::endl;
   }
   else return;

   // Output details. Object1 is not NULL in any case
   // Only for Modified, otherwise there is too much information. TODO Make it optional?
   if(operation == kDiffModified)obj1->printDiffInfo(operation, obj2);
   //else if(operation == kDiffAdd)obj1->printDiffInfo(operation, NULL);

}
