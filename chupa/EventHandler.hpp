#pragma once
#include"Math.hpp"
#include<Windows.h>
#include<windowsx.h>
#include<mutex>
class Map;



enum MOUSE
{
	LEFT ,
	MIDDLE,
	RIGHT,

};

enum Key
{
	Key_BACK = 0x8,
	Key_TAB,
	Key_ENTER = 0xD,

	Key_ESCAPE = 0x1B,
	Key_SPACE = 0x20,
	Key_PAGEUP,
	Key_PAGEDOWN,
	Key_END,
	Key_HOME,
	Key_LARROW,
	Key_UARROW,
	Key_RARROW,
	Key_DARROW,

	Key_INS = 0x2D,
	Key_DEL,

	Key_0 = 0x30,
	Key_1,
	Key_2,
	Key_3,
	Key_4,
	Key_5,
	Key_6,
	Key_7,
	Key_8,
	Key_9,

	Key_A = 0x41,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,


	Key_NUMPAD0 = 0x60,
	Key_NUMPAD1,
	Key_NUMPAD2,
	Key_NUMPAD3,
	Key_NUMPAD4,
	Key_NUMPAD5,
	Key_NUMPAD6,
	Key_NUMPAD7,
	Key_NUMPAD8,
	Key_NUMPAD9,


	Key_F1 = 0x70,
	Key_F2,
	Key_F3,
	Key_F4,
	Key_F5,
	Key_F6,
	Key_F7,
	Key_F8,
	Key_F9,
	Key_F10,
	Key_F11,
	Key_F12,
	Key_F13,
	Key_F14,
	Key_F15,
	Key_F16,

	Key_OEM_CLEAR = 0xFE
};

class EventHandler
{
public:
	EventHandler() = default;
	~EventHandler() = default;
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool LoopEvent();

	inline bool IsKeyPress(Key k)
	{
		if (k >= Key_BACK && k <= Key_OEM_CLEAR)
			return keyBoard[k];
		else
			return false;
	}

	inline bool IsMouseClick(MOUSE m)
	{
		if (m >= LEFT && m <= RIGHT)
			return mouse[m];
		else
			return false;
	}

	inline bool IsWindowFocus()
	{
		return windowFocus;
	}

	inline bool IsWindowDestory()
	{
		return windowDestory;
	}
	static Map map;




protected:

	virtual void OnResize(int width, int hegiht) = 0;
	virtual void OnQuitMsg() = 0;
	
	HWND hwnd = 0;
private:
	enum
	{
		UP,
		DOWN,
	};

	enum
	{
		OFF,
		ON
	};

	
	vec2<int> mousePos;
	vec2<int> screenResoltion;
	bool mouse[3] = { OFF };
	bool windowFocus = false;
	bool windowDestory = false;
	bool keyBoard[255] = { DOWN };
};

class Map
{
public:
	inline void AddInstance(HWND hwnd, EventHandler* eventHandler)
	{
		if (currentCount < maxInstance)
		{
			this->hwnd[currentCount] = hwnd;
			this->eventHandler[currentCount] = eventHandler;
			currentCount++;

		}
	}

	inline void DelInstance(HWND hwnd)
	{
		if (currentCount > 1)
		{
			for (int i = 0; i < currentCount; i++)
			{
				if (hwnd == this->hwnd[i])
				{
					if (currentCount - 1 == i)
						currentCount--;
					else
					{
						this->hwnd[i] = this->hwnd[currentCount - 1];
						this->eventHandler[i] = this->eventHandler[currentCount - 1];
						currentCount--;
					}
				}
			}
		}
		else if(this->hwnd[0] == hwnd)
			currentCount = 0;
			
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
