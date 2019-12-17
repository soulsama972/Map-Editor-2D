#include "Entity.hpp"

Entity::Entity(bool isAlive, int healthPoint, int manaPoint)
{
	this->isAlive = isAlive;
	this->healthPoint = healthPoint;
	this->manaPoint = manaPoint;
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
