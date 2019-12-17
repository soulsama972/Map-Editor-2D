#pragma once
class Physics
{
public:
	Physics(float velocity, float vacceleration);
	
	//sets
	void SetVelocity(float velocity);
	void SetVacceleration(float vacceleration);

	//gets
	float GetVelocity();
	float GetVacceleration();
protected:

private:
	float velocity = 0;
	float vacceleration = 0;
	float gravity = 10;


};

