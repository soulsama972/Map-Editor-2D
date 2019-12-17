#include "Entity.hpp"


void Entity::init(fVec2 size, Texture2D* texture, fVec3 position, fVec3 origin, Physics* physics, bool isDestroyable, bool isAlive, int healthPoint, int manaPoint)
{
	SetSize(size);
	SetTexture(texture);
	SetPosition(position);
	SetOrigin(origin);
	SetPhysics(physics);
	SetIsDestroyable(isDestroyable);
	SetIsAlive(isAlive);
	SetHealthPoint(healthPoint);
	SetManaPoint(manaPoint);
}

void Entity::SetIsAlive(bool isAlive)
{
	this->isAlive = isAlive;
}

void Entity::SetHealthPoint(int healthPoint)
{
	this->healthPoint = healthPoint;
}

void Entity::SetManaPoint(int manaPoint)
{
	this->manaPoint = manaPoint;
}

bool Entity::GetIsAlive()
{
	return isAlive;
}

int Entity::GetHealthPoint()
{
	return healthPoint;
}

int Entity::GetManaPoint()
{
	return manaPoint;
}
