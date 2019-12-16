#pragma once
#include "Object.hpp"
#include "Physics.hpp"

class Entity : public Object
{
public:
	Entity(float objHight, float objWidth, bool isDestroyable, bool isAlive, Physics EntityPhysics);
protected:

private:
	//Physics EntityPhysics;
	bool isAlive;
	int healthPoint = 10;
	int manaPoint = 0;

};

