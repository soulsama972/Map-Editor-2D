#include "Physics.hpp"

void Physics::Init(float velocity, float vacceleration)
{
	this->velocity = velocity;
	this->vacceleration = vacceleration;
}

void Physics::SetVelocity(float velocity)
{
	this->velocity = velocity;
}

void Physics::SetVacceleration(float vacceleration)
{
	this->vacceleration = vacceleration;
}

float Physics::GetVelocity()
{
	return velocity;
}

float Physics::GetVacceleration()
{
	return vacceleration;
}
