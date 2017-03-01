#pragma once
#include "bhop.hpp"

#include "../Utils/Console.hpp"
#include "../Utils/Memory.hpp"
#include "../Game/Offsets.hpp"
#include <thread>

bool isAir()
{
	int flags = memory->Read<int>(offsets->getLocalPlayer() + 0x100) == 256;
	return flags == 256 || flags == 258 || flags == 260 || flags == 262;
}

void bhop()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (!isAir())
			{
				memory->Write<DWORD>(memory->GetClientBase() + offsets->getForceJump(), 5);
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				memory->Write<DWORD>(memory->GetClientBase() + offsets->getForceJump(), 4);
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}