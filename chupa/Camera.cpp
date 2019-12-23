#include "Camera.hpp"

Window* Camera::window = nullptr;


void Camera::Init(float width, float height, float zNear, float zFar)
{	
	view = LookAtRH(fVec3(0,0,10), fVec3(0.0f,0.0f,-10.0f),fVec3(0,1,0));

	proj.u[0][0] = 1 / width;
	proj.u[1][1] = 1 / height;
	proj.u[2][2] = 1 / (zFar-zNear);
	proj.u[3][2] = zNear / (zNear - zFar);


}

