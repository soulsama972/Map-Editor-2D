#pragma once
#include <chrono>
#include<iostream>
#include<ctime>
#include <chrono>
#include<Windows.h>


#define SafeDelete(x) if (x != nullptr) {x->Release(); x = nullptr;}
#define CheckFAILED(x) if(FAILED(x)) { MessageBoxA(NULL,std::to_string(__LINE__).c_str(),__FILE__,MB_OK); exit(0);}
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
#ifdef _WIN32
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> stop;
#else
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> stop;
#endif
};