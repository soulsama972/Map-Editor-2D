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
	struct TexMapInfo
	{
		Texture2D* tex;
		UINT textureId = 0;
		char name[256] = { 0 };
	};
	struct WireSqure
	{
		fVec3 pos;
		fVec3 size;
		fVec4 Color;
	};




	void MouseHandler();
	void AddInstance(fVec3 pos, fVec3 size, const Camera& camera);

	fVec3 GetWorldMouse();
	int IsEmpty(fVec2 pos);
	bool IsInBound();
	void DragAndDrop(const fVec3 &pos);
	void ClickDrop(const fVec3& pos);

	Model11<WireSqure> wSqure;
	fVec3 size = fVec3(100.0f, 100.0f, 100.0f);
	bool stillOn = false;
	fVec3 screen;
	std::vector<TexData> listInfo;
	float zPos = 1;
	Camera camera;
	bool s = false;

	std::vector< TexMapInfo> texMap;
	UINT texIdLen = 0;
	UINT currentId = 0;
	Window* window = nullptr;
private://menu of texture
	void InitMenu();

	void UpdateMenu();


	bool inMenu = false;

	Texture2D menu;

	fVec3 menuSize;

	std::vector< TexData> mList;
};
