//
//  UndoManagerTest.hpp
//  jameo
//
//  Created by Uwe Runtemund on 26.05.16.
//  Copyright © 2016 Jameo Software. All rights reserved.
//

#ifndef UndoManagerTest_h
#define UndoManagerTest_h

#include "core/UndoManager.h"
#include "core/Test.h"
class UndoTestObject: public jm::Object
{
   public:

      jm::UndoManager* undo;

      int8 b1;
      uint8 b2;
      int16 s1;
      uint16 s2;
      int32 i1;
      uint32 i2;
      int64 l1;
      uint64 l2;
      jm::String str;
      float f;
      double d;
      UndoTestObject* obj;

      UndoTestObject(): jm::Object()
      {
         str = jm::kEmptyString;
         b1 = 0;
         b2 = 0;
         s1 = 0;
         s2 = 0;
         i1 = 0;
         i2 = 0;
         l1 = 0;
         l2 = 0;
         f = 0;
         d = 0;
         obj = nullptr;
      }

      ~UndoTestObject()
      {
         if(obj != nullptr)obj->release();
      }

      void SetStr(jm::String value)
      {
         undo->registerChange(this, &str);
         str = value;
      }

      void SetFloat(float value)
      {
         undo->registerChange(this, &f);
         f = value;
      }

      void SetDouble(double value)
      {
         undo->registerChange(this, &d);
         d = value;
      }

      void SetInt8(int8 value)
      {
         undo->registerChange(this, &b1);
         b1 = value;
      }

      void SetUInt8(uint8 value)
      {
         undo->registerChange(this, &b2);
         b2 = value;
      }

      void SetInt16(int16 value)
      {
         undo->registerChange(this, &s1);
         s1 = value;
      }

      void SetUInt16(uint16 value)
      {
         undo->registerChange(this, &s2);
         s2 = value;
      }

      void SetInt32(int32 value)
      {
         undo->registerChange(this, &i1);
         i1 = value;
      }

      void SetUInt32(uint32 value)
      {
         undo->registerChange(this, &i2);
         i2 = value;
      }

      void SetInt64(int64 value)
      {
         undo->registerChange(this, &l1);
         l1 = value;
      }

      void SetUInt64(uint64 value)
      {
         undo->registerChange(this, &l2);
         l2 = value;
      }

      void SetObject(UndoTestObject* other)
      {
         undo->registerChange(this, reinterpret_cast<jm::Object**>(&obj));
         if(obj != nullptr)
         {
            undo->registerRelease(obj);
            obj->release();
         }
         obj = other;
         if(obj != nullptr)
         {
            undo->registerRetain(obj);
            obj->retain();
         }
      }

};

class UndoManagerTest : public jm::Test
{

   public:
      UndoManagerTest();
      void doTest();
      void TestRef(UndoTestObject* obj);
};


#endif /* UndoManagerTest_hpp */
