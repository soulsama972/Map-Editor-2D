#include"Overlay.hpp"
#include"utill.hpp"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	Overlay *overlay = new Overlay(1000,800);
	Timer timer;
	timer.Start();
	int fps = 0;
	if (overlay)
	{
		for (int y = 0; y < 500; y++)
		{
			for (int x = 0; x < 98; x++)
			{
				overlay->InsertCircle(fVec2(x * 10 + 10, y * 20 + 10), 10, fVec4(0, 0, 0, 1), true);
			}
		}
		
		MSG msg;
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
			
				

				//overlay->InsertRect(fVec2(100, 2), fVec2(200,200), fVec4(0, 0, 0, 1));
				//overlay->InsertLine(fVec2(0, 0), fVec2(800,600), fVec4(1, 0, 0, 1));
				overlay->ClearTargetView(fVec4(0.0f, 0.0f, 0.5f, 1.0f));
				overlay->Draw(false);
				fps++;
				if (timer.GetMilisecondsElapsed() > 1000.0f)
				{
					std::string fString = "FPS: " + std::to_string(fps) +"\n";
					OutputDebugStringA(fString.c_str());
					fps = 0;
					timer.Restart();
				}
				
				overlay->Render();
				
			}
		}	
	}
	delete overlay;
	return 0;
}