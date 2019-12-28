#include "StaticObject.hpp"

void StaticObject::Init(fVec3 size, Texture2D* texture, fVec3 position, fVec3 origin)
{
	this->size = size;
	this->texture = texture;
	this->position = position;
	this->origin = origin;
}

void StaticObject::SetSize(fVec3 size)
{
	this->size = size;
}

void StaticObject::SetTexture(Texture2D* texture)
{
	this->texture = texture;
}

void StaticObject::SetPosition(fVec3 position)
{
	this->position = position;
}

void StaticObject::SetOrigin(fVec3 origin)
{
	this->origin = origin;
}



fVec3 StaticObject::GetSize()
{
	return size;
}

Texture2D* StaticObject::GetTexture()
{
	return texture;
}

fVec3 StaticObject::GetPosition()
{
	return position;
}

fVec3 StaticObject::GetOrigin()
{
	return origin;
}


