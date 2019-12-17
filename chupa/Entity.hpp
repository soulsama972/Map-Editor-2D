#pragma once
#include "Object.hpp"
#include "Physics.hpp"

class Entity : public Object
{
public:
	Entity(bool isAlive, int healthPoint, int manaPoint);

	void SetIsAlive(bool isAlive);
	void SetHealthPoint(int healthPoint);
	void SetManaPoint(int manaPoint);

	bool GetIsAlive();
	int GetHealthPoint();
	int GetManaPoint();

protected:

private:
	bool isAlive = true;
	int healthPoint = 10;
	int manaPoint = 0;

};

