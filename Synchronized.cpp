//
//  Synchronized.cpp
//  jameo
//
//  Created by  Uwe Runtemund on 07.12.12.
//  Copyright (c) 2012 Jameo Software. All rights reserved.
//

#include "Precompiled.h"

using namespace jm;

Mutex::Mutex()
{
	#if defined(__APPLE__) || defined(__linux__)   //macOS & Linux
	pthread_condattr_init(&attrc);
	pthread_cond_init(&cond, &attrc);
	pthread_mutexattr_init(&attr);
	pthread_mutex_init(&criticalSection, &attr);

	#elif defined _WIN32//Windows
	InitializeCriticalSection((CRITICAL_SECTION*)&mCriticalSection);
	#endif
}

Mutex::~Mutex()
{
	#if defined _WIN32//Windows
	CRITICAL_SECTION* ptr = (CRITICAL_SECTION*)&mCriticalSection;
	DeleteCriticalSection(ptr);
	#endif
}

void Mutex::Lock()
{
	#if defined(__APPLE__) || defined(__linux__)   //macOS & Linux
	pthread_mutex_lock(&criticalSection);
	#elif defined _WIN32//Windows

	EnterCriticalSection((CRITICAL_SECTION*)&mCriticalSection);

	#endif
}

void Mutex::Unlock()
{
	#if defined(__APPLE__) || defined(__linux__)   //macOS & Linux
	pthread_mutex_unlock(&criticalSection);

	#elif defined _WIN32//Windows

	LeaveCriticalSection((CRITICAL_SECTION*)&mCriticalSection);

	#endif
}

void Mutex::Sleep()
{
	#if defined(__APPLE__) || defined(__linux__)   //macOS & Linux
	pthread_mutex_lock(&criticalSection);
	pthread_cond_wait(&cond, &criticalSection);
	pthread_mutex_unlock(&criticalSection);

	#elif defined _WIN32//Windows

	throw new jm::Exception("jm::Mutex::Sleep() Not implemented");

	exit(24);
	#endif
}

void Mutex::WakeUp()
{
	#if defined(__APPLE__) || defined(__linux__)   //macOS & Linux
	pthread_cond_signal(&cond);

	#elif defined _WIN32//Windows

	throw new jm::Exception("jm::Mutex::WakeUp() Not implemented");

	exit(24);

	#endif
}

Lock::Lock(Mutex &_mutex) : mutex(_mutex), locked(true)
{
	_mutex.Lock();
}

Lock::~Lock()
{
	mutex.Unlock();
}

void Lock::SetUnlock()
{
	locked = false;
}

