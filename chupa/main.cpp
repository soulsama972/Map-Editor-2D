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
	

	bShooter.Init(L"bubbleShooter", 800, 600);
	Texture2D::Bind(&bShooter);
	Object::Bind(&bShooter);
	Texture2D t("b.png",1000);
	Texture2D t2("b2.png", 1000);
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
	camera.Init(world.screenMap.x,world.screenMap.y , 1.0f, 1000.0f);
	phy.Init(10, 10);

	entity.Init({ 100,100 }, &t, { 200,200,0 }, {0,0,0},phy,false, true ,10,0);
	player.Init({ 100,100 }, &t2, { 0.0f,world.screenMap.y-200.0f,10.0f}, { 0,0,0 }, phy, false, true, 10, 0);
	
	/*MapEditor* m = new MapEditor(&bShooter, { 1500,800,1 });
	m->SetTexture(tex,2);
	while (m->Update())
	{
		m->Draw();
	}*/

	while (bShooter.LoopEvent())
	{
		player.Motion(0.56f,entity);
		fVec3 posPlayer = player.GetPosition();
		fVec2 sizePlayer = player.GetSize();

		entity.AutoMotion(0.56f, player);
		fVec3 pos = entity.GetPosition();
		fVec2 size = entity.GetSize();

		fVec3 camPos = camera.GetPos();

		camera.Update(fVec3(0,0,0));

		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });
		Matrix4x4 w;
		t2.Update(w, camera.view, camera.GetProjMatrix());
		t2.AddInstance(player.GetPosition(), player.GetSize().ToFVec3(), camera);
	//	t.AddInstance({ pos.x, pos.y,size.x,size.y});
	//	t.AddInstance({ posPlayer.x, posPlayer.y,sizePlayer.x,sizePlayer.y });
		t.Draw();
		t2.Draw();
		world.Draw(camera);
		bShooter.Render(true);
	}
	//SafeDeletePtr(m);

	return 0;
}

#pragma warning(pop)

