#include "EventHandler.hpp"

Map EventHandler::map;

LRESULT EventHandler::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{


	case WM_MOUSEMOVE:
	{
		mousePos.x = GET_X_LPARAM(lParam);
		mousePos.y = GET_Y_LPARAM(lParam);
	}break;
	case WM_LBUTTONDOWN: mouseDown[LEFT] = true;break;
	case WM_LBUTTONUP:mouseDown[LEFT] = false;break;

	case WM_RBUTTONDOWN: mouseDown[RIGHT] = true; break;
	case WM_RBUTTONUP:mouseDown[RIGHT] = false; break;

	case WM_MBUTTONDOWN: mouseDown[MIDDLE] = true; break;
	case WM_MBUTTONUP:mouseDown[MIDDLE] = false; break;
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


