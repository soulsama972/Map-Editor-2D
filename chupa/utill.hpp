#pragma once
#include <chrono>
#include<iostream>
#include<ctime>
#include <chrono>
#include<Windows.h>
#include<string>

#define SafeDelete(x) if (x != nullptr) {x->Release(); x = nullptr;}
#define SafeDeletePtr(x) if(x){delete x; x = nullptr;}
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


