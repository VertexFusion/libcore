//
//  AutoreleasePool.cpp
//  jameo
//
//  Created by Uwe Runtemund on 28.11.15.
//  Copyright © 2015 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;


AutoreleasePool::AutoreleasePool(): Object()
{
	//1. Eintrag ist ein Dummy, um if-Abfragen bei AddObject zu vermeiden
	mPool = new PoolEntry();
	mPool->object = NULL;
	mPool->next = NULL;

	mTop = mPool;
}

AutoreleasePool::~AutoreleasePool()
{
	//Autorelease aufräumen
	Drain();

	//Dummy löschen
	delete mPool;
}

void AutoreleasePool::Drain()
{
	PoolEntry* pool = mPool->next;

	while(pool != NULL)
	{
		//Objekt freigeben
		pool->object->Release();

		PoolEntry* next = pool->next;
		delete pool;
		pool = next;
	}

	mTop = mPool;
	mPool->next = NULL;
}

void AutoreleasePool::AddObject(Object* object)
{
	PoolEntry* entry = new PoolEntry();
	entry->object = object;
	entry->next = NULL;
	mTop->next = entry;
	mTop = entry;
}

Mutex* AutoreleasePool::GetMutex()
{
	return &mMutex;
}
