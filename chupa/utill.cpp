#include "utill.hpp"

Timer::Timer()
{
	start = std::chrono::high_resolution_clock::now();
	stop = std::chrono::high_resolution_clock::now();
	fps = 0;
}

double Timer::GetMilisecondsElapsed()
{
	if (isrunning)
	{
		auto elapsed = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start);
		return elapsed.count();
	}
	else
	{
		auto elapsed = std::chrono::duration<double, std::milli>(stop - start);
		return elapsed.count();
	}
}

void Timer::Restart()
{
	fps++;
	if (GetMilisecondsElapsed() > 1000.0f)
	{
		std::string fString = "FPS: " + std::to_string(fps) + "\n";
		OutputDebugStringA(fString.c_str());
		fps = 0;

		isrunning = true;
		start = std::chrono::high_resolution_clock::now();
	}

}

bool Timer::Stop()
{
	if (!isrunning)
		return false;
	else
	{
		stop = std::chrono::high_resolution_clock::now();
		isrunning = false;
		return true;
	}
}

bool Timer::Start()
{
	if (isrunning)
	{
		return false;
	}
	else
	{
		start = std::chrono::high_resolution_clock::now();
		isrunning = true;
		return true;
	}
}