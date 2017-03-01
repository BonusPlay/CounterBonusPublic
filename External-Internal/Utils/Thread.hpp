#pragma once
#ifndef THREAD_H
#define THREAD_H

#include <string.h>
#include <Windows.h>
#include <vector>

struct Thread
{
	Thread(char* cname, HANDLE chandle, void* fPtr)
	{
		strcpy_s(name, cname);
		threadHandle = chandle;
		funcPtr = fPtr;
	}

	char name[64];
	HANDLE threadHandle;
	void* funcPtr;
};

class ThreadManager
{
public:
	ThreadManager();
	ThreadManager(ThreadManager&) = delete;
	~ThreadManager();

	bool create(char* threadName, void* funcPtr);
	bool end(char* threadName);
	void endAll();

private:
	std::vector<Thread> threadList;
};

extern ThreadManager* threadManager;

#endif // THREAD_H