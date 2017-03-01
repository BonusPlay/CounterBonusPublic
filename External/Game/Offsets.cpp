#pragma once
#include "Offsets.hpp"
#include "../Utils/Console.hpp"

#pragma region Singleton

Offsets* offsets;

Offsets::Offsets()
{
	console->DebugMessage("Console starting up");

	DWORD start;
	DWORD p1;
	DWORD p2;

	start = memory->FindSignature(memory->GetClientBase(), memory->GetClientSize(), Patterns::pt_dwLocalPlayer, Masks::msk_dwLocalPlayer);
	p1 = memory->Read<DWORD>(start + 0x3);
	p2 = memory->Read<BYTE>(start + 0x12);
	m_dwLocalPlayer = (p1 + p2) - memory->GetClientBase();

	start = memory->FindSignature(memory->GetClientBase(), memory->GetClientSize(), Patterns::pt_dwForceJump, Masks::msk_dwForceJump);
	m_dwForceJump = memory->Read<DWORD>(start + 0x2) - memory->GetClientBase();
}

Offsets::~Offsets()
{
	console->DebugMessage("Console shutting down");
}

#pragma endregion

namespace Patterns
{
	BYTE pt_dwLocalPlayer[] = { 0x8D, 0x34, 0x85, 0x00, 0x00, 0x00, 0x00, 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x41, 0x08, 0x8B, 0x48, 0x00 };
	//BYTE pt_dwForceJump[] = { 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, 0xF6, 0xC2, 0x03, 0x74, 0x03, 0x83, 0xCE, 0x08, 0xA8, 0x08, 0xBF };
	BYTE pt_dwForceJump[] = { 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, 0xF6, 0xC2, 0x03, 0x74, 0x03, 0x83, 0xCE, 0x08 };
}

namespace Masks
{
	char* msk_dwLocalPlayer = "xxx????xx????xxxxx?";
	//char* msk_dwForceJump = "xx????xx????xxxxxxxxxxxx";
	char* msk_dwForceJump = "xx????xx????xxxxxxxx";
}