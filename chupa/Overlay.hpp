#pragma once
#include"Model.hpp"
#include"utill.hpp"
#pragma warning (push)
#pragma warning (disable : 26495)
#pragma warning (disable : 4005)

#pragma warning(pop)


#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")

#pragma comment(lib,"d3d10.lib")
#pragma comment(lib,"d3dx10.lib")
class Overlay
{
private:
	//struct CONSTBUFFER
	//{
	//	D3DXMATRIX proj;
	//	D3DXMATRIX view;
	//	D3DXMATRIX world;
	//};
public:
	static LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

	Overlay(int with, int height);
	~Overlay();

	void InitD3D();
	
	void ClearTargetView(fVec4 color);
	void Draw(bool cleanAfterDraw = true);
	void Render();

	void UpdateScreen(fVec2 screensize);

	void InsertLine(fVec2 p1, fVec2 p2, fVec4 color);
	void InsertCircle(fVec2 pos, float rad, fVec4 color,bool filled = true);
	void InsertRect(fVec2 pos, fVec2 size, fVec4 color);

	void SetRasterizer(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, bool multiSample = true, bool antialiasedLine = true);
private:
	inline fVec2 GetScale(fVec2 s)
	{
		return fVec2(s.x / screen.x, s.y / screen.y);
	}

	inline fVec2 GetTransalte(fVec2 t,fVec2 c)
	{
		return fVec2((t.x + c.x / 2) * 2 / screen.x - 1, 1 - 2 * (t.y + c.y / 2) / screen.y);
	}

	void InitShapes();
	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void CreateSwapChain();
	void CreateBackBuffer();
	void CreateDpethStencil();
	void CreateDepthStencilView();
	void CreateRasterizer(D3D11_FILL_MODE fillMode,D3D11_CULL_MODE cullMode,bool multiSample = true,bool antialiasedLine = true);
public:
	bool rdy = false;
	Timer timer;
private:
	fVec2 screen;
	ID3D11Device* dev = nullptr;
	ID3D11DeviceContext* devcon = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* backBuffer = nullptr;
	ID3D11DepthStencilState* depthStencil = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;
	ID3D11RasterizerState* raster = nullptr;
	Model11<VertexInstance>rect;
	Model11<VertexInstance>line;
	Model11<VertexInstance>circle;
	Model11<VertexInstance>fCircle;
	HINSTANCE hInstance = 0;
	HWND hwnd = 0;
	D3D11_VIEWPORT viewport;
	static Overlay* pThis;
};
