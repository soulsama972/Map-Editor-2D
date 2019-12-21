#pragma once
#include "Math.hpp"
#include "Entity.hpp"
#include "Physics.hpp"
#include "StaticObject.hpp"


class Player : public Entity
{
public:
	void Init(fVec2 size, Texture2D* texture, fVec3 position, fVec3 origin, Physics physics, bool isDestroyable, bool isAlive, int healthPoint, int manaPoint);
	void Motion(float deltaTime, StaticObject obj);
};

