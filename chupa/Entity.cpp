#include "Entity.hpp"

Entity::Entity(fVec2 size, bool isDestroyable, bool isAlive, Physics entityPhysics)
{
	SetSize(size);
	SetIsDestroyable(isDestroyable);
	this->isAlive = isAlive;
}
