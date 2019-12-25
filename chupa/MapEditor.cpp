#include "MapEditor.hpp"

MapEditor::MapEditor(Window* window, fVec3 size)
{
	this->window = window;
	camera.Bind(window);
	camera.Init(size.x, size.y, 0.1f, 1000.0f);
	this->screen = size;
	camera.Update(fVec3(0.0f,0.0f,-10.0f));

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
	tex[0]->Update(w, camera.view, camera.GetProjMatrix());
	tex[1]->Update(w, camera.view, camera.GetProjMatrix());
	for (auto& i : listInfo)
	{
		tex[0]->AddInstance(i.origin, i.size, camera);
	}

	tex[0]->Draw(true);
	tex[1]->Draw(true);
	
	window->Render(true);
}

fVec3 MapEditor::GetWorldMouse()
{
	fVec3 mPos = fVec3(window->GetMousePos().x, window->GetMousePos().y, 0);
	fVec3 camPos = camera.GetPos();
	fVec2 camScreen = camera.GetScreen();
	fVec2 screen = window->GetScreen();
	fVec3 p;
	Matrix4x4 viewProj = camera.view * camera.GetProjMatrix();
	Matrix4x4 inv = viewProj.InvertMatrix();
	mPos = mPos*2;
	p.x = mPos.x / screen.x - 1;
	p.y = -((mPos.y / screen.y )- 1);
	

	fVec3 screenWorld = p.TransfromV3(inv);
	screenWorld.x = screenWorld.x + camScreen.x / 2;
	screenWorld.y = camScreen.y / 2 - screenWorld.y;
	screenWorld.z = 1;
	Print("pos: %f , %f \n", screenWorld.x, screenWorld.y);
	return screenWorld;
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

