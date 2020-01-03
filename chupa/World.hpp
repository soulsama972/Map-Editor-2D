#pragma once
#include"Math.hpp"
#include"Model.hpp"
#include"Object.hpp"
#include"Entity.hpp"
#include<string>
#include<vector>
#include<filesystem>
class World 
{
public:
	World() = default;
	void LoadMap(std::string file);
	void Draw(const Camera& camera);
	fVec3 screenMap;
	void ClearAll();
protected:
	
private:
	void LoadTextureFromFolder(std::string pathOfFolder);
	struct TexData
	{
		fVec3	pos;
		fVec3	origin;
		fVec3	size;
		UINT textureId = 0;
	};
	std::vector<Texture2D*> tex;
	std::vector<TexData> listInfo;
	std::vector<Object> object;
	std::vector<StaticObject>sObject;
	std::vector<Entity> entity;

};

