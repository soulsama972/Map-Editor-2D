#pragma once
#include"Window.hpp"


class Camera
{
public:
	void Init(float width,float height,float zNear,float zFar);
	inline void Bind(Window* window)
	{
		this->window = window;
	}

	inline void Update(fVec3 pos)
	{
		
		this->pos = pos;
	}
	inline fVec3 GetPos()
	{
		return pos;
	}
private:
	fVec3 pos;

	static Window* window;
};

