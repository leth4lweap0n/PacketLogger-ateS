#include "pch.h"
#include "stdafx.h"

void _string_format(const std::string fmt, std::string* result, va_list args)
{
	char buffer[1024];
	_vsnprintf(buffer, sizeof(buffer), fmt.c_str(), args);
	*result = buffer;
}


std::string string_format(const std::string fmt, ...)
{
	std::string result;
	va_list ap;

	va_start(ap, fmt);
	_string_format(fmt, &result, ap);
	va_end(ap);

	return result;
}

void tstring_format(const std::string fmt, std::string* result, va_list args)
{
	char buffer[1024];
	_vsnprintf_s(buffer, sizeof(buffer), fmt.c_str(), args);
	*result = buffer;
}
