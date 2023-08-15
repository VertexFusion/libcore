//
//  Object.cpp
//  Jameo
//
//  Created by Uwe Runtemund on 20.04.2014.
//  Copyright (c) 2014 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

Object::Object()
{
	mRefCount = 1;
	mPool = System::GetAutoreleasePool();
	//Zombie finden
	//mRefCount=2;
}

Object::~Object()
{
	mPool = NULL;
}

void Object::Release()
{
	if(mPool == NULL)return;  //Sicherheit

	uint32 count;
	Mutex* mutex = mPool->GetMutex();

	mutex->Lock();
	mRefCount--;
	count = mRefCount;
	mutex->Unlock();

	if(count == 0)
	{
		//Zombie finden
		//std::cout<<"Zombie delete"<<std::endl;
		delete this;//Wenn Refcount=0 ist, darf Release oder Retain logischer Weise nicht nochmals aufgerufen werden.
	}
}

Object* Object::Retain()
{
	Mutex* mutex = mPool->GetMutex();
	mutex->Lock();
	mRefCount++;
	mutex->Unlock();
	return this;
}

Object* Object::Autorelease()
{
	mPool->AddObject(this);
	return this;
}

uint32 Object::GetReferenceCount() const
{
	return mRefCount;
}

bool Object::Equals(const Object* other) const
{
	return false;
}

int8* Object::GetDiffName() const
{
	return "Object";
}

void Object::PrintDiffInfo(DiffOperation operation, Object* other) const
{
	//Tue hier nichts
}
