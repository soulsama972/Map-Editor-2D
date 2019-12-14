#include "BubbleShooter.hpp"


BubbleShooter::BubbleShooter(ID3D11Device* pDev)
{

	D3D11_INPUT_ELEMENT_DESC polygonLayout[6];
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 1;
	polygonLayout[1].AlignedByteOffset = 0;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[1].InstanceDataStepRate = 1;

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


	pDev->GetImmediateContext(&devcon);
	devcon->GetDevice(&dev);


	//filled circle
	const int numPoint = 72;
	const int numVertex = numPoint;
	float doublePi = 2.0f * PI;

	VertexType VertexCircle[numVertex];
	unsigned int indexCircle[(numVertex - 1) * 3];
	for (int i = 0; i < numVertex; i++)
	{
		float Theta = i * doublePi / numPoint;
		VertexCircle[i].position = fVec3(cosf(Theta), sinf(Theta), 0.0f);
	}
	for (int i = 0; i < (numVertex - 1) * 3; i++)
	{
		if (i < 3)
			indexCircle[i] = i;

		else if (i % 3 == 0)
			indexCircle[i] = 0;
		else if (i % 3 == 1)
			indexCircle[i] = indexCircle[i - 2];
		else if (i % 3 == 2)
			indexCircle[i] = indexCircle[i - 1] + 1;
	}
	circle.InitBuffer(dev, devcon, VertexCircle, indexCircle, numVertex, (numVertex - 1) * 3, 5000, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, sizeof(VertexType), sizeof(VertexInstance));
	circle.InitializeShaders("vBubbleShooter.hlsl","main", "pBubbleShooter.hlsl", "main", polygonLayout,6);
	
}


BubbleShooter::~BubbleShooter()
{
	SafeDelete(dev)
	SafeDelete(devcon)

}

void BubbleShooter::InsertCircle(fVec2 pos, float rad, fVec4 color, bool filled)
{
	Matrix4x4 s;
	fVec2  c = fVec2(rad, rad);
	VertexInstance in;
	in.color = color;
	fVec2 scale = GetScale(c);
	fVec2 translate = GetTransalte(pos, c);

	in.matrix.Translate(fVec3(translate.x, translate.y, 0.0f).ToPointer());
	s._11 = scale.x;
	s._22 = scale.y;

	in.matrix = in.matrix * s;

	if (filled)
		fCircle.AddInstance(in);
	else
		circle.AddInstance(in);

}
