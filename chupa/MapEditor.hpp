#pragma once
#include"Model.hpp"
#include"Math.hpp"
#include"StaticObject.hpp"
#include<vector>
#include"Camera.hpp"

class MapEditor
{
public:
	MapEditor(Window* window,fVec3 size);
	inline void SetTexture(Texture2D* tex,int count)
	{
		this->tex = tex;
		TextureCount = count;
	}
	inline IRect Translate(fVec3 p, fVec2 s);
	void MouseHandler();
	void Draw();
	bool Update();
	void Save();
private:
	int IsEmpty(fVec2 pos);
	bool stillOn = false;
	fVec3 size;
	Window* window = nullptr;
	Texture2D* tex = nullptr;
	int TextureCount = 0;
	std::vector<IRect> listRect;
	Camera camera;
	IRect tempPos;
};
inline IRect MapEditor::Translate(fVec3 p, fVec2 s)
{
	fVec3 cPos = camera.GetCameraPos();
	IRect r;
	r.x = p.x - s.x / 2;
	r.x = p.y - s.y / 2;
	r.z = s.x;
	r.w = s.y;
	return r;
}