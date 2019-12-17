#include "Object.hpp"



void Object::Init(fVec2 size, Texture2D* texture, fVec3 position, fVec3 origin, Physics* physics, bool isDestroyable)
{
	SetSize(size);
	SetTexture(texture);
	SetPosition(position);
	SetOrigin(origin);
	SetPhysics(physics);
	SetIsDestroyable(isDestroyable);


}

void Object::SetIsDestroyable(bool isDestroyable)
{
	this->isDestroyable = isDestroyable;
}

void Object::SetPhysics(Physics* physics)
{
	this->physics = physics;
}

bool Object::GetIsDestroyable()
{
	return isDestroyable;
}

Physics* Object::GetPhysics()
{
	return physics;
}
