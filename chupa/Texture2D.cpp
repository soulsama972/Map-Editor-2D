#include "Texture2D.hpp"

Window* Texture2D::window = nullptr;

Texture2D::~Texture2D()
{
	SafeDelete(this->sampleState);
	SafeDelete(this->textrue);
}

Texture2D::Texture2D(std::string src,UINT MaxInstance)
{
	const auto& devcon = window->GetContext();
	const auto& dev = window->GetDevice();
	TextrueVertex vertex[4];


	vertex[0].pos = fVec3(-1.0f, -1.0f, 0.0f);
	vertex[1].pos = fVec3(-1.0f, 1.0f, 0.0f);
	vertex[2].pos = fVec3(1.0f, 1.0f, 0.0f);
	vertex[3].pos = fVec3(1.0f, -1.0f, 0.0f);

	vertex[0].tex = fVec2(0,1);
	vertex[1].tex = fVec2(0, 0);
	vertex[2].tex = fVec2(1, 0);
	vertex[3].tex = fVec2(1, 1);

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

	polygonLayout[1].SemanticName = "tex";
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



	InitBuffer(dev, devcon, vertex, ind,4,6, MaxInstance, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, sizeof(TextrueVertex), sizeof(TextrueInstanceType));

	InitializeShaders("Texture2DVs.hlsl", "main", "Texture2DPs.hlsl", "main", polygonLayout, 6);


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


	CreateCnstantBuffer(16 *4 * 4 );
}

void Texture2D::Update(Matrix4x4 world, Matrix4x4 view, Matrix4x4 proj)
{
	struct MyStruct
	{
		Matrix4x4 w;
		Matrix4x4 v;
		Matrix4x4 p;
	};
	MyStruct my;
	my.w = world;
	my.v = view;
	my.p = proj;
	Model11::Update(&my);
}

void Texture2D::AddInstance(fVec3 pos, fVec3 size, Camera camera)
{
	TextrueInstanceType in;
	Matrix4x4 s = SetScaleMatrix(size/2);
	fVec3 cameraPos = camera.GetPos();
	fVec2 screen = camera.GetScreen();
	
	//pos = pos - cameraPos.ToNegativeY();
	fVec3 screenWorld = pos.TransfromV3( camera.GetProjMatrix());
	screenWorld.x = screenWorld.x * (screen.x / 2) - ( screen.x / 2);
	screenWorld.y = -screenWorld.y * (screen.y / 2) + (screen.y / 2);
	screenWorld.z = size.z;
	//screenWorld = pos.Transfrom((camera.view * camera.GetProjMatrix()).InvertMatrix());
	//if (screenWorld.x + size.x < 0 || screenWorld.x - size.x> screen.x || screenWorld.y + size.y < -screen.y || screenWorld.y - size.y > 0) // cliping
	//	return;
	fVec4 invProj = fVec4(2 / screen.x, -2 / screen.y, 1 / (1000.0f - 1), 1);
//	 invProj = fVec4(2 / screen.x - screen.x  , -2 / screen.y  + screen.y, 1 / (1000.0f - 1) + (1 - 1000.0f), 1);
	fVec4 vertex = fVec4(-1, -1, 0, 1);
	fVec4 test =   (vertex * size.ToFVec4()/2 + vertex* screenWorld.ToFVec4());
	test.w = 1;
	test = test * invProj;
	//test.x = test.x * (screen.x / 2) - (screen.x / 2);
	//test.y = -test.y * (screen.y / 2) + (screen.y / 2);
	//test.z = size.z;
	in.matrix.Translate(screenWorld.ToPointer());
	in.matrix = s * in.matrix;
	//Model11::AddInstance(in);
	//fVec4 vertex = fVec4(-1, -1, 0,1);
	vertex = vertex.TransfromV4(in.matrix);
	//vertex = vertex.TransfromV4(camera.view);
	vertex = vertex.TransfromV4(camera.GetProjMatrix());
	Matrix4x4 m;
	m.Translate(test.ToPointer());
	in.matrix = m;
	Model11::AddInstance(in);

}



void Texture2D::Draw(bool clearAfter)
{
	
	const auto& devcon = window->GetContext();
	devcon->PSSetShaderResources(0, 1, &textrue);
	devcon->PSSetSamplers(0, 1, &sampleState);
	Model11::Draw();
	devcon->PSSetShaderResources(0, 0,0);
	devcon->PSSetSamplers(0, 0,0);
	if(clearAfter)
		ClearInstance();
}

