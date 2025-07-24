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

      int8 b1 = 0;
      uint8 b2 = 0;
      int16 s1 = 0;
      uint16 s2 = 0;
      int32 i1 = 0;
      uint32 i2 = 0;
      int64 l1 = 0;
      uint64 l2 = 0;
      jm::String str = jm::kEmptyString;
      float f = 0.0;
      double d = 0.0;
      UndoTestObject* obj = nullptr;

      UndoTestObject(): jm::Object()
      {
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
