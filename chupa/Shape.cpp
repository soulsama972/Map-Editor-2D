#include "Shape.hpp"

Window* Shape::window = nullptr;

void Shape::AddInstance(const fVec3& pos, const fVec3& size, const Camera& camera)
{
	//TextrueInstanceType in;
	fVec3 cameraPos = camera.GetPos();
	fVec2 screen = camera.GetScreen();

	fVec3 screenWorld = (pos - cameraPos.ToNegativeY()).TransfromV3(camera.GetProjMatrix());
	screenWorld.x = screenWorld.x * (screen.x / 2) - (screen.x / 2);
	screenWorld.y = -screenWorld.y * (screen.y / 2) + (screen.y / 2);
	screenWorld.z = size.z;


	//if (screenWorld.x + size.x < 0 || screenWorld.x - size.x> screen.x || screenWorld.y + size.y < -screen.y || screenWorld.y - size.y > 0) // cliping
	//	return;
	//in.pos = screenWorld;
	//in.size = size / 2;
	//Model11::AddInstance(in);
}

void Shape::Draw(bool clearAfter)
{
	const auto& devcon = window->GetContext();
	//devcon->PSSetShaderResources(0, 1, &textrue);
	//devcon->PSSetSamplers(0, 1, &sampleState);
	Model11::Draw();
	//devcon->PSSetShaderResources(0, 0, 0);
	//devcon->PSSetSamplers(0, 0, 0);
	if (clearAfter)
		ClearInstance();
}
