//
//  UndoStep.cpp
//  jameo
//
//  Created by Uwe Runtemund on 11.02.14.
//  Copyright (c) 2014 Jameo Software. All rights reserved.
//
#include "Precompiled.h"


using namespace jm;

UndoStep::UndoStep()
{
	prev = NULL;
	recent = NULL;
	eldest = NULL;
	count = 0;
}

UndoStep::~UndoStep()
{
	UndoChange* change = recent;

	while(change != NULL)
	{
		UndoChange* victim = change;
		change = change->mPrev;
		delete victim;
	}

	prev = NULL;
	recent = NULL;
	eldest = NULL;
	count = 0;
}

void UndoStep::AddChange(UndoChange* change)
{
	//Verkette
	change->mPrev = recent;
	if(recent != NULL)recent->mNext = change;
	recent = change;

	//Setze eldest, wenn er noch nicht gesetzt wurde
	if(eldest == NULL)eldest = recent;

	count++;
}
