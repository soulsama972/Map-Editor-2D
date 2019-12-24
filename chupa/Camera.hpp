#pragma once
#include"Window.hpp"


class Camera
{
public:
	void Init(float width, float height, float zNear, float zFar);
	
	Matrix4x4 LookAtRH(fVec3 eye, fVec3 target, fVec3 up);
	
	void Update(fVec3 pos);
	
	inline void Bind(Window* window)
	{
		this->window = window;
	}

	inline fVec3 GetPos()
	{
		return pos;

	}

	inline Matrix4x4 GetProjMatrix()
	{
		return proj;
	}

	inline fVec2 GetScreen()
	{
		return screen;
	}
	Matrix4x4 view;
private:
	fVec3 pos;
	fVec2 screen;
	Matrix4x4 proj;
	static Window* window;
};

