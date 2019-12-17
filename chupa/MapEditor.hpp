#pragma once
#include"Model.hpp"
#include"Math.hpp"
#include"StaticObject.hpp"



class MapEditor
{
public:
	MapEditor(Window* window,fVec3 size);
	inline void SetTexture(Texture2D* tex)
	{
		this->tex = tex;
	}
	void Draw();
	bool Update();
	void Save();
private:
	bool stillOn = false;
	fVec3 size;
	Window* window = nullptr;
	Texture2D* tex = nullptr;
};

