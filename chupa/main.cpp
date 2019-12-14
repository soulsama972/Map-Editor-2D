#include"Overlay.hpp"
#include"Window.hpp"
#include<random>
#pragma warning (push)
#pragma warning (disable : 28251)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	Window bShooter;
	
	bShooter.Init(L"bubbleShooter", 800, 600);
	while (bShooter.LoopEvent())
	{
		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });

		bShooter.Render();
	}
	return 0;
}

#pragma warning(pop)

