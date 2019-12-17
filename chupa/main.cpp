#include"Overlay.hpp"
#include"Window.hpp"
#include<random>
#include"MapEditor.hpp"
#include"Object.hpp"
#pragma warning (push)
#pragma warning (disable : 28251)


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{

	Window bShooter;
	

	bShooter.Init(L"bubbleShooter", 800, 600);
	Texture2D::Bind(&bShooter);
	Object::Bind(&bShooter);
	Texture2D t("b.png",5000);
	Object obj;
	Physics phy(10, 10);
	obj.Init({ 100,100 }, &t, { 200,200,0 }, { 0,0,0 },&phy, true);
	
	/*MapEditor* m = new MapEditor(&bShooter, { 300,300,0 });
	m->SetTexture(&t);
	while (m->Update())
	{
		m->Draw();
	}*/

	while (bShooter.LoopEvent())
	{
		obj.Update(0.56);
		fVec3 pos = obj.GetPosition();
		fVec2 size = obj.GetSize();
		bShooter.ClearTargetView({ 0.2,0.2,0.2,1.0 });
		t.AddInstance({ pos.x, pos.y,size.x,size.y});
		t.Draw();
		bShooter.Render(true);
	}
	return 0;
}

#pragma warning(pop)

