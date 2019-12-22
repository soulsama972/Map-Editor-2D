#include "Camera.hpp"

Window* Camera::window = nullptr;


//2 / w  0    0           0
//0    2 / h  0           0
//0    0    1 / (zf - zn)   0
//0    0 - zn / (zf - zn)  1
void Camera::Init(float width, float height, float zNear, float zFar)
{
	/*viewMatrix._11 = 2 / width;
	viewMatrix._22 = 2 / height;
	viewMatrix._33 = 1 / (zFar - zNear);
	viewMatrix._43 = -zNear / (zFar - zNear);*/
}

