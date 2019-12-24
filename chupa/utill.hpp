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
	std::string str;
	va_start(args, buffer);
	for(int i = 0;i<strlen(buffer);i++)
	{
		if (buffer[i] == '%')
		{
			i++;
			switch (buffer[i])
			{
			case 'd':
			case 'D':
				str += std::to_string(va_arg(args, int));
				break;
			case 'f':
			case 'F':
				str +=std::to_string(va_arg(args, double));
				break;
			default:
				break;
			}
			i++;
		}
		str += buffer[i];
	}
	va_end(args);
	OutputDebugStringA(str.c_str());
}

