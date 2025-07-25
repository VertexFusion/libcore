//
//  UndoManagerTest.cpp
//  jameo
//
//  Created by Uwe Runtemund on 26.05.16.
//  Copyright © 2016 Jameo Software. All rights reserved.
//

#include "core/UndoManager.h"
#include "UndoManagerTest.h"

using namespace jm;

// Reference values
jm::String str = jm::kEmptyString;
int8 b1 = 0;
uint8 b2 = 0;
int16 s1 = 0;
uint16 s2 = 0;
int32 i1 = 0;
uint32 i2 = 0;
int64 l1 = 0;
uint64 l2 = 0;
float f = 0;
double d = 0;
UndoTestObject* o = nullptr;

void UndoManagerTest::TestRef(UndoTestObject* obj)
{
   testEquals(obj->str, str, "str wrong.");
   testEquals(obj->b1, b1, "b1 wrong.");
   testEquals(obj->b2, b2, "b2 wrong.");
   testEquals(obj->s1, s1, "s1 wrong.");
   testEquals(obj->s2, s2, "s2 wrong.");
   testEquals(obj->i1, i1, "i1 wrong.");
   testEquals(obj->i2, i2, "i2 wrong.");
   testEquals(obj->l1, l1, "l1 wrong.");
   testEquals(obj->l2, l2, "l2 wrong.");
   testEquals(obj->f, f, "f wrong.");
   testEquals(obj->d, d, "d wrong.");
   testEquals(obj->obj, o, "obj wrong.");
}


UndoManagerTest::UndoManagerTest(): Test()
{
   setName("Test Undo Manager");
}

