#pragma once
#include"Window.hpp"


class Camera
{
public:
	void Init(const fVec2& screen, float zNear, float zFar);
	void Init(float width, float height, float zNear, float zFar);

	~Camera();
	void SetOrthoLH(const fVec2& screen, float zNear, float zFar);
	void SetOrthoLH(float width, float height, float zNear, float zFar);
	fVec3 WorldToScreen(const fVec3& p)const;
	
	bool InScreen(const fVec3& pos)const;

	inline void Bind(Window* window)
	{
		this->window = window;
	}

	inline void Update(fVec3 pos)
	{
		this->cPos = pos;
		//SetOrthoLH(window->GetScreen(), 0.1, 1000);
		ConstBuffer b;
		b.cPos = cPos;
		b.proj = proj;
		Update(&b);
	}

	inline fVec3 GetPos() const
	{
		return cPos;
	}

	inline Matrix4x4 GetProjMatrix()const
	{
		return proj;
	}

	inline fVec2 GetScreen()const
	{
		return screen;
	}

private:
	struct ConstBuffer
	{
		Matrix4x4 proj;
		fVec3 cPos;
	};
	const UINT bufferSize = 16 * 8;
	void CreateCnstantBuffer();
	void Update(void* newBuffer);
	
	ID3D11Buffer* cnstantBuffer = nullptr;
	fVec3 cPos;
	fVec2 screen;
	Matrix4x4 proj;
	static Window* window;
};

