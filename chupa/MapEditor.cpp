#include "MapEditor.hpp"



void MapEditor::AddInstance(fVec3 pos, fVec3 size, const Camera& camera)
{
	WireSqure in = {};
	fVec3 cameraPos = camera.GetPos();
	fVec2 screen = camera.GetScreen();
	fVec3 screenWorld = screenWorld = camera.WorldToScreen(pos);

	//if (screenWorld.x + size.x < 0 || screenWorld.x - size.x> screen.x || screenWorld.y + size.y < -screen.y || screenWorld.y - size.y > 0) // cliping
	//	return;
	in.pos = screenWorld.ToNegativeY();
	in.size = size / 2;
	in.Color = fVec4(255, 255, 255, 255);
	
	wSqure.AddInstance(in);

}


MapEditor::MapEditor(Window* window, fVec3 size)
{
	this->window = window;
	camera.Bind(window);
	camera.Init(size.ToVec2(), 0.1f, 1000.0f);
	this->screen = size;
	camera.Update(fVec3(size.x/2,size.y/2,size.z));

	
	LoadTextureFromFolder(GetPath()+ "texture");

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



	wSqure.InitBuffer(window->GetDevice(), window->GetContext(),vertex , ind, 4, 6, 10000, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		,sizeof(MyStruct), sizeof(WireSqure));


	wSqure.InitializeShaders("WireSqureVs.hlsl", "main", "WireSqurePs.hlsl", "main", polygonLayout, 4);

	for (int j = 0; j <  screen.y / 100; j++)
	{
		for (int i = 0; i < screen.x / 100; i++)
		{
			AddInstance(fVec3(i * 100 + 50, j * 100 + 50, 1), fVec3(100, 100, 100), camera);
		}
	}
	InitMenu();
}

MapEditor::~MapEditor()
{
	for (auto& r : texMap)
	{
		SafeDeletePtr(r);
	}
	texMap.clear();
}

void MapEditor::MouseHandler()
{
	fVec3 ori = GetWorldMouse();
	fVec3 pos = ori ;

	if (IsInBound() && !inMenu)
	{
		if (s)
			DragAndDrop(ori);
		else
			ClickDrop(ori);
	}



}

void MapEditor::Draw()
{

	window->ClearTargetView({ 0.0f,0.0f,0.0f,1.0f });
	Matrix4x4 w;

	for (auto& i : listInfo)
	{
		texMap[i.textureId]->AddInstance(i.origin, i.size, camera);
	}
	for (auto r : texMap)
	{
		r->Draw(true);
	}
	menu.Draw();
	window->SetRasterizer(D3D11_FILL_WIREFRAME, D3D11_CULL_NONE);

	wSqure.Draw();
	window->SetRasterizer(D3D11_FILL_SOLID, D3D11_CULL_NONE);
	window->Render(true);
}

fVec3 MapEditor::GetWorldMouse()
{
	fVec3 mPos = fVec3(window->GetMousePos().x, window->GetMousePos().y,0);
	fVec3 camPos = camera.GetPos();
	fVec2 camScreen = camera.GetScreen();
	fVec2 screen = window->GetScreen();
	fVec2 diff = camScreen / screen;
	mPos.x *= diff.x;
	mPos.y *= diff.y;
	fVec3 camDiff = camPos - camScreen.ToVec3() /2;
	mPos =  mPos + camDiff;
	mPos.x = floor(mPos.x / 100) * 100 + size.x/2;
	mPos.y = floor(mPos.y / 100) * 100 + size.y/2;
	mPos.z = zPos;
	//Print("pos: %f , %f \n", mPos.x, mPos.y);
	return mPos;
}

