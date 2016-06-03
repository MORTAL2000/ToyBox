#include <cstdarg>
#include <string>
#include <cstring>
#include <functional>
#include "toy/Log.hpp"
#include "toy/Windows.hpp"
#include "toy/Utf.hpp"



//----------------PrintStr let you choose the way to print string----------------start

namespace toy{
namespace log{

#if defined(TOY_WINDOWS)
	static std::function<void(const char*)> PrintStr = [](const char *str)
	{
		auto      word = utf::UTF8ToWChar(std::string(str));
		DWORD     ws;
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),word.c_str(),word.size(),&ws,nullptr);
	};

	static std::function<void(const wchar_t*)> PrintStrW = [](const wchar_t *str)
	{
		DWORD     ws;
		WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE),str,std::wcslen(str),&ws,nullptr);
	};
#else
	static std::function<void(const char*)> PrintStr = [](const char *str)
	{
		printf("%s",str);
	};

	static std::function<void(const wchar_t*)> PrintStrW = [](const wchar_t *str)
	{
		//wprintf(L"%ls",str);    // No. It doesn't works on Linux.
		printf("%s",utf::WCharToUTF8(std::wstring(str)).c_str());
	};
#endif

}//namespace log
}//namespace toy

void toy::log::SetDevice(std::function<void(const char*)> func)
{
	toy::log::PrintStr = std::move(func);
}

void toy::log::SetDevice(std::function<void(const wchar_t*)> func)
{
	toy::log::PrintStrW = std::move(func);
}

//----------------PrintStr let you choose the way to print string----------------end



#define STRING_SIZE 128

void toy::Log(const char *fmt, ... )
{
	va_list         argptr;
	va_start(argptr, fmt);

	char      buffer[STRING_SIZE];
	vsnprintf(buffer,STRING_SIZE,fmt,argptr);
	toy::log::PrintStr(buffer);

	va_end(argptr);
}

void toy::Log(const wchar_t *fmt, ... )
{
	va_list         argptr;
	va_start(argptr, fmt);

	wchar_t      buffer[STRING_SIZE];

	#if defined(TOY_MSVC)
		_vsnwprintf_s(buffer,STRING_SIZE,(int)STRING_SIZE-1,fmt,argptr);
	#elif defined(TOY_MINGW)
		vsnwprintf(buffer,STRING_SIZE,fmt,argptr);
	#else
		vswprintf(buffer,STRING_SIZE,fmt,argptr);   // Just in case.
	#endif

	toy::log::PrintStrW(buffer);

	va_end(argptr);
}

void toy::Log(const std::exception &except)
{
	toy::Log("%s\n",except.what());
}

#undef STRING_SIZE
