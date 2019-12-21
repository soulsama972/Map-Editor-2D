#pragma once
#include"Window.hpp"
class Camera
{
public:

	inline void Bind(Window* window)
	{
		this->window = window;
	}
	inline void Update(fVec3 pos)
	{
		this->pos = pos;
	}
	inline fVec3 GetCameraPos()
	{
		return pos;
	}
private:
	fVec3 pos;

	static Window* window;
};

