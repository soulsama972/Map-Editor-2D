#include"Overlay.hpp"
#include"Window.hpp"
#include<random>
#include"MapEditor.hpp"
#include"Texture2D.hpp"
#pragma warning (push)
#pragma warning (disable : 28251)




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	Window bShooter;
	bShooter.Init(L"bubbleShooter", 1600, 900);
	Texture2D::Bind(&bShooter);
	Camera camera;
	camera.Bind(&bShooter);
	camera.Init(1600, 900, 0.1f, 1000.0f);
	camera.Update(fVec3(0, 2500, -10));

	while (bShooter.LoopEvent())
	{
		fVec3 camPos = camera.GetPos();
		if (bShooter.IsKeyPress(Key::Key_D))
			camPos.x += 10.01f;
		if (bShooter.IsKeyPress(Key::Key_A))
			camPos.x -= 10.01f;
		if (bShooter.IsKeyPress(Key::Key_S))
			camPos.y += 10.01f;
		if (bShooter.IsKeyPress(Key::Key_W))
			camPos.y -= 10.01f;
		camera.Update( camPos);
		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });
		bShooter.Render(true);
	}
	return 0;
}

#pragma warning(pop)

