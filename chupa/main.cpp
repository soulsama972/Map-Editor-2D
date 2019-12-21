#include"Overlay.hpp"
#include"Window.hpp"
#include<random>
#include"MapEditor.hpp"
#include"Object.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#pragma warning (push)
#pragma warning (disable : 28251)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{

	Window bShooter;
	

	bShooter.Init(L"bubbleShooter", 800, 600);
	Texture2D::Bind(&bShooter);
	Object::Bind(&bShooter);
	Texture2D t("b.png",5000);
	Entity entity;
	Player player;
	Physics phy;
	phy.Init(10, 10);

	entity.Init({ 100,100 }, &t, { 200,200,0 }, {0,0,0},phy,false, true ,10,0);
	player.Init({ 100,100 }, &t, { 300,200,0 }, { 0,0,0 }, phy, false, true, 10, 0);
	
	/*MapEditor* m = new MapEditor(&bShooter, { 300,300,0 });
	m->SetTexture(&t);
	while (m->Update())
	{
		m->Draw();
	}*/

	while (bShooter.LoopEvent())
	{
		player.Motion(0.56,entity);
		fVec3 posPlayer = player.GetPosition();
		fVec2 sizePlayer = player.GetSize();

		entity.AutoMotion(0.56, player);
		fVec3 pos = entity.GetPosition();
		fVec2 size = entity.GetSize();

		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });
		t.AddInstance({ pos.x, pos.y,size.x,size.y});
		t.AddInstance({ posPlayer.x, posPlayer.y,sizePlayer.x,sizePlayer.y });
		t.Draw();
		bShooter.Render(true);
	}
	return 0;
}

#pragma warning(pop)

