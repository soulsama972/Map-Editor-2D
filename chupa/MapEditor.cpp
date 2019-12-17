#include "MapEditor.hpp"

MapEditor::MapEditor(Window* window, fVec3 size)
{
	this->window = window;
	this->size = size;
}

void MapEditor::Draw()
{
	window->ClearTargetView({ 0.0f,0.0f,0.0f,1.0f });
	tex->Draw(false);
	window->Render();
}

bool MapEditor::Update()
{
	if (window->LoopEvent())
	{
		if (window->IsKeyPress(Key::Key_C))
		{
			tex->Clear();
		}
		if (window->IsMouseClick(MOUSE::LEFT))
		{
			IRect pos = { window->GetMousePos().x,window->GetMousePos().y,100,100 };
			tex->AddInstance(pos);
		}
		return true;
	}
	return false;
}


void MapEditor::Save()
{

}
