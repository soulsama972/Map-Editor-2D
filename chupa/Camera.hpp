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
	inline void SetPos(fVec3 p)
	{
		this->pos = p;
	}

	inline void Update(fVec3 pos)
	{
		fVec3 up, lookAt;
	
		// Setup the vector that points upwards.
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;

		// Setup where the camera is looking by default.
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 1.0f;

		lookAt = pos + lookAt;

		viewMatrix =  LookAtRH(pos, lookAt, up);
	}
	inline fVec3 GetCameraPos()
	{
		return pos;
	}
private:
	fVec3 pos;
	Matrix4x4 viewMatrix;
	static Window* window;
};

