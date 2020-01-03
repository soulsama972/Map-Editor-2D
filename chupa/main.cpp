#include"Overlay.hpp"
#include"Window.hpp"
#include<random>
#include"MapEditor.hpp"
#include"Object.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include"World.hpp"
#pragma warning (push)
#pragma warning (disable : 28251)




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	Window bShooter;
	bShooter.Init(L"bubbleShooter", 1600, 900);
	Texture2D::Bind(&bShooter);
	Object::Bind(&bShooter);
	Camera camera;
	World world;
	camera.Bind(&bShooter);
	world.LoadMap("map1");
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
		if (bShooter.IsKeyPress(Key::Key_F2))
		{
			MapEditor* m = new MapEditor(&bShooter, { 2500,2500,-10 });
			Sleep(1000);
			
			while (m->Update() && !bShooter.IsKeyPress(Key::Key_F1))
			{
				
				m->Draw();
			}
			SafeDeletePtr(m);
			world.ClearAll();
			world.LoadMap("map1");
			if (bShooter.IsWindowDestory())
				return 0;
		}
		camera.Update( camPos);

		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });

		world.Draw(camera);
		bShooter.Render(true);
	}


	return 0;
}

#pragma warning(pop)

