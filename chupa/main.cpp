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
		bShooter.UpdateScreen({ 800,600 });
		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });
		t.DrawObj({ 0,0,400,200 }, { 800, 600 });
		bShooter.Render();
	}
	return 0;
}

#pragma warning(pop)

