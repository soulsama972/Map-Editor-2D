#pragma once
#include "Math.hpp"
#include "Textrue2D.hpp"

class Object
{
public:
	Object(fVec2 size,bool isDestroyable);
	Object() = default;
	void SetSize(fVec2 size);
	void SetIsDestroyable(bool isDestroyable);
protected:

private:
	
	fVec2 size;
	bool isDestroyable = false;
	Textrue2D* textrue = nullptr;
	//Physics EntityPhysics;

};

