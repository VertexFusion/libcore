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
jm::String str="";
int8 b1=0;
uint8 b2=0;
int16 s1=0;
uint16 s2=0;
int32 i1=0;
uint32 i2=0;
int64 l1=0;
uint64 l2=0;
float f=0;
double d=0;
UndoTestObject* o=NULL;

void UndoManagerTest::TestRef(UndoTestObject* obj)
{
	TestEquals(obj->str,str,"str falsch.");
	TestEquals(obj->b1,b1,"b1 falsch.");
	TestEquals(obj->b2,b2,"b2 falsch.");
	TestEquals(obj->s1,s1,"s1 falsch.");
	TestEquals(obj->s2,s2,"s2 falsch.");
	TestEquals(obj->i1,i1,"i1 falsch.");
	TestEquals(obj->i2,i2,"i2 falsch.");
	TestEquals(obj->l1,l1,"l1 falsch.");
	TestEquals(obj->l2,l2,"l2 falsch.");
	TestEquals(obj->f,f,"f falsch.");
	TestEquals(obj->d,d,"d falsch.");
	TestEquals(obj->obj,o,"obj falsch.");
}


UndoManagerTest::UndoManagerTest(bool debug):Test(debug)
{
	SetName("Test Undo Manager");
}

void UndoManagerTest::DoTest()
{
	UndoManager* undo= new UndoManager();
	undo->SetActive(true);

	UndoTestObject* obj = new UndoTestObject();
	obj->undo=undo;

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 1, "Referenzzähler muss 1 sein.");
	TestEquals(undo->GetUndoCount(),0,"Undostack not empty. (1)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (1)");

	TestRef(obj);

	//
	//String verändern
	//
	obj->SetStr("Hallo Welt");//Hier wird der Ref-Zähler erhöht, weil ein undo-Step erzeugt wird
	str="Hallo Welt";
	undo->Close();

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 2, "Referenzzähler muss 2 sein.");
	TestEquals(undo->GetUndoCount(),1,"Undostack not empty. (2)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (2)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	str="";

	TestEquals(obj->GetReferenceCount(), 2, "Referenzzähler muss 2 sein.");//Undo ändert nichts am Referenzzähler...
	TestEquals(undo->GetUndoCount(),0,"Undostack not empty.(3)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(3)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	str="Hallo Welt";

	TestEquals(obj->GetReferenceCount(), 2, "Referenzzähler muss 2 sein.");//Redo ändert nichts am Referenzzähler...
	TestEquals(undo->GetUndoCount(),1,"Undostack not empty. (4)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(4)");

	TestRef(obj);

	//
	//double verändern
	//
	obj->SetDouble(24.08);
	d=24.08;
	undo->Close();

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 3, "Referenzzähler muss 3 sein.");
	TestEquals(undo->GetUndoCount(),2,"Undostack not empty. (5)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (5)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	d=0;

	TestEquals(obj->GetReferenceCount(), 3, "Referenzzähler muss 3 sein.");//Undo ändert nichts am Referenzzähler...
	TestEquals(undo->GetUndoCount(),1,"Undostack not empty.(6)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(6)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	d=24.08;

	TestEquals(obj->GetReferenceCount(), 3, "Referenzzähler muss 3 sein.");//Redo ändert nichts am Referenzzähler...
	TestEquals(undo->GetUndoCount(),2,"Undostack not empty. (7)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(7)");

	TestRef(obj);

	//
	//int8 verändern
	//
	obj->SetInt8(17);
	b1=17;
	undo->Close();

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 4, "Referenzzähler muss 4 sein.");
	TestEquals(undo->GetUndoCount(),3,"Undostack not empty. (8)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (8)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	b1=0;

	TestEquals(obj->GetReferenceCount(), 4, "Referenzzähler muss 4 sein.");//Undo ändert nichts am Referenzzähler...
	TestEquals(undo->GetUndoCount(),2,"Undostack not empty.(9)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(9)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	b1=17;

	TestEquals(obj->GetReferenceCount(), 4, "Referenzzähler muss 4 sein.");//Redo ändert nichts am Referenzzähler...
	TestEquals(undo->GetUndoCount(),3,"Undostack not empty. (10)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(10)");

	TestRef(obj);

	//
	//uint8 verändern
	//
	obj->SetUInt8(19);
	b2=19;
	undo->Close();

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 5, "Referenzzähler muss 5 sein.");
	TestEquals(undo->GetUndoCount(),4,"Undostack not empty. (11)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (11)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	b2=0;

	TestEquals(undo->GetUndoCount(),3,"Undostack not empty.(12)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(12)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	b2=19;

	TestEquals(undo->GetUndoCount(),4,"Undostack not empty. (13)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(13)");

	TestRef(obj);

	//
	// Mache zwei Schritte rückgängig
	//
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (14)");
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (15)");
	TestEquals(undo->GetUndoCount(),2,"Undostack not empty. (8)");
	TestEquals(undo->GetRedoCount(),2,"Redostack not empty. (8)");
	b2=0;
	b1=0;
	TestRef(obj);
	TestTrue(undo->Redo(),"Redo nicht ausgeführt (14)");
	TestTrue(undo->Redo(),"Redo nicht ausgeführt (15)");
	TestEquals(undo->GetUndoCount(),4,"Undostack not empty. (8)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (8)");
	b1=17;
	b2=19;
	TestRef(obj);
	TestEquals(obj->GetReferenceCount(), 5, "Referenzzähler muss 5 sein.");

	//
	//int16 verändern
	//
	obj->SetInt16(-33);
	s1=-33;
	undo->Close();

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 6, "Referenzzähler muss 6 sein.");
	TestEquals(undo->GetUndoCount(),5,"Undostack not empty. (8)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (8)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	s1=0;

	TestEquals(undo->GetUndoCount(),4,"Undostack not empty.(9)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(9)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	s1=-33;

	TestEquals(undo->GetUndoCount(),5,"Undostack not empty. (10)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(10)");

	TestRef(obj);

	//
	//uint16 verändern
	//
	obj->SetUInt16(99);
	s2=99;
	undo->Close();

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 7, "Referenzzähler muss 7 sein.");
	TestEquals(undo->GetUndoCount(),6,"Undostack not empty. (11)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (11)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	s2=0;

	TestEquals(undo->GetUndoCount(),5,"Undostack not empty.(12)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(12)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	s2=99;

	TestEquals(undo->GetUndoCount(),6,"Undostack not empty. (13)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(13)");
	
	TestRef(obj);

	//
	//int32 verändern
	//
	obj->SetInt32(-342);
	i1=-342;
	undo->Close();

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 8, "Referenzzähler muss 8 sein.");
	TestEquals(undo->GetUndoCount(),7,"Undostack not empty. (8)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (8)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	i1=0;

	TestEquals(undo->GetUndoCount(),6,"Undostack not empty.(9)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(9)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	i1=-342;

	TestEquals(undo->GetUndoCount(),7,"Undostack not empty. (10)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(10)");

	TestRef(obj);

	//
	//uint32 verändern
	//
	obj->SetUInt32(992);
	i2=992;
	undo->Close();

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 9, "Referenzzähler muss 9 sein.");
	TestEquals(undo->GetUndoCount(),8,"Undostack not empty. (11)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (11)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	i2=0;

	TestEquals(undo->GetUndoCount(),7,"Undostack not empty.(12)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(12)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	i2=992;

	TestEquals(undo->GetUndoCount(),8,"Undostack not empty. (13)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(13)");
	
	TestRef(obj);

	//
	//int64 verändern
	//
	obj->SetInt64(-3425);
	l1=-3425;
	undo->Close();

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 10, "Referenzzähler muss 10 sein.");
	TestEquals(undo->GetUndoCount(),9,"Undostack not empty. (8)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (8)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	l1=0;

	TestEquals(undo->GetUndoCount(),8,"Undostack not empty.(9)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(9)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	l1=-3425;

	TestEquals(undo->GetUndoCount(),9,"Undostack not empty. (10)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(10)");

	TestRef(obj);

	//
	//uint64 verändern
	//
	obj->SetUInt64(5992);
	l2=5992;
	undo->Close();

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 11, "Referenzzähler muss 11 sein.");
	TestEquals(undo->GetUndoCount(),10,"Undostack not empty. (11)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (11)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	l2=0;

	TestEquals(undo->GetUndoCount(),9,"Undostack not empty.(12)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(12)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	l2=5992;

	TestEquals(undo->GetUndoCount(),10,"Undostack not empty. (13)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(13)");
	
	TestRef(obj);

	//
	//float verändern
	//
	obj->SetFloat(1.42f);
	f=1.42f;
	undo->Close();

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 12, "Referenzzähler muss 12 sein.");
	TestEquals(undo->GetUndoCount(),11,"Undostack not empty. (11)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (11)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	f=0;

	TestEquals(undo->GetUndoCount(),10,"Undostack not empty.(12)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(12)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	f=1.42f;

	TestEquals(undo->GetUndoCount(),11,"Undostack not empty. (13)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(13)");

	TestRef(obj);


	//
	//Object verändern
	//
	UndoTestObject* o2 = new UndoTestObject();
	TestEquals(o2->GetReferenceCount(), 1, "Obj-Referenzzähler muss 1 sein. (a)");

	obj->SetObject(o2);
	o=o2;
	undo->Close();

	//+1 Zähler für obj
	TestEquals(o2->GetReferenceCount(), 2, "Obj-Referenzzähler muss 3 sein. (b)");

	//Objekt prüfen
	TestEquals(obj->GetReferenceCount(), 13, "Referenzzähler muss 13 sein.");
	TestEquals(undo->GetUndoCount(),12,"Undostack not empty. (14)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (14)");

	TestRef(obj);

	//Einfügen Rückgängig machen
	TestTrue(undo->Undo(),"Undo nicht ausgeführt (3)");
	o=NULL;

	//-1 Zähler für obj
	//+1 Zähler für UndoManager
	//= Zähler bleibt gleich
	TestEquals(o2->GetReferenceCount(), 2, "Obj-Referenzzähler muss 2 sein. (c)");

	TestEquals(undo->GetUndoCount(),11,"Undostack not empty.(15)");
	TestEquals(undo->GetRedoCount(),1,"Redostack not empty.(15)");

	TestRef(obj);

	//Einfügen wiederherstellen
	TestTrue(undo->Redo(),"Redo nicht ausgeführt. (4)");
	o=o2;

	//+1 Zähler für obj
	//-1 Zähler für UndoManager
	//= Zähler bleibt gleich
	TestEquals(o2->GetReferenceCount(), 2, "Obj-Referenzzähler muss 2 sein. (d)");

	TestEquals(undo->GetUndoCount(),12,"Undostack not empty. (16)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty.v(16)");

	TestRef(obj);


	//
	// ENDE
	//

	//Am Ende Stacks leeren
	TestEquals(obj->GetReferenceCount(), 13, "Referenzzähler muss 12 sein.");
	undo->ClearStacks();

	TestEquals(obj->GetReferenceCount(), 1, "Referenzzähler muss 1 sein.");
	TestEquals(o2->GetReferenceCount(), 2, "Obj-Referenzzähler muss 2 sein. (e)");

	TestEquals(undo->GetUndoCount(),0,"Undostack not empty. (X)");
	TestEquals(undo->GetRedoCount(),0,"Redostack not empty. (X)");

	undo->Release();
	TestEquals(obj->GetReferenceCount(), 1, "Referenzzähler muss 1 sein.");
	obj->Release();
	TestEquals(o2->GetReferenceCount(), 1, "Obj-Referenzzähler muss 1 sein. (e)");
	o2->Release();
}
