#pragma once
#include "Model.hpp"
#include"Window.hpp"
#include"Math.hpp"
#include<string>
#include"Camera.hpp"

struct TextrueInstanceType
{
	fVec3 pos;
	fVec3 size;
};





class Texture2D : private Model11<TextrueInstanceType>
{
public:
	~Texture2D();
	Texture2D() = default;
	Texture2D(std::string src,std::string vs,std::string ps, UINT MaxInstance);
	void Init(std::string src, std::string vs, std::string ps, UINT MaxInstance);
	void AddInstance(const fVec3& pos, const fVec3& size, const Camera& camera);
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
	void CreateSample();
	void CreateVertexTexBuffer(UINT MaxInstance);
	void CreateVertexColorBuffer(UINT MaxInstance);
	ID3D11ShaderResourceView* textrue = nullptr;
	ID3D11SamplerState* sampleState = nullptr;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[4] = {};

	static Window* window;
};


