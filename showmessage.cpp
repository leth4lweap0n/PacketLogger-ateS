#include "pch.h"
#include "stdafx.h"

#pragma region ShowMessageSystem::ShowMessageSystem()

ShowMessageSystem::ShowMessageSystem()
{
	/*

	*/
}

#pragma endregion

#pragma region ShowMessageSystem::ShowMessage(bool nStatus, MSG_TYPE type, ConsoleColor sColor, LPCSTR msg, ...)

/*
	@brief	Use this method for only debug purposes. Prints
	the message on the screen depending on its level.
	@param	type	The message type.
	@param	msg	The log message.
	@param	...		the parameters.
*/

void ShowMessageSystem::ShowMessage(bool nStatus, MSG_TYPE type, ConsoleColor sColor, LPCSTR msg, ...)
{
	if (nStatus)
	{
		std::string result;
		va_list ap;

		va_start(ap, msg);
		_string_format(msg, &result, ap);
		va_end(ap);

		if (type == MSG_NORMAL)//1
		{
			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), sColor);
		}

		printf(result.c_str());
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), sColor);
	}
}

#pragma endregion 

#pragma region ShowMessageSystem::color_c(char* buff,WORD color)

void ShowMessageSystem::color_c(char* buff, WORD color)
{
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD written;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	SetConsoleTextAttribute(hstdout, color);

	WriteConsole(hstdout, buff, strlen(buff), &written, NULL);
}

#pragma endregion 