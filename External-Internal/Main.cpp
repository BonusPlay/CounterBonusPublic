#pragma once
#include "Main.hpp"

#include "Utils/Console.hpp"
#include "Utils/Memory.hpp"
#include "Utils/Thread.hpp"

#include "Cheats/bhop.hpp"

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) main, NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}

	TerminateThread(main, 0);

	return TRUE;
}

void main()
{
	if (!setup())
		return;

	threadManager->create("bhop", bhop);
	while (GetAsyncKeyState(VK_F9))
		Sleep(100);

	cleanup();
}

bool setup()
{
	console = new Console();
	threadManager = new ThreadManager();
	memory = new Memory();

	memory->Attach("csgo.exe");
	memory->GetModule("client.dll");

	return true;
}

bool cleanup()
{
	threadManager->endAll();

	delete memory;
	delete threadManager;
	delete console;
	return true;
}