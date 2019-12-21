#include "Player.hpp"

void Player::Init(fVec2 size, Texture2D* texture, fVec3 position, fVec3 origin, Physics physics, bool isDestroyable, bool isAlive, int healthPoint, int manaPoint)
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

void Player::Motion(float deltaTime, StaticObject obj)
{
	fVec3 pos = this->GetPosition();
	Physics physics = this->GetPhysics();
	float velocity = physics.GetVelocity();


	if (window->IsKeyPress(Key::Key_RARROW))
	{
		physics.SetVelocity(10);
		pos.x += (velocity * deltaTime);
		if(!IsCollide(obj))
			this->SetPosition(pos);
	}
	if (window->IsKeyPress(Key::Key_LARROW)) {
		physics.SetVelocity(10);
		pos.x -= (velocity * deltaTime);
		if (!IsCollide(obj))
			this->SetPosition(pos);
	}
}
