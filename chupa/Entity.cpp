#include "Entity.hpp"




void Entity::Init(fVec3 size, Texture2D* texture, fVec3 position, fVec3 origin, Physics physics, bool isDestroyable, bool isAlive, int healthPoint, int manaPoint)
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

void Entity::AutoMotion(float deltaTime, StaticObject obj)
{
	fVec3 pos = this->GetPosition();
	Physics physics = this->GetPhysics();
	float velocity = physics.GetVelocity();
	timeElapsed += deltaTime;
	physics.SetVelocity(10);

	if(timeElapsed <6.0f){
		pos.x += (velocity * deltaTime);
		if(!IsCollide(obj))
			this->SetPosition(pos);
	}
	else if (timeElapsed < 12.0f)
	{
		pos.x -= (velocity * deltaTime);
		if (!IsCollide(obj))
			this->SetPosition(pos);
	}
	else {
		pos.x += (velocity * deltaTime);
		if (!IsCollide(obj))
			this->SetPosition(pos);
		timeElapsed = 0;
	}
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
