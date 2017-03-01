#pragma once
#include "Main.hpp"

#include <Windows.h>

#include "Utils/Console.hpp"
#include "Utils/Memory.hpp"
#include "Utils/Thread.hpp"

#include "Cheats/bhop.hpp"

int main(int argc, char** argv)
{
	if (!setup())
		return 1;

	threadManager->create("bhop", bhop);
	while (GetAsyncKeyState(VK_F9))
		Sleep(100);

	cleanup();
	return 1;
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