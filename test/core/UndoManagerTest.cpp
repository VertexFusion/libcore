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

//Referenzwerte
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
   TestEquals(obj->str, str, "str falsch.");
   TestEquals(obj->b1, b1, "b1 falsch.");
   TestEquals(obj->b2, b2, "b2 falsch.");
   TestEquals(obj->s1, s1, "s1 falsch.");
   TestEquals(obj->s2, s2, "s2 falsch.");
   TestEquals(obj->i1, i1, "i1 falsch.");
   TestEquals(obj->i2, i2, "i2 falsch.");
   TestEquals(obj->l1, l1, "l1 falsch.");
   TestEquals(obj->l2, l2, "l2 falsch.");
   TestEquals(obj->f, f, "f falsch.");
   TestEquals(obj->d, d, "d falsch.");
   TestEquals(obj->obj, o, "obj falsch.");
}


UndoManagerTest::UndoManagerTest(): Test()
{
   SetName("Test Undo Manager");
}

void UndoManagerTest::DoTest()
{
   UndoManager* undo = new UndoManager();
   undo->setActive(true);

   UndoTestObject* obj = new UndoTestObject();
   obj->undo = undo;

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 1, "Reference Counter must be 1.");
   TestEquals(undo->undoCount(), 0, "Undostack not empty. (1)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (1)");

   TestRef(obj);

   //
   //String verändern
   //
   obj->SetStr("Hallo Welt");//Hier wird der Ref-Zähler erhöht, weil ein undo-Step erzeugt wird
   str = "Hallo Welt";
   undo->close();

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 2, "Referenzzähler muss 2 sein.");
   TestEquals(undo->undoCount(), 1, "Undostack not empty. (2)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (2)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   str = jm::kEmptyString;

   TestEquals(obj->referenceCount(), 2,
              "Referenzzähler muss 2 sein.");//Undo ändert nichts am Referenzzähler...
   TestEquals(undo->undoCount(), 0, "Undostack not empty.(3)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(3)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   str = "Hallo Welt";

   TestEquals(obj->referenceCount(), 2,
              "Referenzzähler muss 2 sein.");//Redo ändert nichts am Referenzzähler...
   TestEquals(undo->undoCount(), 1, "Undostack not empty. (4)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(4)");

   TestRef(obj);

   //
   //double verändern
   //
   obj->SetDouble(24.08);
   d = 24.08;
   undo->close();

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 3, "Referenzzähler muss 3 sein.");
   TestEquals(undo->undoCount(), 2, "Undostack not empty. (5)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (5)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   d = 0;

   TestEquals(obj->referenceCount(), 3,
              "Referenzzähler muss 3 sein.");//Undo ändert nichts am Referenzzähler...
   TestEquals(undo->undoCount(), 1, "Undostack not empty.(6)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(6)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   d = 24.08;

   TestEquals(obj->referenceCount(), 3,
              "Referenzzähler muss 3 sein.");//Redo ändert nichts am Referenzzähler...
   TestEquals(undo->undoCount(), 2, "Undostack not empty. (7)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(7)");

   TestRef(obj);

   //
   //int8 verändern
   //
   obj->SetInt8(17);
   b1 = 17;
   undo->close();

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 4, "Referenzzähler muss 4 sein.");
   TestEquals(undo->undoCount(), 3, "Undostack not empty. (8)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (8)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   b1 = 0;

   TestEquals(obj->referenceCount(), 4,
              "Referenzzähler muss 4 sein.");//Undo ändert nichts am Referenzzähler...
   TestEquals(undo->undoCount(), 2, "Undostack not empty.(9)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(9)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   b1 = 17;

   TestEquals(obj->referenceCount(), 4,
              "Referenzzähler muss 4 sein.");//Redo ändert nichts am Referenzzähler...
   TestEquals(undo->undoCount(), 3, "Undostack not empty. (10)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(10)");

   TestRef(obj);

   //
   //uint8 verändern
   //
   obj->SetUInt8(19);
   b2 = 19;
   undo->close();

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 5, "Referenzzähler muss 5 sein.");
   TestEquals(undo->undoCount(), 4, "Undostack not empty. (11)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (11)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   b2 = 0;

   TestEquals(undo->undoCount(), 3, "Undostack not empty.(12)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(12)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   b2 = 19;

   TestEquals(undo->undoCount(), 4, "Undostack not empty. (13)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(13)");

   TestRef(obj);

   //
   // Mache zwei Schritte rückgängig
   //
   TestTrue(undo->undo(), "Undo nicht ausgeführt (14)");
   TestTrue(undo->undo(), "Undo nicht ausgeführt (15)");
   TestEquals(undo->undoCount(), 2, "Undostack not empty. (8)");
   TestEquals(undo->redoCount(), 2, "Redostack not empty. (8)");
   b2 = 0;
   b1 = 0;
   TestRef(obj);
   TestTrue(undo->redo(), "Redo nicht ausgeführt (14)");
   TestTrue(undo->redo(), "Redo nicht ausgeführt (15)");
   TestEquals(undo->undoCount(), 4, "Undostack not empty. (8)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (8)");
   b1 = 17;
   b2 = 19;
   TestRef(obj);
   TestEquals(obj->referenceCount(), 5, "Referenzzähler muss 5 sein.");

   //
   //int16 verändern
   //
   obj->SetInt16(-33);
   s1 = -33;
   undo->close();

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 6, "Referenzzähler muss 6 sein.");
   TestEquals(undo->undoCount(), 5, "Undostack not empty. (8)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (8)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   s1 = 0;

   TestEquals(undo->undoCount(), 4, "Undostack not empty.(9)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(9)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   s1 = -33;

   TestEquals(undo->undoCount(), 5, "Undostack not empty. (10)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(10)");

   TestRef(obj);

   //
   //uint16 verändern
   //
   obj->SetUInt16(99);
   s2 = 99;
   undo->close();

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 7, "Referenzzähler muss 7 sein.");
   TestEquals(undo->undoCount(), 6, "Undostack not empty. (11)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (11)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   s2 = 0;

   TestEquals(undo->undoCount(), 5, "Undostack not empty.(12)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(12)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   s2 = 99;

   TestEquals(undo->undoCount(), 6, "Undostack not empty. (13)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(13)");

   TestRef(obj);

   //
   //int32 verändern
   //
   obj->SetInt32(-342);
   i1 = -342;
   undo->close();

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 8, "Referenzzähler muss 8 sein.");
   TestEquals(undo->undoCount(), 7, "Undostack not empty. (8)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (8)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   i1 = 0;

   TestEquals(undo->undoCount(), 6, "Undostack not empty.(9)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(9)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   i1 = -342;

   TestEquals(undo->undoCount(), 7, "Undostack not empty. (10)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(10)");

   TestRef(obj);

   //
   //uint32 verändern
   //
   obj->SetUInt32(992);
   i2 = 992;
   undo->close();

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 9, "Referenzzähler muss 9 sein.");
   TestEquals(undo->undoCount(), 8, "Undostack not empty. (11)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (11)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   i2 = 0;

   TestEquals(undo->undoCount(), 7, "Undostack not empty.(12)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(12)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   i2 = 992;

   TestEquals(undo->undoCount(), 8, "Undostack not empty. (13)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(13)");

   TestRef(obj);

   //
   //int64 verändern
   //
   obj->SetInt64(-3425);
   l1 = -3425;
   undo->close();

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 10, "Referenzzähler muss 10 sein.");
   TestEquals(undo->undoCount(), 9, "Undostack not empty. (8)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (8)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   l1 = 0;

   TestEquals(undo->undoCount(), 8, "Undostack not empty.(9)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(9)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   l1 = -3425;

   TestEquals(undo->undoCount(), 9, "Undostack not empty. (10)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(10)");

   TestRef(obj);

   //
   //uint64 verändern
   //
   obj->SetUInt64(5992);
   l2 = 5992;
   undo->close();

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 11, "Referenzzähler muss 11 sein.");
   TestEquals(undo->undoCount(), 10, "Undostack not empty. (11)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (11)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   l2 = 0;

   TestEquals(undo->undoCount(), 9, "Undostack not empty.(12)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(12)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   l2 = 5992;

   TestEquals(undo->undoCount(), 10, "Undostack not empty. (13)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(13)");

   TestRef(obj);

   //
   //float verändern
   //
   obj->SetFloat(1.42f);
   f = 1.42f;
   undo->close();

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 12, "Referenzzähler muss 12 sein.");
   TestEquals(undo->undoCount(), 11, "Undostack not empty. (11)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (11)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   f = 0;

   TestEquals(undo->undoCount(), 10, "Undostack not empty.(12)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(12)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   f = 1.42f;

   TestEquals(undo->undoCount(), 11, "Undostack not empty. (13)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(13)");

   TestRef(obj);


   //
   //Object verändern
   //
   UndoTestObject* o2 = new UndoTestObject();
   TestEquals(o2->referenceCount(), 1, "Obj-Referenzzähler muss 1 sein. (a)");

   obj->SetObject(o2);
   o = o2;
   undo->close();

   //+1 Zähler für obj
   //+1 Zähler für Undo/retain
   TestEquals(o2->referenceCount(), 3, "Obj-Referenzzähler muss 3 sein. (b)");

   //Objekt prüfen
   TestEquals(obj->referenceCount(), 13, "Referenzzähler muss 13 sein.");
   TestEquals(undo->undoCount(), 12, "Undostack not empty. (14)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (14)");

   TestRef(obj);

   //Einfügen Rückgängig machen
   TestTrue(undo->undo(), "Undo nicht ausgeführt (3)");
   o = nullptr;

   //-1 Zähler für obj
   //(+1 Zähler für UndoManager) NEIN AKTUELL NICHT (2023-11-05) WAR 3
   //= Zähler bleibt gleich
   TestEquals(o2->referenceCount(), 2, "Obj-Referenzzähler muss 2 sein. (c)");

   TestEquals(undo->undoCount(), 11, "Undostack not empty.(15)");
   TestEquals(undo->redoCount(), 1, "Redostack not empty.(15)");

   TestRef(obj);

   //Einfügen wiederherstellen
   TestTrue(undo->redo(), "Redo nicht ausgeführt. (4)");
   o = o2;

   //+1 Zähler für obj
   //-1 Zähler für UndoManager
   //= Zähler bleibt gleich
   TestEquals(o2->referenceCount(), 3, "Obj-Referenzzähler muss 3 sein. (d)");

   TestEquals(undo->undoCount(), 12, "Undostack not empty. (16)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty.v(16)");

   TestRef(obj);


   //
   // ENDE
   //

   //Am Ende Stacks leeren
   TestEquals(obj->referenceCount(), 13, "Referenzzähler muss 12 sein.");
   undo->clearStacks();

   TestEquals(obj->referenceCount(), 1, "Referenzzähler muss 1 sein.");
   TestEquals(o2->referenceCount(), 2, "Obj-Referenzzähler muss 2 sein. (e)");

   TestEquals(undo->undoCount(), 0, "Undostack not empty. (X)");
   TestEquals(undo->redoCount(), 0, "Redostack not empty. (X)");

   undo->release();
   TestEquals(obj->referenceCount(), 1, "Referenzzähler muss 1 sein.");
   obj->release();
   TestEquals(o2->referenceCount(), 1, "Obj-Referenzzähler muss 1 sein. (e)");
   o2->release();
}
