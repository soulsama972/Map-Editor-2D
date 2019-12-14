#include "Object.hpp"

Object::Object(float objHight, float objWidth, bool isDestroyable)
{
	this->objHight = objHight;
	this->objWidth = objWidth;
	this->isDestroyable = isDestroyable;
}

void Object::setObjHight(float objHight)
{
	this->objHight = objHight;
}

void Object::setObjWidth(float objWidth)
{
	this->objWidth = objWidth;
}

void Object::setIsDestroyable(float isDestroyable)
{
	this->isDestroyable = isDestroyable;
}
