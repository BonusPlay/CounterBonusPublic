#pragma once
#include "Console.hpp"
#include <Windows.h>

#pragma warning(disable:4996)
#define GetArgs(from, to) va_list args; va_start(args, from); vsprintf_s(to, from, args); va_end(args);

#pragma region Singleton

Console* console;

Console::Console()
{
	DWORD consoleMode;
	HANDLE ConInput = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE ConOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleMode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(ConInput, consoleMode);
	SetConsoleCtrlHandler(CTRL_C_EVENT, TRUE);
	freopen("CON", "w", stdout);
	SetConsoleTitle(TEXT("CounterBonusPublic External"));
	SetConsoleCursor(false);
	Clear();
	this->DebugMessage("ConsoleHandler starting up");
	this->SetConsoleColor(white, black);
}

Console::~Console()
{
	this->DebugMessage("ConsoleHandler shutting down");
	FreeConsole();
}

#pragma endregion

int Console::GetWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int Console::GetHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void Console::Clear()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hStdOut;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
		return;
	cellCount = csbi.dwSize.X*csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count))
		return;

	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
		return;
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void Console::SetConsoleCursor(bool cursor)
{
	CONSOLE_CURSOR_INFO curCursorInfo;
	curCursorInfo.bVisible = cursor;
	curCursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curCursorInfo);
}

void Console::SetConsoleColor(color textColor, color bgColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

void Console::SetConsoleSize(int width, int height)
{
	HWND hConsole = GetConsoleWindow();
	RECT r;

	GetWindowRect(hConsole, &r);

	MoveWindow(hConsole, r.left, r.top, width, height, TRUE);
}

void Console::GotoXY(int x, int y)
{
	COORD CursorPosition = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void Console::Message(std::string msg)
{
	printf(msg.c_str());
	printf("\n");
}

void Console::Message(char* msg, ...)
{
	char buf[128];
	GetArgs(msg, buf);
	printf("%s\n", buf);
}

void Console::ColorMessage(color textColor, color bgColor, std::string msg)
{
	this->SetConsoleColor(textColor, bgColor);
	printf(msg.c_str());
	printf("\n");
	this->SetConsoleColor(white, black);
}

void Console::ColorMessage(color textColor, color bgColor, char* msg, ...)
{
	this->SetConsoleColor(textColor, bgColor);
	char buf[128];
	GetArgs(msg, buf);
	printf("%s\n", buf);
	this->SetConsoleColor(white, black);
}

void Console::DebugMessage(std::string msg)
{
#if DEBUG
	this->ColorMessage(purple, black, "[DEBUG] " + msg);
#endif
}

void Console::DebugMessage(char* msg, ...)
{
#if DEBUG
	this->SetConsoleColor(purple, black);
	char buf[128];
	GetArgs(msg, buf);
	printf("%s\n", buf);
	this->SetConsoleColor(white, black);
#endif
}

void Console::SuccessMessage(std::string msg)
{
	this->ColorMessage(dark_green, black, msg);
}

void Console::SuccessMessage(char* msg, ...)
{
	this->SetConsoleColor(green, black);
	char buf[128];
	GetArgs(msg, buf);
	printf("%s\n", buf);
	this->SetConsoleColor(white, black);
}

void Console::ErrorMessage(std::string msg)
{
	this->ColorMessage(red, black, "[ERROR] " + msg);
}

void Console::ErrorMessage(char* msg, ...)
{
	this->SetConsoleColor(red, black);
	char buf[128];
	GetArgs(msg, buf);
	printf("[ERROR] %s\n", buf);
	this->SetConsoleColor(white, black);
}