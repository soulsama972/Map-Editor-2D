#pragma once
#include"Math.hpp"
#include<Windows.h>
#include<windowsx.h>

class Map;

enum MOUSE
{
	LEFT ,
	MIDDLE,
	RIGHT,

};
class EventHandler
{
public:
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	EventHandler() = default;
	~EventHandler() = default;

	static Map map;
private:
	vec2<int> mousePos;
	bool mouseDown[3] = { 0 };
	bool windowFocus = false;
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

	inline EventHandler* GetWindow(HWND hwnd) const
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
