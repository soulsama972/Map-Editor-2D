#include "Camera.hpp"

Window* Camera::window = nullptr;

void Camera::Init(float width, float height, float zNear, float zFar)
{

	float l = -width / 2;
	float r = width / 2;
	float b = -height / 2;
	float t = height / 2;
	proj.u[0][0] = 2 / (r - l);
	proj.u[1][1] = 2 / (t - b);
	proj.u[2][2] = 1 / (zFar - zNear);


	proj.u[3][0] = (l + r) / (l - r);
	proj.u[3][1] = (t + b) / (b - t);
	proj.u[3][2] = zNear / (zNear - zFar);


	screen = fVec2(width, height);
}

Matrix4x4 Camera::LookAtRH(fVec3 eye, fVec3 target, fVec3 up)
{
	fVec3 zaxis = (target - eye);    // The "forward" vector.
	zaxis = zaxis.GetNormalize();
	fVec3 xaxis = Cross(up, zaxis);// The "right" vector.
	xaxis = xaxis.GetNormalize();
	fVec3 yaxis = Cross(xaxis, zaxis);     // The "up" vector.

	// Create a 4x4 view matrix from the right, up, forward and eye position vectors
	Matrix4x4 viewMatrix;
	viewMatrix.u[0][0] = xaxis.x;
	viewMatrix.u[1][0] = xaxis.y;
	viewMatrix.u[2][0] = xaxis.z;
	viewMatrix.u[3][0] = -xaxis.GetDot(eye);

	viewMatrix.u[0][1] = yaxis.x;
	viewMatrix.u[1][1] = yaxis.y;
	viewMatrix.u[2][1] = yaxis.z;
	viewMatrix.u[3][1] = -yaxis.GetDot(eye);

	viewMatrix.u[0][2] = zaxis.x;
	viewMatrix.u[1][2] = zaxis.y;
	viewMatrix.u[2][2] = zaxis.z;
	viewMatrix.u[3][2] = -zaxis.GetDot(eye);

	viewMatrix.u[0][3] = 0.0f;
	viewMatrix.u[1][3] = 0.0f;
	viewMatrix.u[2][3] = 0.0f;
	viewMatrix.u[3][3] = 1;

	return viewMatrix;
}

void Camera::Update(fVec3 pos)
{
	{
		fVec3 lookAt(0, 0, 1);
		fVec3 up(0, 1, 0);
		view = LookAtRH(pos, pos + lookAt, up);
		this->pos = pos;
	}
}
