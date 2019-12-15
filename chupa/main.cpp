#include"Overlay.hpp"
#include"Window.hpp"
#include<random>
#include"Textrue2D.hpp"
#pragma warning (push)
#pragma warning (disable : 28251)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{

	Window bShooter;
	

	bShooter.Init(L"bubbleShooter", 800, 600);
	Textrue2D t("b.png",bShooter.GetDevice(),bShooter.GetContext());

	
	while (bShooter.LoopEvent())
	{
		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });
		t.DrawObj({ 0,0,200,200 },bShooter.GetScreen());
		bShooter.Render();
	}
	return 0;
}

#pragma warning(pop)

