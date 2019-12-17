#include"Overlay.hpp"
#include"Window.hpp"
#include<random>
#include"MapEditor.hpp"
#pragma warning (push)
#pragma warning (disable : 28251)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{

	Window bShooter;
	

	bShooter.Init(L"bubbleShooter", 800, 600);
	Texture2D::Bind(&bShooter);
	Texture2D t("b.png",5000);
	MapEditor* m = new MapEditor(&bShooter, { 300,300,0 });
	m->SetTexture(&t);
	while (m->Update())
	{
		m->Draw();
	}
	while (bShooter.LoopEvent())
	{
		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });
		t.AddInstance({ 0,0,200,200 });
		t.AddInstance({ 300,0,200,200 });
		t.Draw();
		bShooter.Render();
	}
	return 0;
}

#pragma warning(pop)

