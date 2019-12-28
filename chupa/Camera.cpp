#include "Camera.hpp"

Window* Camera::window = nullptr;

void Camera::Init(const fVec2& screen, float zNear, float zFar)
{
	this->screen = screen;
	SetOrthoLH(screen, zNear, zFar);
	CreateCnstantBuffer();
}

void Camera::Init(float width, float height, float zNear, float zFar)
{
	
	screen = fVec2(width, height);
	SetOrthoLH(width, height, zNear, zFar);
	CreateCnstantBuffer();

}

Camera::~Camera()
{
	SafeDelete(this->cnstantBuffer);
}

void Camera::SetOrthoLH(const fVec2& screen, float zNear, float zFar)
{
	proj.u[0][0] = 2 / screen.x;
	proj.u[1][1] = 2 / screen.y;
	proj.u[2][2] = 1 / (zFar - zNear);

	proj.u[3][2] = -zNear / (zFar - zNear);

}

void Camera::SetOrthoLH(float width, float height, float zNear, float zFar)
{
	proj.u[0][0] = 2 / width;
	proj.u[1][1] = 2 / height;
	proj.u[2][2] = 1 / (zFar - zNear);
	proj.u[3][2] = -zNear / (zFar - zNear);
}

fVec3 Camera::WorldToScreen(const fVec3& p) const
{
	fVec3 screenWorld = (p - cPos);
	return p;
}

bool Camera::InScreen(const fVec3& pos) const
{
	if (pos.x < 0 || pos.x > screen.x || pos.y < -screen.y || pos.y > 0) // cliping
		return false;
	return true;
}



void Camera::CreateCnstantBuffer()
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = bufferSize;
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	CheckFAILED(window->GetDevice()->CreateBuffer(&matrixBufferDesc, NULL, &cnstantBuffer));

	
}

void Camera::Update(void* newBuffer)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	CheckFAILED(window->GetContext()->Map(cnstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));

	// Get a pointer to the data in the constant buffer.
	memcpy(mappedResource.pData, newBuffer, bufferSize);
	// Unlock the constant buffer.
	window->GetContext()->Unmap(cnstantBuffer, 0);

	window->GetContext()->VSSetConstantBuffers(0, 1, &cnstantBuffer);
}