int MapEditor::IsEmpty(fVec2 pos)
{
	int i = 0;
	for (auto& r : listInfo)
	{
		if ((pos.x >= r.pos.x && pos.x < r.pos.x + r.size.x) &&
			(pos.y >= r.pos.y && pos.y < r.pos.y + r.size.y ))
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

void MapEditor::DragAndDrop(const fVec3& pos)
{
	if (window->IsMouseClick(MOUSE::LEFT) && !stillOn)
	{
		int res = IsEmpty(pos.ToVec2());
		if (res >= 0)
		{

			size = listInfo[res].size;
			currentId = listInfo[res].textureId;
			std::swap(listInfo[res], listInfo.back());
			listInfo.pop_back();
		}
		texMap[currentId]->AddInstance(pos, size, camera);
		stillOn = true;
	}

	else if (!window->IsMouseClick(MOUSE::LEFT) && stillOn)
	{
		stillOn = false;
		TexData info;
		info.origin = pos;
		info.pos = pos;
		info.size = size;
		info.textureId = currentId;
		listInfo.push_back(info);
	}
	else if (stillOn)
		texMap[currentId]->AddInstance(pos, size, camera);
}

void MapEditor::ClickDrop(const fVec3& pos)
{
	if (window->IsMouseClick(MOUSE::LEFT) )
	{
		int res = IsEmpty(pos.ToVec2());
		if (res == -1)
		{
			TexData info;
			info.origin = pos;
			info.pos = pos;
			info.size = size;
			info.textureId = currentId;
			listInfo.push_back(info);
		}
	}
}

void MapEditor::InitMenu()
{
	menuSize = fVec3(400, screen.y, 1);
	menu.Init((GetPath() + "MapEditorMenu.png").c_str(), 1);
}

void MapEditor::UpdateMenu()
{
	mList.clear();
	fVec3 camPos = camera.GetPos().ToVec2().ToVec3();
	fVec3 pos = fVec3(menuSize.x/2, menuSize.y/2, 0) ;
	UINT index = 0;
	fVec3 itemPos = fVec3(0, 0,0);
	fVec3 itemSize = fVec3(menuSize.x / 2, menuSize.x / 2, 0);
	fVec3 ori = fVec3(-screen.x / 2, -screen.y / 2, 0) + camPos.ToVec2().ToVec3();
	UINT idLen = 0;
	for (auto r : texMap)
	{
		menu.AddInstance(ori + pos, menuSize, camera);	
		r->AddInstance(ori + itemPos  + itemSize/2, itemSize, camera);

		TexData info;
		info.pos = itemPos;
		info.origin = ori + itemPos;
		info.size = itemSize;
		info.textureId = idLen++;
		mList.push_back(info);

		index++;
		if (index == 2)
		{
			itemPos.x -= 2*(menuSize.x / 2);
			itemPos.y += menuSize.x / 2;
			index = 0;
		}
		itemPos.x += menuSize.x / 2;
	}
	fVec3 mPos =  fVec3(window->GetMousePos().x, window->GetMousePos().y,0);
	fVec3 m = mPos;

	fVec2 diff =  window->GetScreen() / camera.GetScreen().ToVec2();
	m.x /= diff.x;
	m.y /= diff.y;
	if (m.x >= 0 && m.x < menuSize.x ) // if we are in menu
		inMenu = true;
	else
		inMenu = false;
	// check if click and update textrue
	if (inMenu && window->IsMouseClick(MOUSE::LEFT))
	{
		for (auto r : mList)
		{
			if (m.x  > r.pos.x && m.x < (r.pos.x + r.size.x)  && m.y > r.pos.y && m.y < (r.pos.y + r.size.y ))
				currentId = r.textureId;
		}
	}
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
			size.x += 1.0f;
		if (window->IsKeyPress(Key::Key_A))
			size.x -= 1.0f;
		if (window->IsKeyPress(Key::Key_W))
			size.y += 1.0f;
		if (window->IsKeyPress(Key::Key_S))
			size.y -= 1.0f;
		if (window->IsKeyPress(Key::Key_Q))
			zPos -= 1.0f;
		if (window->IsKeyPress(Key::Key_E))
			zPos += 1.0f;

		if (window->IsKeyPress(Key::Key_DARROW))
			camPos.y += 10.0f;
		if (window->IsKeyPress(Key::Key_UARROW))
			camPos.y -= 10.0f;
		if (window->IsKeyPress(Key::Key_LARROW))
			camPos.x -= 10.0f;
		if (window->IsKeyPress(Key::Key_RARROW))
			camPos.x += 10.0f;
		if (window->IsKeyPress(Key::Key_1))
			s = !s;

		if (window->IsKeyPress(Key::Key_F5))
			Save("Map1");
		camera.Update(camPos);
		UpdateMenu();
		MouseHandler();
		return true;
	}

	return false;

}

void MapEditor::LoadTextureFromFolder(std::string pathOfFolder)
{
	for (const auto& entry : std::filesystem::directory_iterator(pathOfFolder))
	{
		if (entry.path().string().find(".png") != std::string::npos)
		{
			Texture2D *t = new Texture2D(entry.path().string(), 1000);
			texMap.push_back(t);
		}
	}
}


void MapEditor::Save(std::string nameOfMap)
{
	std::ofstream f(nameOfMap);
	if (f.is_open())
	{
		f << camera.GetScreen().x << ' ' << camera.GetScreen().y << std::endl;
		f << listInfo.size() << std::endl;
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

