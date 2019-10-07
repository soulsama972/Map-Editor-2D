#include"Overlay.hpp"

#include<random>
#pragma warning (push)
#pragma warning (disable : 28251)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	Overlay *overlay = new Overlay(800,600);
	srand(time(NULL));
	overlay->timer.Start();
	if (overlay)
	{	
		MSG msg;
		overlay->InsertRect({200-10,10}, {200 + 140,10}, fVec4(0, 0, 0, 1));
		//overlay->InsertRect({ 200 - 10,320 + 20 }, { 200 - 10 + 140 ,20 }, fVec4(0, 0, 0, 1));
		
		overlay->InsertRect({ 200 - 10,20 }, { 10 ,10 +320}, fVec4(0, 0, 0, 1));
		overlay->InsertRect({ 200  + 320,20 }, { 10 ,10 + 320 }, fVec4(0, 0, 0, 1));

		overlay->InsertRect({ 200 + 160,500 }, { 5 ,60 }, fVec4(0, 0, 0, 1));
		overlay->InsertRect({ 200 + 160,500 }, { 5 ,60 }, fVec4(0, 0, 0, 1));
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				int  scale = 40;
				fVec2  pos(200 + j * scale,20 + i * scale);
				fVec4 color;
				int rng = rand() % 3;
				if (rng == 1)
					color = fVec4(1, 0, 0, 1);
				else if (rng == 2)
					color = fVec4(0, 1, 0, 1);
				else
					color = fVec4(0, 0, 1, 1);

				overlay->InsertCircle(pos, scale, color);
			}
		}

		while (TRUE)
		{		
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if (msg.message == WM_QUIT)
					break;
			}
			else
			{
				
				overlay->ClearTargetView(fVec4(0.0, 0.5, 1.0, 1.0));
				overlay->Draw(false);
				overlay->timer.Restart();
				overlay->Render();

			}
		}	
	}
	delete overlay;
	return 0;
}

#pragma warning(pop)