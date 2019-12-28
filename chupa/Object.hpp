#pragma once
#include "Math.hpp"
#include "Physics.hpp"
#include "StaticObject.hpp"


class Object : public StaticObject
{
public:
	Object() = default;

	void Init(fVec3 size, Texture2D* texture, fVec3 position, fVec3 origin, Physics physics, bool isDestroyable);
	void Update(float deltaTime);
	bool IsCollide(StaticObject anotherObj);

	//bind
	inline static void Bind(Window* window)
	{
		Object::window = window;
	}
	//sets
	void SetIsDestroyable(bool isDestroyable);
	void SetPhysics(Physics physics);

	//gets
	bool GetIsDestroyable();
	Physics GetPhysics();
protected:
	static Window* window;
private:
	bool isDestroyable = false;
	Physics physics;
	
};

