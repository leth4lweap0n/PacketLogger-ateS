#pragma once
//========================================
//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_DEPRECATE
//#pragma warning(disable : 4996)
//#pragma warning(disable : 4099)
//#pragma warning(disable : 4800)
//========================================
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
//========================================
#define _WINSOCKAPI_
#include "winsock2.h"
#include "windows.h"
#include "windef.h"
#include "random"
#include "ws2tcpip.h"
#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "cstdio"
#include "ctime"
#include "fcntl.h"
#include "corecrt_io.h"
#include "detours.h"
#include "showmessage.h"
#include "time.h"
#include "fstream"
#include "stdint.h"
#include "iostream"
#include "commctrl.h"
#include "cstdint"
#include "direct.h"
#include "sstream"
#include "iomanip"
#include "vector"
#include "map"
#include "algorithm"
#include "types.h"
#include "minwindef.h"
#include "tchar.h"
#include "list"
#include "vector"
#include "PacketDefine.h"
#include "JvCryption.h"
#include "boost/algorithm/hex.hpp"
//========================================
#pragma comment(lib, "detours.lib")
//========================================
#pragma comment(lib, "ws2_32.lib")
//========================================
#define MINPACKETLEN 5
#define MAX_PACKETSIZE 1024
#undef UNICODE
//========================================
void _string_format(const std::string fmt, std::string* result, va_list args);
static std::string string_format(const std::string fmt, ...);
static void tstring_format(const std::string fmt, std::string* result, va_list args);
//========================================
typedef unsigned char byte;