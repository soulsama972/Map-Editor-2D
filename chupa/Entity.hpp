#pragma once
#include "Object.hpp"
#include "Physics.hpp"

class Entity : public Object
{
public:
	Entity(fVec2 size, bool isDestroyable, bool isAlive, Physics EntityPhysics);
protected:

private:
	bool isAlive;
	int healthPoint = 10;
	int manaPoint = 0;

};

