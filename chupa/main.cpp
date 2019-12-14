#include"Overlay.hpp"
#include"Window.hpp"
#include<random>
#pragma warning (push)
#pragma warning (disable : 28251)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
<<<<<<< HEAD
	Window bShooter;
	
	bShooter.Init(L"bubbleShooter", 800, 600);
	

	while (bShooter.LoopEvent())
	{
		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });

=======
	

	Window bShooter;
	
	bShooter.Init(L"bubbleShooter", 800, 600);
	BubbleShooter* b = new BubbleShooter(bShooter.GetDeovce(),bShooter.GetScreen());
	while (bShooter.LoopEvent())
	{
		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });
		b->Draw();
>>>>>>> a1299912828782dc60d5cdf84eb7dfba028dd530
		bShooter.Render();
	}
	return 0;
}

#pragma warning(pop)

