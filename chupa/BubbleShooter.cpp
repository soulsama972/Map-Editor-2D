#include "BubbleShooter.hpp"


<<<<<<< HEAD
BubbleShooter::BubbleShooter(ID3D11Device* pDev)
=======

BubbleShooter::BubbleShooter(ID3D11Device* pDev,fVec2* Screen)
>>>>>>> a1299912828782dc60d5cdf84eb7dfba028dd530
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

	screen = Screen;
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
	
	srand(static_cast<unsigned int>(time(NULL)));

	colors[0] = blue;
	colors[1] = red;
	colors[2] = green;
	colors[3] = yellow;
	colors[4] = crystal;

	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 17; x++)
		{
			if (y % 2 == 1)
			{
				bubble[y][x].color = colors[rand() % 5];
				bubble[y][x].pos.x = x + 0.5;
				bubble[y][x].pos.y = y;
			}
			else
			{
				bubble[y][x].color = colors[rand() % 5];
				bubble[y][x].pos.x = x;
				bubble[y][x].pos.y = y;
			}
			bubble[y][x].alive = true;
		}
	}

}


BubbleShooter::~BubbleShooter()
{
	SafeDelete(dev)
	SafeDelete(devcon)

}

void BubbleShooter::InsertCircle(fVec2 pos, float rad, fVec4 color)
{
	Matrix4x4 s;
	fVec2  c = fVec2(rad, rad);
	VertexInstance in;
	in.color = color;
	fVec2 scale = GetScale(c,*screen);
	fVec2 translate = GetTransalte(pos, c,*screen);

	in.matrix.Translate(fVec3(translate.x, translate.y, 0.0f).ToPointer());
	s._11 = scale.x;
	s._22 = scale.y;

	in.matrix = in.matrix * s;
	circle.AddInstance(in);

}

void BubbleShooter::Draw()
{
	float deltaX = screen->x * 0.80f / 17;
	float deltaY = screen->y  / 16;

	float rad = (deltaX * deltaX + deltaY * deltaY) / sqrt(deltaX * deltaX + deltaY * deltaY)/2;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 17; x++)
		{
			if (bubble[y][x].alive)
			{
				InsertCircle(fVec2(bubble[y][x].pos.x * deltaX, bubble[y][x].pos.y * deltaY), rad, bubble[y][x].color);
			}
		}
	}

	circle.Draw();
	circle.ClearInstance();
}
