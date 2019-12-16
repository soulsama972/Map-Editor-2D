#pragma once
#include "Model.hpp"
#include"Math.hpp"
#include<string>
struct TextrueInstanceType
{
	Matrix4x4 matrix;
};
struct TextrueVertex
{
	fVec3 pos;
	fVec2 tex;
};
using IRect = vec4<int>;


class Textrue2D : private Model11<TextrueInstanceType>
{
public:
	Textrue2D(std::string src,ID3D11Device* dev, ID3D11DeviceContext* devcon);
	
	void DrawObj(IRect rect,fVec2 Screen);

private:
	ID3D11ShaderResourceView* textrue;
	ID3D11SamplerState* sampleState;
	ID3D11DeviceContext* devcon;
};

