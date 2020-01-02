#pragma once
#include"Model.hpp"
#include"Math.hpp"
#include"StaticObject.hpp"
#include<vector>
#include"Camera.hpp"
#include<string>
#include<fstream>
#include <filesystem>

class MapEditor
{
public:
	MapEditor(Window* window,fVec3 size);
	~MapEditor();

	void MouseHandler();
	void Draw();
	bool Update();
	void LoadTextureFromFolder(std::string pathOfFolder);
	void Save(std::string nameOfMap);
private:
	struct TexData
	{
		fVec3	pos;
		fVec3	origin;
		fVec3	size;
		UINT textureId = 0;
	};

	struct WireSqure
	{
		fVec3 pos;
		fVec3 size;
		fVec4 Color;
	};
	void AddInstance(fVec3 pos, fVec3 size, const Camera& camera);
	Model11<WireSqure> wSqure;

	fVec3 GetWorldMouse();
	int IsEmpty(fVec2 pos);
	bool IsInBound();
	void DragAndDrop(const fVec3 &pos);
	void ClickDrop(const fVec3& pos);
	fVec3 size = fVec3(100.0f, 100.0f, 100.0f);
	bool stillOn = false;
	fVec3 screen;
	Window* window = nullptr;
	std::vector<TexData> listInfo;
	float zPos = 1;
	Camera camera;
	bool s = false;
	UINT texId = 0;
	std::vector<Texture2D*> lTex;

private://menu texture
	void InitMenu();
	void UpdateMenu();
	inline void DrawMenu()
	{
		menu.Draw(false);
	}
	bool inMenu = false;
	Texture2D menu;
	fVec3 menuSize;
	std::vector< TexData> mList;
};
