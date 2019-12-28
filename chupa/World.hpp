#pragma once
#include"Math.hpp"
#include"Model.hpp"
#include"Object.hpp"
#include"Entity.hpp"
#include<string>
#include<vector>
class World 
{
public:
	World() = default;
	void LoadMap(std::string file);
	void Draw(const Camera& camera);
	Texture2D *tex;
	fVec3 screenMap;
	void ClearAll();
protected:
	
private:
	struct TexData
	{
		fVec3	pos;
		fVec3	origin;
		fVec3	size;
		UINT textureId = 0;
	};

	std::vector<TexData> listInfo;
	std::vector<Object> object;
	std::vector<StaticObject>sObject;
	std::vector<Entity> entity;

};

