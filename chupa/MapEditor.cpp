#include "MapEditor.hpp"

MapEditor::MapEditor(Window* window, fVec3 size)
{
	this->window = window;
	camera.Bind(window);
	camera.Init(300, 300, 1, 1000);
	camera.Update(fVec3(0,0,0));
	this->size = size;
}

void MapEditor::MouseHandler()
{
	fVec3 mousePos = fVec3(window->GetMousePos().x, window->GetMousePos().y,0);
	fVec2 objectSize = fVec2(100.0f, 100.0f);
	fVec3 camPos = camera.GetPos();
	tempPos = mousePos - camPos;
	if (window->IsMouseClick(MOUSE::LEFT) && !stillOn)
	{
		int res = IsEmpty(fVec2(mousePos.x,mousePos.y));
		if (res >= 0)
		{
			std::swap(listRect[res], listRect.back());
			listRect.pop_back();
		}
		IRect r;
		r.x = tempPos.x;
		r.y = tempPos.y;
		r.z = objectSize.x;
		r.w = objectSize.y;
		tex->AddInstance(r);
		stillOn = true;
	}
	else if (!window->IsMouseClick(MOUSE::LEFT) && stillOn)
	{
		stillOn = false;
		IRect r;
		r.x = tempPos.x;
		r.y = tempPos.y;
		r.z = objectSize.x;
		r.w = objectSize.y;
		listRect.push_back(r);
	}
	else if (stillOn)
	{
		IRect r;
		r.x = tempPos.x;
		r.y = tempPos.y;
		r.z = objectSize.x;
		r.w = objectSize.y;
		tex->AddInstance(r);
	}
	for (auto& i : listRect)
	{
		tex->AddInstance(i);
	}


}

void MapEditor::Draw()
{
	Texture2D t2("b2.png", 5000);
	t2.AddInstance(IRect(0.0f, 0.0f, size.x, size.y));
	window->ClearTargetView({ 0.0f,0.0f,0.0f,1.0f });

	tex->Draw(true);
	t2.Draw();
	window->Render();



}

int MapEditor::IsEmpty(fVec2 pos)
{
	int i = 0;
	for (auto& r : listRect)
	{
		if ((pos.x >= r.x&& pos.x <= r.x + r.z) && (pos.y >= r.y && pos.y <= r.y + r.w))
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
			listRect.clear();
		}
		if (window->IsKeyPress(Key::Key_D))
			camPos.x += 1;
		if (window->IsKeyPress(Key::Key_A))
			camPos.x -= 1;
		camera.Update(camPos);
		MouseHandler();
		
		return true;
	}

	return false;
}


void MapEditor::Save()
{

}

