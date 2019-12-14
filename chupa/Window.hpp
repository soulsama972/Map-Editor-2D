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
	void Init(const wchar_t* className, vec2<float> screenRes);
	void UpdateScreen(const fVec2& screensize);

<<<<<<< HEAD
	ID3D11Device* GetDevice() const;
=======
	ID3D11Device* GetDeovce() const;
	fVec2* GetScreen();

	Timer timer;
>>>>>>> a1299912828782dc60d5cdf84eb7dfba028dd530
private:
	void OnResize(int width,int height) override;
	void OnQuitMsg() override;

	void InitD3D();

	inline fVec2 GetScale(fVec2 s);

	inline fVec2 GetTransalte(fVec2 t, fVec2 c);

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

inline fVec2 Window::GetScale(fVec2 s)
{
	return fVec2(s.x / screen.x, s.y / screen.y);
}

inline fVec2 Window::GetTransalte(fVec2 t, fVec2 c)
{
	return fVec2((t.x + c.x / 2) * 2 / screen.x - 1, 1 - 2 * (t.y + c.y / 2) / screen.y);
}

inline ID3D11Device* Window::GetDevice()const
{
	return dev;
}

inline fVec2* Window::GetScreen() 
{
	return &screen;
}
