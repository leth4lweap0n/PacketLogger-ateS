// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "stdafx.h"

//
int (WINAPI* pSend)(SOCKET socket, const char* buffer, int length, int flags) = send;
int (WINAPI* pRecv)(SOCKET socket, char* buffer, int length, int flags) = recv;
int (WINAPI* pWSARecv)(SOCKET socket, LPWSABUF buffer, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) = WSARecv;
int (WINAPI* pWSASend)(SOCKET socket, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) = WSASend;
//
bool bLogSend = false;
bool bLogRecv = false;
//
#pragma region WSA RECV
int WINAPI MyWSARecv(SOCKET socket, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	std::vector<byte> listBuff;
	std::string packet;
	int rval = pWSARecv(socket, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);
	ULONG len = *lpNumberOfBytesRecvd;

	if (bLogRecv && len > MINPACKETLEN)
	{
		ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_LIGHTBLUE, ("[W-Recv-%d:%d]"), len ,lpFlags);
		if (len > 100)
			len = 100;
		for (unsigned int i = 0; i < len; i++)
		{
			//ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_LIGHTGREEN, ("%02X "), static_cast<unsigned char>(lpBuffers->buf[i]));
			listBuff.push_back(lpBuffers->buf[i]);
		}
		boost::algorithm::hex(listBuff.begin(), listBuff.end(), back_inserter(packet));
		std::cout << packet << std::endl;
		listBuff.clear();
		packet.clear();
		//printf("\n");
	}
	return rval;
}
#pragma endregion

#pragma region SEND
int WINAPI MySend(SOCKET socket, const char* buffer, int length, int flags)
{
	std::vector<byte> listBuff;
	std::string packet;
	int rval = pSend(socket, buffer, length, flags);
	ULONG len = length;
	if (bLogSend && len > MINPACKETLEN)
	{
		ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_LIGHTBLUE, ("[Send-%d:%d] "), len, flags);
		if (len > 100)
			len = 100;
		for (unsigned int i = 0; i < len; i++)
		{
			listBuff.push_back(buffer[i]);
			//ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_LIGHTGREEN, ("%02X "), (unsigned char)buffer[i]);
		}
		boost::algorithm::hex(listBuff.begin(), listBuff.end(), back_inserter(packet));
		std::cout << packet << std::endl;
		listBuff.clear();
		packet.clear();
		//printf("\n");
	}
	return rval;
}
#pragma endregion

#pragma region WSA SEND
int WINAPI MyWSASend(SOCKET socket, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	std::vector<byte> listBuff;
	std::string packet;
	int rval = pWSASend(socket, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
	ULONG len = *lpNumberOfBytesSent;

	if (bLogSend && len > MINPACKETLEN)
	{
		ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_LIGHTBLUE, ("[W-Send-%d:%d]"), len, dwFlags);
		if (len > 100)
			len = 100;
		for (unsigned int i = 0; i < len; i++)
		{
			//ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_LIGHTGREEN, ("%02X "), static_cast<unsigned char>(lpBuffers->buf[i]));
			listBuff.push_back(lpBuffers->buf[i]);
		}
		boost::algorithm::hex(listBuff.begin(), listBuff.end(), back_inserter(packet));
		std::cout << packet << std::endl;
		listBuff.clear();
		packet.clear();
		//printf("\n");
	}

	return rval;
}
#pragma endregion

#pragma region RECV
int WINAPI MyRecv(SOCKET socket, char* buffer, int length, int flags)
{
	std::vector<byte> listBuff;
	std::string packet;
	int rval = pRecv(socket, buffer, length, flags);
	ULONG len = length;
	if (bLogRecv && len > MINPACKETLEN)
	{
		ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_LIGHTBLUE, ("[Recv-%d:%d] "), len, flags);
		if (len > 100)
			len = 100;
		for (unsigned int i = 0; i < len; i++)
		{
			//ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_LIGHTGREEN, ("%02X "), (unsigned char)buffer[i]);
			listBuff.push_back(buffer[i]);
		}
		boost::algorithm::hex(listBuff.begin(), listBuff.end(), back_inserter(packet));
		std::cout << packet << std::endl;
		listBuff.clear();
		packet.clear();
		//printf("\n");
	}
	return rval;
}
#pragma endregion

#pragma region CONSOLE
extern  "C"  __declspec(dllexport) void __cdecl Init()
{
	if (!AllocConsole())
		return;

	freopen("CON", "r", stdin);
	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);

	char sConsoleTitle[MAX_PATH];
	memset(sConsoleTitle, 0, MAX_PATH);
	sprintf(sConsoleTitle, "Knight Online Client ateS-PacketLogger - Debug Console");
	SetConsoleTitleA(sConsoleTitle);

	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = 500;
	coninfo.dwMaximumWindowSize.Y = 700;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	long lStdHandle1 = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	int hConHandle1 = _open_osfhandle(lStdHandle1, _O_TEXT);
	FILE* fp1 = _fdopen(hConHandle1, "w");
	*stdin = *fp1;
	setvbuf(stdin, NULL, _IONBF, 0);

	long lStdHandle2 = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	int hConHandle2 = _open_osfhandle(lStdHandle2, _O_TEXT);
	FILE* fp2 = _fdopen(hConHandle2, "w");
	*stdout = *fp2;
	setvbuf(stdout, NULL, _IONBF, 0);

	long lStdHandle3 = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	int hConHandle3 = _open_osfhandle(lStdHandle3, _O_TEXT);
	FILE* fp3 = _fdopen(hConHandle3, "w");
	*stderr = *fp3;
	setvbuf(stderr, NULL, _IONBF, 0);

	time_t t;
	struct tm* zaman_bilgisi;
	time(&t);
	zaman_bilgisi = localtime(&t);
	ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_YELLOW, ("Sistem dosyalari dogrulandi -> %s\n"), asctime(zaman_bilgisi));
	ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_RED, ("ateS-PacketLogger started up successfully!\n\n"));
	ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_WHITE, "Console running...\n\n");
}

void EjectDLL(HMODULE hModule)
{
	Sleep(500);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
};
DWORD WINAPI MainThread(LPVOID lpModule)
{
	while (1)
	{
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			bLogSend = !bLogSend;
			ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_RED, ("[bLogSend - %s]\n"), bLogSend ? "true" : "false");
		}

		if (GetAsyncKeyState(VK_F2) & 1)
		{
			bLogRecv = !bLogRecv;
			ShowMessageSystem::ShowMessage(true, MSG_NORMAL, CONSOLE_FORE_COLOR_LIGHTRED, ("[bLogRecv - %s]\n"), bLogRecv ? "true" : "false");
		}

		if (GetAsyncKeyState(VK_F10) & 1) { EjectDLL(HMODULE(lpModule)); }
		Sleep(10);
	}
}
#pragma endregion

#pragma region DLLMAIN
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Init, hModule, NULL, NULL);
		CreateThread(NULL, 0, MainThread, hModule, NULL, NULL);
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)pSend, MySend);
		//DetourAttach(&(PVOID&)pWSARecv, MyWSASend);
		if (DetourTransactionCommit() == NO_ERROR)
			OutputDebugStringA("send() detoured successfully");
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		//DetourAttach(&(PVOID&)pRecv, MyRecv);
		DetourAttach(&(PVOID&)pWSARecv, MyWSARecv);
		if (DetourTransactionCommit() == NO_ERROR)
			OutputDebugStringA("recv() detoured successfully");
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}
#pragma endregion 