void UndoManagerTest::doTest()
{
   UndoManager* undo = new UndoManager();
   undo->setActive(true);

   UndoTestObject* obj = new UndoTestObject();
   obj->undo = undo;

   // Check object
   testEquals(obj->referenceCount(), 1, "Reference Counter must be 1.");
   testEquals(undo->undoCount(), 0, "Undostack not empty. (1)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (1)");

   TestRef(obj);

   //
   //String verändern
   //
   obj->SetStr("Hallo Welt");//Hier wird der Ref-Zähler erhöht, weil ein undo-Step erzeugt wird
   str = "Hallo Welt";
   undo->close();

   // Check object
   testEquals(obj->referenceCount(), 2, "Reference Counter must be 2.");
   testEquals(undo->undoCount(), 1, "Undostack not empty. (2)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (2)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   str = jm::kEmptyString;

   testEquals(obj->referenceCount(), 2,
              "Reference Counter must be 2.");//Undo ändert nichts am Referenzzähler...
   testEquals(undo->undoCount(), 0, "Undostack not empty.(3)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(3)");

   TestRef(obj);

   //Einfügen wiederherstellen
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   str = "Hallo Welt";

   testEquals(obj->referenceCount(), 2,
              "Referenzzähler muss 2 sein.");//Redo ändert nichts am Referenzzähler...
   testEquals(undo->undoCount(), 1, "Undostack not empty. (4)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(4)");

   TestRef(obj);

   //
   //double verändern
   //
   obj->SetDouble(24.08);
   d = 24.08;
   undo->close();

   // Check object
   testEquals(obj->referenceCount(), 3, "Referenzzähler muss 3 sein.");
   testEquals(undo->undoCount(), 2, "Undostack not empty. (5)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (5)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   d = 0;

   testEquals(obj->referenceCount(), 3,
              "Referenzzähler muss 3 sein.");//Undo ändert nichts am Referenzzähler...
   testEquals(undo->undoCount(), 1, "Undostack not empty.(6)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(6)");

   TestRef(obj);

   //Einfügen wiederherstellen
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   d = 24.08;

   testEquals(obj->referenceCount(), 3,
              "Referenzzähler muss 3 sein.");//Redo ändert nichts am Referenzzähler...
   testEquals(undo->undoCount(), 2, "Undostack not empty. (7)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(7)");

   TestRef(obj);

   //
   //int8 verändern
   //
   obj->SetInt8(17);
   b1 = 17;
   undo->close();

   // Check object
   testEquals(obj->referenceCount(), 4, "Referenzzähler muss 4 sein.");
   testEquals(undo->undoCount(), 3, "Undostack not empty. (8)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (8)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   b1 = 0;

   testEquals(obj->referenceCount(), 4,
              "Referenzzähler muss 4 sein.");//Undo ändert nichts am Referenzzähler...
   testEquals(undo->undoCount(), 2, "Undostack not empty.(9)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(9)");

   TestRef(obj);

   //Einfügen wiederherstellen
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   b1 = 17;

   testEquals(obj->referenceCount(), 4,
              "Referenzzähler muss 4 sein.");//Redo ändert nichts am Referenzzähler...
   testEquals(undo->undoCount(), 3, "Undostack not empty. (10)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(10)");

   TestRef(obj);

   //
   //uint8 verändern
   //
   obj->SetUInt8(19);
   b2 = 19;
   undo->close();

   // Check object
   testEquals(obj->referenceCount(), 5, "Referenzzähler muss 5 sein.");
   testEquals(undo->undoCount(), 4, "Undostack not empty. (11)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (11)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   b2 = 0;

   testEquals(undo->undoCount(), 3, "Undostack not empty.(12)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(12)");

   TestRef(obj);

   //Einfügen wiederherstellen
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   b2 = 19;

   testEquals(undo->undoCount(), 4, "Undostack not empty. (13)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(13)");

   TestRef(obj);

   //
   // Mache zwei Schritte rückgängig
   //
   testTrue(undo->undo(), "Undo nicht ausgeführt (14)");
   testTrue(undo->undo(), "Undo nicht ausgeführt (15)");
   testEquals(undo->undoCount(), 2, "Undostack not empty. (8)");
   testEquals(undo->redoCount(), 2, "Redostack not empty. (8)");
   b2 = 0;
   b1 = 0;
   TestRef(obj);
   testTrue(undo->redo(), "Redo nicht ausgeführt (14)");
   testTrue(undo->redo(), "Redo nicht ausgeführt (15)");
   testEquals(undo->undoCount(), 4, "Undostack not empty. (8)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (8)");
   b1 = 17;
   b2 = 19;
   TestRef(obj);
   testEquals(obj->referenceCount(), 5, "Referenzzähler muss 5 sein.");

   //
   //int16 verändern
   //
   obj->SetInt16(-33);
   s1 = -33;
   undo->close();

   // Check object
   testEquals(obj->referenceCount(), 6, "Referenzzähler muss 6 sein.");
   testEquals(undo->undoCount(), 5, "Undostack not empty. (8)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (8)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   s1 = 0;

   testEquals(undo->undoCount(), 4, "Undostack not empty.(9)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(9)");

   TestRef(obj);

   //Einfügen wiederherstellen
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   s1 = -33;

   testEquals(undo->undoCount(), 5, "Undostack not empty. (10)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(10)");

   TestRef(obj);

   //
   //uint16 verändern
   //
   obj->SetUInt16(99);
   s2 = 99;
   undo->close();

   // Check object
   testEquals(obj->referenceCount(), 7, "Referenzzähler muss 7 sein.");
   testEquals(undo->undoCount(), 6, "Undostack not empty. (11)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (11)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   s2 = 0;

   testEquals(undo->undoCount(), 5, "Undostack not empty.(12)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(12)");

   TestRef(obj);

   //Einfügen wiederherstellen
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   s2 = 99;

   testEquals(undo->undoCount(), 6, "Undostack not empty. (13)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(13)");

   TestRef(obj);

   //
   //int32 verändern
   //
   obj->SetInt32(-342);
   i1 = -342;
   undo->close();

   // Check object
   testEquals(obj->referenceCount(), 8, "Referenzzähler muss 8 sein.");
   testEquals(undo->undoCount(), 7, "Undostack not empty. (8)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (8)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   i1 = 0;

   testEquals(undo->undoCount(), 6, "Undostack not empty.(9)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(9)");

   TestRef(obj);

   //Einfügen wiederherstellen
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   i1 = -342;

   testEquals(undo->undoCount(), 7, "Undostack not empty. (10)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(10)");

   TestRef(obj);

   //
   //uint32 verändern
   //
   obj->SetUInt32(992);
   i2 = 992;
   undo->close();

   // Check object
   testEquals(obj->referenceCount(), 9, "Referenzzähler muss 9 sein.");
   testEquals(undo->undoCount(), 8, "Undostack not empty. (11)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (11)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   i2 = 0;

   testEquals(undo->undoCount(), 7, "Undostack not empty.(12)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(12)");

   TestRef(obj);

   //Einfügen wiederherstellen
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   i2 = 992;

   testEquals(undo->undoCount(), 8, "Undostack not empty. (13)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(13)");

   TestRef(obj);

   //
   //int64 verändern
   //
   obj->SetInt64(-3425);
   l1 = -3425;
   undo->close();

   // Check object
   testEquals(obj->referenceCount(), 10, "Referenzzähler muss 10 sein.");
   testEquals(undo->undoCount(), 9, "Undostack not empty. (8)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (8)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   l1 = 0;

   testEquals(undo->undoCount(), 8, "Undostack not empty.(9)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(9)");

   TestRef(obj);

   //Einfügen wiederherstellen
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   l1 = -3425;

   testEquals(undo->undoCount(), 9, "Undostack not empty. (10)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(10)");

   TestRef(obj);

   //
   //uint64 verändern
   //
   obj->SetUInt64(5992);
   l2 = 5992;
   undo->close();

   // Check object
   testEquals(obj->referenceCount(), 11, "Referenzzähler muss 11 sein.");
   testEquals(undo->undoCount(), 10, "Undostack not empty. (11)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (11)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   l2 = 0;

   testEquals(undo->undoCount(), 9, "Undostack not empty.(12)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(12)");

   TestRef(obj);

   //Einfügen wiederherstellen
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   l2 = 5992;

   testEquals(undo->undoCount(), 10, "Undostack not empty. (13)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(13)");

   TestRef(obj);

   //
   //float verändern
   //
   obj->SetFloat(1.42f);
   f = 1.42f;
   undo->close();

   // Check object
   testEquals(obj->referenceCount(), 12, "Referenzzähler muss 12 sein.");
   testEquals(undo->undoCount(), 11, "Undostack not empty. (11)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (11)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   f = 0;

   testEquals(undo->undoCount(), 10, "Undostack not empty.(12)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(12)");

   TestRef(obj);

   //Einfügen wiederherstellen
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   f = 1.42f;

   testEquals(undo->undoCount(), 11, "Undostack not empty. (13)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(13)");

   TestRef(obj);


   //
   // change object
   //

   // o2 => ref count = 1 :
   // +1 object creation
   UndoTestObject* o2 = new UndoTestObject();
   testEquals(o2->referenceCount(), 1, "Reference Counter must be 1. (a)");

   // o2 => ref count + 2 = 3 :
   // +1 setObject
   // +1 undo register release
   obj->SetObject(o2);
   o = o2;
   undo->close();

   testEquals(o2->referenceCount(), 3, "Reference Counter must be 3. (b)");

   // Check object
   testEquals(obj->referenceCount(), 13, "Reference Counter must be 13.");
   testEquals(undo->undoCount(), 12, "Undostack not empty. (14)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (14)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   // o2 => ref count = 3 :
   // -1 UndoObjectRelease
   // +1 UndoChangeObjectRef (value2)
   testTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   o = nullptr;

   testEquals(o2->referenceCount(), 3, "Reference Counter must be 3. (c)");

   testEquals(undo->undoCount(), 11, "Undostack not empty.(15)");
   testEquals(undo->redoCount(), 1, "Redostack not empty.(15)");

   TestRef(obj);

   //Einfügen wiederherstellen
   // o2 => ref count +1 = 4 :
   // +1 UndoObjectRelease
   testTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   o = o2;

   testEquals(o2->referenceCount(), 4, "Reference Counter must be 4. (d)");

   testEquals(undo->undoCount(), 12, "Undostack not empty. (16)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(16)");

   TestRef(obj);

   //
   // Noch mal undo/redo -> Zähler sollten gleich bleiben
   //
   //

   // o2 => ref count -1 = 3 :
   // -1 UndoObjectRelease
   testTrue(undo->undo(), "Undo nicht ausgeführt (5)");
   testEquals(o2->referenceCount(), 3, "Reference Counter must be 3. (c)");

   // o2 => ref count +1 = 4 :
   // +1 UndoObjectRelease
   testTrue(undo->redo(), "Redo nicht ausgeführt. (6)");
   testEquals(o2->referenceCount(), 4, "Reference Counter must be 4. (d)");

   testEquals(undo->undoCount(), 12, "Undostack not empty. (16)");
   testEquals(undo->redoCount(), 0, "Redostack not empty.v(16)");

   TestRef(obj);


   //
   // END
   //

   // Clear stacks at the end
   testEquals(obj->referenceCount(), 13, "Referenzzähler muss 12 sein.");
   undo->clearStacks();

   testEquals(obj->referenceCount(), 1, "Referenzzähler muss 1 sein.");
   testEquals(o2->referenceCount(), 2, "Obj-Referenzzähler muss 2 sein. (e)");

   testEquals(undo->undoCount(), 0, "Undostack not empty. (X)");
   testEquals(undo->redoCount(), 0, "Redostack not empty. (X)");

   undo->release();
   testEquals(obj->referenceCount(), 1, "Referenzzähler muss 1 sein.");
   obj->release();
   testEquals(o2->referenceCount(), 1, "Obj-Referenzzähler muss 1 sein. (e)");
   o2->release();
}
