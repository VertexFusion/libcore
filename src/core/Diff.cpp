//
//  main.cpp
//  test
//
//  Created by Uwe Runtemund on 12.11.13.
//  Copyright (c) 2013 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

using std::cout;
using std::endl;

void Diff::HandleEntityU(DiffDistance* dd, DwgEntity* e)
{
	if(e->GetObjectType() ==  kDwgTypePOLYLINE_3D)
	{
		DwgPolyline* pl = static_cast<DwgPolyline*>(e);
		dd->AddU(pl);

		for(int a = 0; a < pl->GetVertexCount(); a++)dd->AddU(pl->GetVertex(a));
	}
	else if(e->GetObjectType() == kDwgTypeINSERT)
	{
		DwgInsert* i = static_cast<DwgInsert*>(e);
		dd->AddU(i);

		for(int a = 0; a < i->GetAttributeCount(); a++)dd->AddU(i->GetAttribute(a));
	}
	else dd->AddU(e);
}

void Diff::HandleEntityV(DiffDistance* dd, DwgEntity* e)
{
	if(e->GetObjectType() == kDwgTypePOLYLINE_3D)
	{
		DwgPolyline* pl = static_cast<DwgPolyline*>(e);
		dd->AddV(pl);

		for(int a = 0; a < pl->GetVertexCount(); a++)dd->AddV(pl->GetVertex(a));
	}
	else if(e->GetObjectType() == kDwgTypeINSERT)
	{
		DwgInsert* i = static_cast<DwgInsert*>(e);
		dd->AddV(i);

		for(int a = 0; a < i->GetAttributeCount(); a++)dd->AddV(i->GetAttribute(a));
	}
	else dd->AddV(e);
}

uint32 Diff::MakeDiff(dwg::Drawing* c1, dwg::Drawing* c2)
{
	DiffDistance dd = DiffDistance();
	int distance = 1;
	try
	{
		//Header
		dd.AddU(c1->GetHeader());
		dd.AddV(c2->GetHeader());

		//Vergleiche Linienstile
		DwgSymbolTable* t1 = c1->GetLineTypeTable();
		DwgSymbolTable* t2 = c2->GetLineTypeTable();
		LinkedListIterator li = t1->GetIterator();
		while(li.HasNext())dd.AddU(li.Next());
		li = t2->GetIterator();
		while(li.HasNext())dd.AddV(li.Next());

		//Vergleiche Layer
		t1 = c1->GetLayerTable();
		t2 = c2->GetLayerTable();
		li = t1->GetIterator();
		while(li.HasNext())dd.AddU(li.Next());
		li = t2->GetIterator();
		while(li.HasNext())dd.AddV(li.Next());

		//Vergleiche Blockrecords
		t1 = c1->GetBlockRecordTable();
		t2 = c2->GetBlockRecordTable();
		li = t1->GetIterator();
		while(li.HasNext())dd.AddU(li.Next());
		li = t2->GetIterator();
		while(li.HasNext())dd.AddV(li.Next());

		//Vergleiche Styles
		t1 = c1->GetStyleTable();
		t2 = c2->GetStyleTable();
		li = t1->GetIterator();
		while(li.HasNext())dd.AddU(li.Next());
		li = t2->GetIterator();
		while(li.HasNext())dd.AddV(li.Next());

		//Vergleiche AppIDs
		t1 = c1->GetAPPIDTable();
		t2 = c2->GetAPPIDTable();
		li = t1->GetIterator();
		while(li.HasNext())dd.AddU(li.Next());
		li = t2->GetIterator();
		while(li.HasNext())dd.AddV(li.Next());

		//Vergleiche Dimstyles
		t1 = c1->GetDimStyleTable();
		t2 = c2->GetDimStyleTable();
		li = t1->GetIterator();
		while(li.HasNext())dd.AddU(li.Next());
		li = t2->GetIterator();
		while(li.HasNext())dd.AddV(li.Next());

		//Vergleiche VPorts
		t1 = c1->GetVPortTable();
		t2 = c2->GetVPortTable();
		li = t1->GetIterator();
		while(li.HasNext())dd.AddU(li.Next());
		li = t2->GetIterator();
		while(li.HasNext())dd.AddV(li.Next());

		//Vergleiche Views
		t1 = c1->GetViewTable();
		t2 = c2->GetViewTable();
		li = t1->GetIterator();
		while(li.HasNext())dd.AddU(li.Next());
		li = t2->GetIterator();
		while(li.HasNext())dd.AddV(li.Next());

		//Vergleiche UCS
		t1 = c1->GetUCSTable();
		t2 = c2->GetUCSTable();
		li = t1->GetIterator();
		while(li.HasNext())dd.AddU(li.Next());
		li = t2->GetIterator();
		while(li.HasNext())dd.AddV(li.Next());

		//Vergleiche Klassen
		li = c1->GetClassSection()->GetClassIterator();
		while(li.HasNext())dd.AddU(li.Next());
		li = c2->GetClassSection()->GetClassIterator();
		while(li.HasNext())dd.AddV(li.Next());

		//Vergleiche Blockobjekte.
		li = c1->GetBlockSection()->GetBlockIterator();
		while(li.HasNext())
		{
			DwgBlock* b = static_cast<DwgBlock*>(li.Next());
			dd.AddU(b);
			LinkedListIterator bi = b->GetEntityIterator();
			while(bi.HasNext())HandleEntityU(&dd, static_cast<DwgEntity*>(bi.Next()));
		}
		li = c2->GetBlockSection()->GetBlockIterator();
		while(li.HasNext())
		{
			DwgBlock* b = static_cast<DwgBlock*>(li.Next());
			dd.AddV(b);
			LinkedListIterator bi = b->GetEntityIterator();
			while(bi.HasNext())HandleEntityV(&dd, static_cast<DwgEntity*>(bi.Next()));
		}

/*
		//Vergleiche Entitäten
		DwgEntity* ent = c1->GetFirstEntity();
		while(ent != NULL)
		{
			HandleEntityU(&dd, ent);
			ent = ent->next;
		}
		ent = c2->GetEntitySection()->GetFirstEntity();
		while(ent != NULL)
		{
			HandleEntityV(&dd, ent);
			ent = ent->next;
		}*/

		//Vergleiche Objekte
		Iterator* it = c1->GetIterator();
		while(it->HasNext())dd.AddU(it->Next());
		delete it;
		it = c2->GetIterator();
		while(it->HasNext())dd.AddV(it->Next());
		delete it;

		//Löse DIFF
		DiffBacktrace* db = dd.Solve();
		distance = dd.GetDistance();
		db->Print();
		delete db;

		dd.Clear();
	}
	catch(Exception* e)
	{
		e->PrintStackTrace();
		delete e;
		std::cout << Tr("An Error occured during DIFF.") << std::endl;
	}

	return distance;
}
