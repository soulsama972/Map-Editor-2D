#include "MapEditor.hpp"

MapEditor::MapEditor(Window* window, fVec3 size)
{
	this->window = window;
	camera.Bind(window);
	camera.Init(800, 600, 1.0f, 1000.0f);
	camera.Update(fVec3(0,0,0));
	this->screen = size;
}

void MapEditor::MouseHandler()
{
	fVec3 mousePos = fVec3(window->GetMousePos().x, window->GetMousePos().y,0);
	fVec3 camPos = camera.GetPos();
	temp.pos = mousePos + camPos;
	temp.size = fVec2(100.0f, 100.0f);
	temp.origin = temp.pos - fVec3(temp.size.x/2, temp.size.y/2, 0.0f);
	if (window->IsMouseClick(MOUSE::LEFT) && !stillOn)
	{
		int res = IsEmpty(fVec2(temp.pos.x, temp.pos.y));
		if (res >= 0)
		{
			std::swap(listPos[res], listPos.back());
			listPos.pop_back();
		}
		tex->AddInstance(temp.origin, camera.GetPos(), temp.size);
		stillOn = true;
	}
	else if (!window->IsMouseClick(MOUSE::LEFT) && stillOn)
	{
		stillOn = false;

		listPos.push_back(temp);
	}
	else if (stillOn)
	{
		
		tex->AddInstance(temp.origin, camera.GetPos(), temp.size);
	}
	for (auto& i : listPos)
	{
		tex->AddInstance(i.origin,camera.GetPos(), i.size);
	}


}

void MapEditor::Draw()
{
	Texture2D t2("b2.png", 5000);
	Texture2D t("b.png", 5000);
	//t2.AddInstance(fVec3(0,0,0),fVec3(0,0,0),fVec2(300,300));
	t2.Test(fVec3(900.0, 0.0, 1.0), fVec2(100, 100), camera);
//	t.Test(fVec3(900.0, 100.0, 0.0), fVec2(100, 100), camera);
	window->ClearTargetView({ 0.0f,0.0f,0.0f,1.0f });

	tex->Draw(true);
	t.Draw();
	t2.Draw();
	
	window->Render();
}

int MapEditor::IsEmpty(fVec2 pos)
{
	int i = 0;
	for (auto& r : listPos)
	{
		if ((pos.x > r.origin.x && pos.x < r.origin.x + r.size.x) &&
			(pos.y > r.origin.y && pos.y < r.origin.y + r.size.y ))
			return i;
		i++;
	}
	return -1;

}

bool MapEditor::Update()
{
	if (window->LoopEvent())
	{
		fVec3 camPos = camera.GetPos();
		if (window->IsKeyPress(Key::Key_C))
		{
			listPos.clear();
		}
		if (window->IsKeyPress(Key::Key_D))
			camPos.x += 5.01f;
		if (window->IsKeyPress(Key::Key_A))
			camPos.x -= 5.01f;
		if (window->IsKeyPress(Key::Key_W))
			camPos.y -= 5.01f;
		if (window->IsKeyPress(Key::Key_S))
			camPos.y += 5.01f;
		if (window->IsKeyPress(Key::Key_Q))
			camPos.z += 5.01f;
		if (window->IsKeyPress(Key::Key_E))
			camPos.z -= 5.01f;
		camera.Update(camPos);
		MouseHandler();
		
		return true;
	}

	return false;
}


void MapEditor::Save()
{

}

