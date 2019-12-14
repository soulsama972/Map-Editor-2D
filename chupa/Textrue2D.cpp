#include "Textrue2D.hpp"

Textrue2D::Textrue2D(std::string src,ID3D11Device * dev,ID3D11DeviceContext* devcon)
{

	this->devcon = devcon;
	TextrueVertex vertex[4];
	/*vertex[0].pos = fVec3(-1.0f, -1.0f, 0.0f);
	vertex[1].pos = fVec3(-1.0f, 1.0f, 0.0f);
	vertex[2].pos = fVec3(1.0f, 1.0f, 0.0f);
	vertex[3].pos = fVec3(1.0f, -1.0f, 0.0f);*/


	vertex[0].pos = fVec3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertex[0].tex = fVec2(0.0f, 1.0f);

	vertex[1].pos = fVec3(4.0f, 1.0f, 0.0f);  // Top middle.
	vertex[1].tex = fVec2(0.0f, 0.0f);

	vertex[2].pos = fVec3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertex[2].tex = fVec2(1.0f, 1.0f);


	/*vertex[0].tex = fVec2(0,1);
	vertex[1].tex = fVec2(1, 0);
	vertex[2].tex = fVec2(1, 1);
	vertex[3].tex = fVec2(0, 0);*/

	unsigned int ind[] =
	{
		0,1,2,
		0,2,3
	};
	D3D11_INPUT_ELEMENT_DESC polygonLayout[6];


	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "world";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[2].InputSlot = 1;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[2].InstanceDataStepRate = 1;

	polygonLayout[3] = polygonLayout[2];
	polygonLayout[4] = polygonLayout[2];
	polygonLayout[5] = polygonLayout[2];

	polygonLayout[3].SemanticIndex = 1;
	polygonLayout[4].SemanticIndex = 2;
	polygonLayout[5].SemanticIndex = 3;



	InitBuffer(dev, devcon, vertex, ind, 3, 3,6, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, sizeof(TextrueVertex), sizeof(TextrueInstanceType));

	InitializeShaders("Textrue2DVs.hlsl", "main", "Textrue2DPs.hlsl", "main", polygonLayout, 6);


	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	CheckFAILED(dev->CreateSamplerState(&samplerDesc, &sampleState));

	// Load the texture in.
	CheckFAILED(D3DX11CreateShaderResourceViewFromFileA(dev, src.c_str(), NULL, NULL, &textrue, NULL));
}

void Textrue2D::DrawObj(IRect rect, fVec2 Screen)
{
	TextrueInstanceType in;
	in.matrix;
	Matrix4x4 s;
	fVec2 scale = GetScale(fVec2(rect.z,rect.w), Screen);
	fVec2 translate = GetTransalte(fVec2(rect.x, rect.y),fVec2(rect.z,rect.w), Screen);

	in.matrix.Translate(fVec3(translate.x, translate.y, 0.0f).ToPointer());
	s._11 = scale.x;
	s._22 = scale.y;
	in.matrix = in.matrix * s;

	AddInstance(in);
	devcon->PSSetShaderResources(0, 1, &textrue);
	devcon->PSSetSamplers(0, 1, &sampleState);
	Draw();

	ClearInstance();
}
