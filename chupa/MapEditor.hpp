#pragma once
#include"Model.hpp"
#include"Math.hpp"
#include"StaticObject.hpp"
#include<vector>
#include"Camera.hpp"
#include<string>
#include<fstream>


class MapEditor
{
public:
	MapEditor(Window* window,fVec3 size);
	inline void SetTexture(Texture2D** tex,int count)
	{
		this->tex = tex;
		TextureCount = count;
	}
	void MouseHandler();
	void Draw();
	bool Update();
	void Save(std::string nameOfMap);
private:
	struct TexData
	{
		fVec3	pos;
		fVec3	origin;
		fVec3	size;
		UINT textureId = 0;
	};

	fVec3 GetWorldMouse();

	int IsEmpty(fVec2 pos);
	bool IsInBound();
	fVec3 size = fVec3(100.0f, 100.0f, 100.0f);
	bool stillOn = false;
	fVec3 screen;
	Window* window = nullptr;
	Texture2D** tex = nullptr;
	int TextureCount = 0;
	std::vector<TexData> listInfo;
	Camera camera;
};
