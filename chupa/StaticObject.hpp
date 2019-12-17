#pragma once
#include "Math.hpp"
#include "Texture2D.hpp"
#include "Physics.hpp"
class StaticObject
{
public:
	StaticObject() = default;
	void Init(fVec2 size, Texture2D* texture, fVec3 position, fVec3 origin);

	//sets
	void SetSize(fVec2 size);
	void SetTexture(Texture2D* texture);
	void SetPosition(fVec3 position);
	void SetOrigin(fVec3 origin);

	//gets
	fVec2 GetSize();
	Texture2D* GetTexture();
	fVec3 GetPosition();
	fVec3 GetOrigin();
protected:
private:
	fVec2 size = { 0,0 };
	fVec3 position = { 0,0,0 };
	fVec3 origin = { 0,0,0 };
	Texture2D* texture = nullptr;
};

