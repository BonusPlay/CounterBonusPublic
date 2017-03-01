#pragma once

#include "Thread.hpp"
#include "Console.hpp"

#pragma region Singleton

ThreadManager* threadManager;

ThreadManager::ThreadManager()
{
	console->DebugMessage("Thread Manager starting up");
}

ThreadManager::~ThreadManager()
{
	console->DebugMessage("Thread Manager shutting down");
}

#pragma endregion

bool ThreadManager::create(char* threadName, void* funcPtr)
{
	HANDLE newThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)funcPtr, 0, 0, 0);
	if (!newThread)
	{
		console->ErrorMessage("Could not create thread %s", threadName);
		return false;
	}
	console->Message("Created thread %s", threadName);
	threadList.push_back(Thread(threadName, newThread, funcPtr));
	return true;
}

bool ThreadManager::end(char* threadName)
{
	for (auto m : threadList)
	{
		if (!_stricmp(threadName, m.name))
		{
			if (TerminateThread(m.threadHandle, 0))
			{
				console->Message("Ended thread %s", m.name);
				return true;
			}
			else
			{
				console->ErrorMessage("Could not end thread %s", m.name);
				return false;
			}
		}
	}
}

void ThreadManager::endAll()
{
	for (auto m : threadList)
		end(m.name);
}