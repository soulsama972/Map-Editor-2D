#pragma once
#pragma warning (push)
#pragma warning (disable : 26495)
#pragma warning (disable : 4005)

#pragma warning(pop)


#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")

#pragma comment(lib,"d3d10.lib")
#pragma comment(lib,"d3dx10.lib")

#include"Model.hpp"

#include"EventHandler.hpp"

class Window : public EventHandler
{
public:
	Window() = default;
	~Window();

	void ClearTargetView(fVec4 color);

	void Render(bool sync = false);

	void SetRasterizer(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, bool multiSample = true, bool antialiasedLine = true);

	void Init(const wchar_t * className, int width, int height);
	void Init(const wchar_t* className, fVec2 screenRes);
	void UpdateScreen(const fVec2& screensize);

	ID3D11Device* GetDevice() const;

	ID3D11DeviceContext *GetContext()const;

	fVec2 GetScreen() const;


private:
	void OnResize(int width,int height) override;
	void OnQuitMsg() override;

	void InitD3D();

	void CreateSwapChain();
	void CreateBackBuffer();
	void CreateDpethStencil();
	void CreateDepthStencilView();
	void CreateRasterizer(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, bool multiSample = true, bool antialiasedLine = true); 

	fVec2 screen;
	ID3D11Device* dev = nullptr;
	ID3D11DeviceContext* devcon = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* backBuffer = nullptr;
	ID3D11DepthStencilState* depthStencil = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;
	ID3D11RasterizerState* raster = nullptr;
	HINSTANCE hInstance = 0;
	D3D11_VIEWPORT viewport = {0};
	
	wchar_t* className = 0;

};


inline ID3D11Device* Window::GetDevice()const
{
	return dev;
}

inline ID3D11DeviceContext* Window::GetContext() const
{
	return devcon;
}

inline fVec2 Window::GetScreen() const
{
	return screen;
}

