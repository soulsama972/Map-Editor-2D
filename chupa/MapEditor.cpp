#include "MapEditor.hpp"



void MapEditor::AddInstance(fVec3 pos, fVec3 size, Camera camera)
{
	WireSqure in;
	fVec3 cameraPos = camera.GetPos();
	fVec2 screen = camera.GetScreen();

	fVec3 screenWorld = (pos - cameraPos.ToNegativeY()).TransfromV3(camera.GetProjMatrix());
	screenWorld.x = screenWorld.x * (screen.x / 2) - (screen.x / 2);
	screenWorld.y = -screenWorld.y * (screen.y / 2) + (screen.y / 2);
	screenWorld.z = size.z;


	//if (screenWorld.x + size.x < 0 || screenWorld.x - size.x> screen.x || screenWorld.y + size.y < -screen.y || screenWorld.y - size.y > 0) // cliping
	//	return;
	in.pos = screenWorld;
	in.size = size / 2;
	in.Color = fVec4(255, 255, 255, 255);
	wSqure.AddInstance(in);

}


MapEditor::MapEditor(Window* window, fVec3 size)
{
	this->window = window;
	camera.Bind(window);
	camera.Init(size.x, size.y, 0.1f, 1000.0f);
	this->screen = size;
	camera.Update(fVec3(0.0f,0.0f,-10.0f));



	struct MyStruct
	{
		fVec3 pos;
	};
	MyStruct vertex[4];


	vertex[0].pos = fVec3(-1.0f, -1.0f, 0.0f);
	vertex[1].pos = fVec3(-1.0f, 1.0f, 0.0f);
	vertex[2].pos = fVec3(1.0f, 1.0f, 0.0f);
	vertex[3].pos = fVec3(1.0f, -1.0f, 0.0f);

	unsigned int ind[] =
	{
		0,1,2,
		0,2,3
	};
	D3D11_INPUT_ELEMENT_DESC polygonLayout[4];

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "POS";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[1].InputSlot = 1;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[1].InstanceDataStepRate = 1;

	polygonLayout[2].SemanticName = "SIZE";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 1;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[2].InstanceDataStepRate = 1;

	polygonLayout[3].SemanticName = "COLOR";
	polygonLayout[3].SemanticIndex = 0;
	polygonLayout[3].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[3].InputSlot = 1;
	polygonLayout[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[3].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
	polygonLayout[3].InstanceDataStepRate = 1;



	wSqure.InitBuffer(window->GetDevice(), window->GetContext(),vertex , ind, 4, 6, 1000, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		,sizeof(MyStruct), sizeof(WireSqure));


	wSqure.InitializeShaders("WireSqureVs.hlsl", "main", "WireSqurePs.hlsl", "main", polygonLayout, 4);

	
}

void MapEditor::MouseHandler()
{
	fVec3 ori = GetWorldMouse();
	fVec3 pos = ori - size/2;

	if (IsInBound())
	{
		if (window->IsMouseClick(MOUSE::LEFT) && !stillOn)
		{
			int res = IsEmpty(ori.ToFVec2());
			if (res >= 0)
			{
				size = listInfo[res].size;
				std::swap(listInfo[res], listInfo.back());
				listInfo.pop_back();
			}
			tex[0]->AddInstance(ori, size, camera);
			stillOn = true;
		}

		else if (!window->IsMouseClick(MOUSE::LEFT) && stillOn)
		{
			stillOn = false;
			TexData info;
			info.origin = ori;
			info.pos = pos;
			info.size = size;
			info.textureId = 1;
			listInfo.push_back(info);
		}

		else if (stillOn)
		{

			tex[0]->AddInstance(ori, size, camera);
		}
	}
}

void MapEditor::Draw()
{

	window->ClearTargetView({ 0.0f,0.0f,0.0f,1.0f });
	Matrix4x4 w;

	for (auto& i : listInfo)
	{
		tex[0]->AddInstance(i.origin, i.size, camera);
	}
	


	tex[0]->Draw(true);
	tex[1]->Draw(true);

	for (int j = 0; j < screen.y /100; j++)
	{
		for (int i = 0; i < screen.x / 100; i++)
		{
			AddInstance(fVec3(i * 100 + 50, j * 100 + 50, 1), fVec3(100,100,100), camera);
		}
	}
	window->SetRasterizer(D3D11_FILL_WIREFRAME, D3D11_CULL_NONE);

	wSqure.Draw();
	wSqure.ClearInstance();
	window->SetRasterizer(D3D11_FILL_SOLID, D3D11_CULL_NONE);
	window->Render(true);
}

fVec3 MapEditor::GetWorldMouse()
{
	fVec3 mPos = fVec3(window->GetMousePos().x, window->GetMousePos().y, 0);
	fVec3 camPos = camera.GetPos();
	fVec2 camScreen = camera.GetScreen();
	fVec2 screen = window->GetScreen();
	fVec2 diff = camScreen / screen;
	mPos.x *= diff.x;
	mPos.y *= diff.y;
	mPos =  mPos + camPos.ToNegativeY();
	//Print("pos: %f , %f \n", mPos.x, mPos.y);
	return mPos;
}

int MapEditor::IsEmpty(fVec2 pos)
{
	int i = 0;
	for (auto& r : listInfo)
	{
		if ((pos.x > r.pos.x && pos.x < r.pos.x + r.size.x) &&
			(pos.y > r.pos.y && pos.y < r.pos.y + r.size.y ))
			return i;
		i++;
	}
	return -1;

}

bool MapEditor::IsInBound()
{
	fVec3 ori = GetWorldMouse();
	if(ori.x < 0 || ori.x > screen.x || ori.y < 0 || ori.y > screen.y)
		return false;
	return true;
}

bool MapEditor::Update()
{
	if (window->LoopEvent())
	{
		fVec3 camPos = camera.GetPos();
		if (window->IsKeyPress(Key::Key_C))
		{
			listInfo.clear();
		}

		if (window->IsKeyPress(Key::Key_D))
			size.x += 10.0f;
		if (window->IsKeyPress(Key::Key_A))
			size.x -= 10.0f;
		if (window->IsKeyPress(Key::Key_W))
			size.y += 10.0f;
		if (window->IsKeyPress(Key::Key_S))
			size.y -= 10.0f;
		if (window->IsKeyPress(Key::Key_Q))
			size.z -= 1.0f;
		if (window->IsKeyPress(Key::Key_E))
			size.z += 1.0f;

		if (window->IsKeyPress(Key::Key_DARROW))
			camPos.y -= 10.0f;
		if (window->IsKeyPress(Key::Key_UARROW))
			camPos.y += 10.0f;
		if (window->IsKeyPress(Key::Key_LARROW))
			camPos.x -= 10.0f;
		if (window->IsKeyPress(Key::Key_RARROW))
			camPos.x += 10.0f;


		if (window->IsKeyPress(Key::Key_F5))
			Save("Map1");
		camera.Update(camPos);
		MouseHandler();
		
		return true;
	}

	return false;
}


void MapEditor::Save(std::string nameOfMap)
{
	std::ofstream f(nameOfMap);
	if (f.is_open())
	{
		f << camera.GetScreen().x << ' ' << camera.GetScreen().y << std::endl;
		for (auto& r : listInfo)
		{
			f << r.origin.x << ' ' << r.origin.y << ' ' << r.origin.z << ' ';
			f << r.pos.x	<< ' ' <<	r.pos.y << ' ' << r.pos.z << ' ';
			f << r.size.x	<< ' ' << r.size.y << ' ' << r.size.z << ' ';
			f << r.textureId << std::endl;
		}
		f.close();
	}
}

