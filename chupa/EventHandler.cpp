#include "EventHandler.hpp"

Map EventHandler::map;

LRESULT EventHandler::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		screenResoltion.x = LOWORD(lParam);
		screenResoltion.y = HIWORD(lParam);
		OnResize(screenResoltion.x, screenResoltion.y);
		break;
	case WM_MOUSEMOVE:
	{
		mousePos.x = GET_X_LPARAM(lParam);
		mousePos.y = GET_Y_LPARAM(lParam);
	}break;
	case WM_LBUTTONDOWN: 
		mouse[LEFT] = DOWN;
		break;
	case WM_LBUTTONUP:
		mouse[LEFT] = UP;
		break;
	case WM_RBUTTONDOWN: 
		mouse[RIGHT] = DOWN;
		break;
	case WM_RBUTTONUP:
		mouse[RIGHT] = UP;
		break;

	case WM_MBUTTONDOWN: 
		mouse[MIDDLE] = DOWN;
		break;
	case WM_MBUTTONUP:
		mouse[MIDDLE] = UP;
		break;
	case WM_ACTIVATE:
	{
		switch (wParam)
		{
		case WA_ACTIVE://FOCUS
		case WA_CLICKACTIVE:
			windowFocus = ON; 
			break;
		case WA_INACTIVE:
			windowFocus = OFF; 
			break;
		}
	}break;

	case WM_KEYDOWN:
	{
		if (wParam >= 8 && wParam < 255)
			keyBoard[wParam] = DOWN;
	}break;
	case WM_KEYUP:
	{
		if (wParam >= 8 && wParam < 255)
			keyBoard[wParam] = UP;
	}break;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}



