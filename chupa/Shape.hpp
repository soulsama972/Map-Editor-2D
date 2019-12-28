#pragma once
#include<string>
#include"Window.hpp"
#include"Model.hpp"
#include"Camera.hpp"


struct ShapeInstance
{
	fVec3 pos;
	fVec3 size;
};

struct ShapeVertex
{
	fVec3 pos;
};



class Shape : private Model11<ShapeInstance>
{
public:
	inline static void Bind(Window* window)
	{
		Shape::window = window;
	}
	void AddInstance(const fVec3& pos, const fVec3& size, const Camera& camera);
	void Draw(bool clearAfter = true);

	inline void Clear()
	{
		ClearInstance();
	}
	
private:

	static Window* window;
	void WrapInitBuffer();
	void WrapInitShader();

};

