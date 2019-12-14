#include "Entity.hpp"

Entity::Entity(float objHight, float objWidth, bool isDestroyable, bool isAlive, Physics entityPhysics)
{
	setObjHight(objHight);
	setObjWidth(objWidth);
	setIsDestroyable(isDestroyable);
	this->isAlive = isAlive;
	this->entityPhysics = entityPhysics;

	
}
