#include"Overlay.hpp"
#include"utill.hpp"


#pragma warning (push)
#pragma warning (disable : 28251)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	Overlay *overlay = new Overlay(800,600);
	Timer timer;
	timer.Start();
	int fps = 0;
	if (overlay)
	{	
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
			
				
				overlay->InsertCircle(fVec2(400, 200),400, fVec4(1, 0, 0, 1));
				overlay->InsertRect(fVec2(100, 2), fVec2(200,200), fVec4(0, 0, 0, 1));
				overlay->InsertLine(fVec2(0, 0), fVec2(800,600), fVec4(1, 1, 0, 1));
				overlay->ClearTargetView(fVec4(0.0f, 0.0f, 0.5f, 1.0f));
				overlay->Draw(true);
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

#pragma warning(pop)