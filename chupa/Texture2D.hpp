#pragma once
#include "Model.hpp"
#include"Window.hpp"
#include"Math.hpp"
#include<string>
#include"Camera.hpp"
struct TextrueInstanceType
{
	Matrix4x4 matrix;
};

struct TextrueVertex
{
	fVec3 pos;
	fVec2 tex;
};



class Texture2D : private Model11<TextrueInstanceType>
{
public:
	~Texture2D();
	Texture2D() = default;
	Texture2D(std::string src, UINT MaxInstance);
	void Update(Matrix4x4 world, Matrix4x4 view, Matrix4x4 proj);
	void AddInstance(fVec3 pos, fVec3 size, Camera camera);
	void Draw(bool clearAfter = true);
	inline void Clear()
	{
		ClearInstance();
	}

	inline static void Bind(Window* window)
	{
		Texture2D::window = window;
	}

private:
	
	ID3D11ShaderResourceView* textrue = nullptr;
	ID3D11SamplerState* sampleState = nullptr;
	bool deleted = false;
	static Window* window;
};

