#pragma once
#include<Windows.h>
#include<windowsx.h>
class EventHandler
{
public:
	EventHandler();
	~EventHandler();
};

class Map
{
public:
	void AddInstance(HWND hwnd, EventHandler* eventHandler)
	{
		if (currentCount < maxInstance)
		{
			this->hwnd[currentCount] = hwnd;
			this->eventHandler[currentCount] = eventHandler;
			currentCount++;

		}
	}

	inline EventHandler* GetWindow(HWND hwnd)
	{
		for (int i = 0; i < 100; i++)
		{
			if (hwnd == this->hwnd[i])
				return eventHandler[i];
		}
		return 0;
	}
private:

	int currentCount = 0;
	int maxInstance = 100;
	HWND hwnd[100] = { 0 };
	EventHandler* eventHandler[100] = { 0 };
};
