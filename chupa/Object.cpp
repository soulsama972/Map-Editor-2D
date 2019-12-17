#include "Object.hpp"

Object::Object(fVec2 size, bool isDestroyable)
{
	this->size = size;
	this->isDestroyable = isDestroyable;
}

void Object::SetSize(fVec2 size)
{
	this->size = size;
}


void Object::SetIsDestroyable(bool isDestroyable)
{
	this->isDestroyable = isDestroyable;
}
