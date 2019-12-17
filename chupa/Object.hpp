#pragma once
#include "Math.hpp"
#include "Physics.hpp"
#include "StaticObject.hpp"


class Object : public StaticObject
{
public:
	Object() = default;

	void Init(fVec2 size, Texture2D* texture, fVec3 position, fVec3 origin, Physics* physics, bool isDestroyable);

	void Update(float deltaTime);
	//bind
	inline void Bind(Window* window)
	{
		this->window = window;
	}
	//sets
	void SetIsDestroyable(bool isDestroyable);
	void SetPhysics(Physics* physics);

	//gets
	bool GetIsDestroyable();
	Physics* GetPhysics();
protected:
private:
	bool isDestroyable = false;
	Physics* physics = nullptr;
	static Window* window;
};

