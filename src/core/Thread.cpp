////////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        Thread.cpp
// Library:     Jameo Core Library
// Purpose:     Thread
//
// Author:      Uwe Runtemund (2013-today)
// Modified by:
// Created:     30.05.2013
//
// Copyright:   (c) 2013 Jameo Software, Germany. https://jameo.de
//
// Licence:     The MIT License
//              Permission is hereby granted, free of charge, to any person obtaining a copy of this
//              software and associated documentation files (the "Software"), to deal in the
//              Software without restriction, including without limitation the rights to use, copy,
//              modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//              and to permit persons to whom the Software is furnished to do so, subject to the
//              following conditions:
//
//              The above copyright notice and this permission notice shall be included in all
//              copies or substantial portions of the Software.
//
//              THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//              INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//              PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//              HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
//              CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
//              OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Precompiled.h"

using namespace jm;

#if defined __APPLE__ || defined __linux__

void* StartThread(void* arg)
{
	Thread* t = (Thread*)arg;

	pthread_mutex_lock(&t->criticalSection);
	t->alive = true;
	pthread_mutex_unlock(&t->criticalSection);

	t->Run();
	pthread_exit(NULL);
	return NULL;
}

#elif defined _WIN32

DWORD WINAPI StartThread(LPVOID lpParameter)
{
	Thread* t = (Thread*)lpParameter;

	EnterCriticalSection((CRITICAL_SECTION*)t->mCriticalSection);
	t->alive = true;
	LeaveCriticalSection((CRITICAL_SECTION*)t->mCriticalSection);

	t->Run();
	CloseHandle(t->mHandle);
	return 0;
}


#endif


Thread::Thread(): jm::Object()
{
	#if defined __APPLE__ || defined __linux__
	thread = 0;
	alive = false;
	pthread_condattr_init(&attrc);
	pthread_cond_init(&cond, &attrc);

	pthread_mutexattr_init(&attra);
	pthread_mutex_init(&criticalSection, &attra);
	#elif defined _WIN32
	mCriticalSection = new CRITICAL_SECTION;
	InitializeCriticalSection((CRITICAL_SECTION*)mCriticalSection);
	#endif
}


Thread::~Thread()
{
	#if defined _WIN32//Windows
	DeleteCriticalSection((CRITICAL_SECTION*)mCriticalSection);
	delete((CRITICAL_SECTION*)mCriticalSection);
	#endif
}

void Thread::Start()
{
	#if defined __APPLE__ || defined __linux__
	void* arg = (void*)this;

	int ret = pthread_create(&thread, NULL, StartThread, arg);
	if(ret != 0)throw new Exception("Error on starting Thread");
	#elif defined _WIN32
	void* arg = (void*)this;
	mHandle = CreateThread(0, 0, StartThread, arg, 0, &mThreadID);
	if(mHandle == NULL)throw new Exception("Error on starting Thread");

	#endif
}


void Thread::Sleep(int millis)
{
	#if defined __APPLE__ || defined __linux__
	timespec   ts;
	timeval    now;
	gettimeofday(&now, NULL);

	//Konversion machen, damit es keinen overflow gibt, der dann in einer falschen Zeit resultiert.
	uint64 m = millis;

	/* Convert from timeval to timespec */
	ts.tv_sec = now.tv_sec;
	ts.tv_nsec = now.tv_usec * 1000;
	ts.tv_nsec += m * 1000000;
	ts.tv_sec += ts.tv_nsec / 1000000000L;
	ts.tv_nsec = ts.tv_nsec % 1000000000L;

	pthread_mutex_lock(&criticalSection);
	pthread_cond_timedwait(&cond, &criticalSection, &ts);
	pthread_mutex_unlock(&criticalSection);
	#elif defined _WIN32
	::Sleep(millis);
	#endif
}

void Thread::Lock()
{
	#if defined __APPLE__ || defined __linux__
	pthread_mutex_lock(&criticalSection);
	#elif defined _WIN32
	EnterCriticalSection((CRITICAL_SECTION*)mCriticalSection);
	#endif
}

void Thread::Unlock()
{
	#if defined __APPLE__ || defined __linux__
	pthread_mutex_unlock(&criticalSection);
	#elif defined _WIN32
	LeaveCriticalSection((CRITICAL_SECTION*)mCriticalSection);
	#endif
}

void Thread::Sleep()
{
	#if defined __APPLE__ || defined __linux__
	pthread_mutex_lock(&criticalSection);
	pthread_cond_wait(&cond, &criticalSection);
	pthread_mutex_unlock(&criticalSection);
	#elif defined _WIN32
	//	EnterCriticalSection((CRITICAL_SECTION*)mCriticalSection);
	SuspendThread(mHandle);
	//	LeaveCriticalSection((CRITICAL_SECTION*)mCriticalSection);
	#endif
}

void Thread::WakeUp()
{
	#if defined __APPLE__ || defined __linux__
	pthread_cond_signal(&cond);
	#elif defined _WIN32
	ResumeThread(mHandle);
	#endif
}

void Thread::Interrupt()
{
	#if defined __APPLE__ || defined __linux__
	pthread_mutex_lock(&criticalSection);
	alive = false;
	pthread_mutex_unlock(&criticalSection);
	pthread_cond_signal(&cond);
	pthread_join(thread, NULL);
	#elif defined _WIN32
	TerminateThread(mHandle, 0);
	#endif
}

bool Thread::IsAlive()
{
	#if defined __APPLE__ || defined __linux__
	bool ret;
	pthread_mutex_lock(&criticalSection);
	ret = alive;
	pthread_mutex_unlock(&criticalSection);
	return ret;
	#elif defined _WIN32
	bool ret;
	EnterCriticalSection((CRITICAL_SECTION*)mCriticalSection);
	ret = alive;
	LeaveCriticalSection((CRITICAL_SECTION*)mCriticalSection);
	return ret;
	#endif
}


void Thread::SetName(const jm::String &name)
{
#if defined __APPLE__ || defined __linux__
	int8* cstr= (int8*) name.ToCString();
	pthread_setname_np(thread,cstr);
	delete[] cstr;
#elif defined _WIN32
	uint16* cstr = name.ToWString();
	SetThreadDescription(mHandle,(PCWSTR)cstr);
	delete[] cstr;
#endif
}



bool Thread::IsMainThread()
{
	#ifdef __APPLE__
	//Nur OS X?
	return pthread_main_np() != 0;
	#elif defined __linux__
	//Linux
	return syscall(SYS_gettid) == getpid();
	#elif defined _WIN32
	return false;
	#endif
}

