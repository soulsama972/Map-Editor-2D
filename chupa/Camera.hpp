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
	inline Matrix4x4 GetProjMatrix()
	{
		return proj;
	}
	Matrix4x4 view;
private:
	fVec3 pos;
	Matrix4x4 proj;
	
	static Window* window;
};

