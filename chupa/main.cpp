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

template<typename T>
class V
{
public:
	T x,y,z;
};

template<typename T>
class V2
{
public:
	T x,y,z,w;
};



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{

	Window bShooter;
	
	 
	bShooter.Init(L"bubbleShooter", 1600, 900);
	Texture2D::Bind(&bShooter);
	Object::Bind(&bShooter);
	Texture2D t("b.png",10000);
	Texture2D t2("b2.png", 10000);
	Texture2D *tex[2];
	tex[0] = &t;
	tex[1] = &t2;
	Entity entity;
	Player player;
	Physics phy;
	Camera camera;
	World world;
	camera.Bind(&bShooter);
	world.tex = &t;
	world.LoadMap("map1");
	camera.Init(1600, 900, 0.1f, 1000.0f);
	phy.Init(10, 10);
	camera.Update(fVec3(0, 2500, -10));
	entity.Init({ 100,100 }, &t, { 200,200,0 }, {0,0,0},phy,false, true ,10,0);
	player.Init({ 100,100,10 }, &t2, { 0.0f,world.screenMap.y-200.0f,1.0f}, { 0,0,0 }, phy, false, true, 10, 0);
	

	while (bShooter.LoopEvent())
	{
		player.Motion(0.56f,entity);
		fVec3 posPlayer = player.GetPosition();
		fVec3 sizePlayer = player.GetSize();

		entity.AutoMotion(0.56f, player);
		fVec3 pos = entity.GetPosition();
		fVec3 size = entity.GetSize();

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
			m->SetTexture(tex, 2);
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
		camera.Update( player.GetPosition() - fVec3(0,0,10));
		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });
		t2.AddInstance(player.GetPosition(), player.GetSize().ToVec3(), camera);
		t.Draw();
		t2.Draw();
		world.Draw(camera);
		bShooter.Render(true);
	}


	return 0;
}

#pragma warning(pop)

