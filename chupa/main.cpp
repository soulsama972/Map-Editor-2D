#include"Overlay.hpp"
#include"Window.hpp"
#include<random>

#pragma warning (push)
#pragma warning (disable : 28251)

class q  : public Window
{
public:
	q();
};
q* qq;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	qq = new q();
	qq->Init(L"test",800, 600);
	Overlay *overlay = new Overlay(800,600);

	srand(static_cast<unsigned int>(time(NULL)));
	overlay->timer.Start();
	if (overlay)
	{	
		MSG msg;
		int th = 5;
		int  scale = 20;
		vec2<int> pos = vec2<int>(200, 10);
		overlay->InsertRect({ pos.x,pos.y}, {scale * 17 +10,th }, fVec4(1, 1, 1, 1));//top
		overlay->InsertRect({ 200 ,scale * 17 + th }, { scale * 17 +10,th }, fVec4(1, 1, 1, 1));//bot
		
		overlay->InsertRect({ 200-th,10 }, { th ,scale * 17 }, fVec4(1, 1, 1, 1));//left
		overlay->InsertRect({ 200  + scale * 17 + 10,10 }, { th ,scale * 17 }, fVec4(1, 1, 1, 1));//right

		overlay->InsertRect({ 200 + 160,500 }, { 5 ,60 }, fVec4(1, 1, 1, 1));
		overlay->InsertRect({ 200 + 160,500 }, { 5 ,60 }, fVec4(1, 1, 1, 1));
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 17; j++)
			{				
				fVec2  pos(i % 2 == 0 ? 200 + j * scale : 210 + j * scale,20 + i * scale);
				fVec4 color;
				int rng = rand() % 3;
				if (rng == 1)
					color = fVec4(1, 0, 0, 1);
				else if (rng == 2)
					color = fVec4(0.0, 0.7, 0.0, 1.0);
				else
					color = fVec4(0, 0, 1, 1);

				overlay->InsertCircle(pos, scale, color);
			}
		}
		overlay->InsertCircle({ 200,200 }, 300, { 0,0,1,1 });
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

				overlay->ClearTargetView(fVec4(0.3f, 0.3f, 0.3f, 1.0f));

				overlay->Draw(false);
				overlay->timer.Restart();
				overlay->Render();
			}
		}	
	}
	delete qq;
	delete overlay;
	return 0;
}

#pragma warning(pop)

q::q()
{

}
