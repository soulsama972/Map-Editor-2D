#pragma once
#include <chrono>
#include<iostream>
#include<ctime>
#include <chrono>
#include<Windows.h>
#include<string>

#define SafeDelete(x) if (x != nullptr) {x->Release(); x = nullptr;}
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

class Timer
{
public:
	Timer();
	double GetMilisecondsElapsed();
	void Restart();
	bool Stop();
	bool Start();
private:
	bool isrunning = false;
	uintptr_t fps;
#ifdef _WIN32
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> stop;
#else
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> stop;
#endif
};