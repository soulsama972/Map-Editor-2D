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
	World();
	void CreateMap(std::string file);
protected:
	
private:
	fVec2 screenMap;
	std::vector<Object> object;
	std::vector<Entity> entity;

};

