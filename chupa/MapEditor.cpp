#include "MapEditor.hpp"

MapEditor::MapEditor(Window* window, fVec3 size)
{
	this->window = window;
	camera.Bind(window);
	camera.Init(300, 300, 1, 1000);
	camera.Update({ size.x/2,size.y/2,size.z/2 });
	this->size = size;
}

void MapEditor::MouseHandler()
{
	fVec3 mousePos = fVec3(window->GetMousePos().x, window->GetMousePos().y,0);
	fVec2 objectSize = fVec2(100.0f, 100.0f);
	tempPos = IRect(mousePos.x - objectSize.x / 2, mousePos.y - objectSize.y / 2, objectSize.x, objectSize.y);
	tempPos = Translate(mousePos, objectSize);
	if (window->IsMouseClick(MOUSE::LEFT) && !stillOn)
	{
		int res = IsEmpty(fVec2(mousePos.x,mousePos.y));
		if (res >= 0)
		{
			std::swap(listRect[res], listRect.back());
			listRect.pop_back();
		}
		tex->AddInstance(tempPos);
		stillOn = true;
	}
	else if (!window->IsMouseClick(MOUSE::LEFT) && stillOn)
	{
		stillOn = false;
		listRect.push_back(tempPos);
	}
	else if (stillOn)
	{
		tex->AddInstance(tempPos);
	}
	for (auto& i : listRect)
	{
		IRect r;
		r.x = i.x - camera.GetCameraPos().x;
		r.y = i.y - camera.GetCameraPos().y;
		r.z = i.z;
		r.w = i.w;
		if (r.x < 0)
			r.x = 0;
		if (r.x > size.x)
			r.x = size.x - r.z;
		if (r.y < 0)
			r.y = 0;
		if (r.y + r.w > size.y)
			r.y = size.y - r.w;
		tex->AddInstance(r);
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
	
		if (window->IsKeyPress(Key::Key_C))
		{
			listRect.clear();
		}

		MouseHandler();

		return true;
	}

	return false;
}


void MapEditor::Save()
{

}

