#pragma once
#include "Object.hpp"
#include "Physics.hpp"

class Entity : public Object
{
public:
	Entity() = default;
	void init(fVec2 size, Texture2D* texture, fVec3 position, fVec3 origin, Physics* physics, bool isDestroyable, bool isAlive, int healthPoint, int manaPoint);
	

	//sets
	void SetIsAlive(bool isAlive);
	void SetHealthPoint(int healthPoint);
	void SetManaPoint(int manaPoint);

	//gets
	bool GetIsAlive();
	int GetHealthPoint();
	int GetManaPoint();

protected:

private:
	bool isAlive = true;
	int healthPoint = 10;
	int manaPoint = 0;

};

