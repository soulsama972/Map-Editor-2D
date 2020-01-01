#pragma once
#include <chrono>
#include<iostream>
#include<ctime>
#include <chrono>
#include<Windows.h>
#include<string>
#include <cstdarg>
#define SafeDelete(x) if (x != nullptr) {x->Release(); x = nullptr;}
#define SafeDeletePtr(x) if(x){delete x; x = nullptr;}
#define SafeDeletePtrArr(x) if(x){delete[] x; x = nullptr;}
#define CheckFAILED(x) if(FAILED(x)) { MessageBoxA(NULL,std::to_string(__LINE__).c_str(),__FILE__,MB_OK); exit(0);}
#define CheckAlloc(x) if(x == 0) {MessageBoxA(NULL,std::to_string(__LINE__).c_str(),__FILE__,MB_OK); exit(0);}

template<typename T>
inline void * ForceCast(T t)
{
	union MyUnion
	{
		T t;
		void* v;
	};
	MyUnion u;
	u.t = t;
	return u.v;
}

inline void Print(const char * buffer ,...)
{
	std::va_list args;
	std::wstring str;
	va_start(args, buffer);
	wchar_t* stringValue = 0;
	char r = 0;
	for(int i = 0;i<strlen(buffer);i++)
	{
		if (buffer[i] == '%')
		{
			i++;
			switch (buffer[i])
			{
			case 'd':
			case 'D':
				str += std::to_wstring(va_arg(args, int));
				break;
			case 'f':
			case 'F':
				str +=std::to_wstring(va_arg(args, double));
				break;
			case 's':
			case 'S':

				str += va_arg(args, wchar_t*);
				break;
			default:
				break;
			}
			i++;
		}
		str += buffer[i];
	}
	va_end(args);
	OutputDebugString(str.c_str());
}

inline std::string GetPath()
{
	char buffer[256];
	GetModuleFileNameA(NULL, buffer, 256);
	std::string path(buffer);
	path = path.substr(0, path.find_last_of('\\') + 1);
	return path;
}

