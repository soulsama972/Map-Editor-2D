#include "Object.hpp"

Window* Object::window = nullptr;

void Object::Init(fVec3 size, Texture2D* texture, fVec3 position, fVec3 origin, Physics physics, bool isDestroyable)
{
	SetSize(size);
	SetTexture(texture);
	SetPosition(position);
	SetOrigin(origin);
	SetPhysics(physics);
	SetIsDestroyable(isDestroyable);


}

void Object::Update(float deltaTime)
{
	fVec3 pos = this->GetPosition();
	Physics physics = this->GetPhysics();
	float velocity = physics.GetVelocity();


	if (window->IsKeyPress(Key::Key_RARROW))
	{
		physics.SetVelocity(10);
		pos.x += (velocity * deltaTime);
		this->SetPosition(pos);
	}
	if (window->IsKeyPress(Key::Key_LARROW)) {
		physics.SetVelocity(10);
		pos.x -= (velocity * deltaTime);
		this->SetPosition(pos);
	}
}

bool Object::IsCollide(StaticObject anotherObj)
{
	if (this->GetPosition() == anotherObj.GetPosition())
	{
		return false;
	}else
		return false;
}

void Object::SetIsDestroyable(bool isDestroyable)
{
	this->isDestroyable = isDestroyable;
}

void Object::SetPhysics(Physics physics)
{
	this->physics = physics;
}

bool Object::GetIsDestroyable()
{
	return isDestroyable;
}

Physics Object::GetPhysics()
{
	return physics;
}
