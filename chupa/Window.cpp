#include "Window.hpp"


LRESULT WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	const Map* map = &EventHandler::map;
	EventHandler* handler = map->GetWindow(hwnd);
	if (handler)
		return handler->WndProc(hwnd, msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

Window::~Window()
{
	UnregisterClass(className, hInstance);
	SafeDelete(backBuffer);
	SafeDelete(dev);
	SafeDelete(devcon);
	SafeDelete(swapChain);
	SafeDelete(depthStencil);
	SafeDelete(depthStencilView);
	SafeDelete(raster);
}

void Window::Init(const wchar_t* className, int width, int height)
{
	hInstance = GetModuleHandle(nullptr);
	screen = fVec2(width, height);
	this->className = const_cast<wchar_t*>(className);
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = className;

	RegisterClassEx(&wc);
	RECT r;
	SetRect(&r, 0, 0, static_cast<int>(screen.x), static_cast<int>(screen.y));
	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);

	hwnd = CreateWindowExW(NULL, className, L"chupa", WS_OVERLAPPEDWINDOW,
		0, 0, r.right - r.left, r.bottom - r.top, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_SHOW);
	InitD3D();
	map.AddInstance(hwnd, this);
}

void Window::Init(const wchar_t* className, vec2<float> screenRes)
{
	hInstance = GetModuleHandle(nullptr);
	screen = screenRes;
	this->className = const_cast<wchar_t*>(className);
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = className;

	RegisterClassEx(&wc);
	RECT r;
	SetRect(&r, 0, 0, static_cast<int>(screen.x), static_cast<int>(screen.y));
	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);

	hwnd = CreateWindowEx(NULL, className, L"chupa", WS_OVERLAPPEDWINDOW,
		0, 0, r.right - r.left, r.bottom - r.top, NULL, NULL, hInstance, NULL);


	ShowWindow(hwnd, SW_SHOW);
	InitD3D();
	map.AddInstance(hwnd, this);
}




void Window::ClearTargetView(fVec4 color)
{
	devcon->ClearRenderTargetView(backBuffer, color.ToPointer());
	devcon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
}


void Window::Render(bool sync)
{
	swapChain->Present(sync, 0);
}

void Window::UpdateScreen(fVec2 screensize)
{
	screen = screensize;
	viewport.Width = screen.x;
	viewport.Height = screen.y;

	SafeDelete(backBuffer);
	SafeDelete(depthStencil);
	SafeDelete(depthStencilView);
	CheckFAILED(swapChain->ResizeBuffers(0, static_cast<UINT>(screen.x), static_cast<UINT>(screen.y), DXGI_FORMAT_R8G8B8A8_UNORM, 0))


	CreateBackBuffer();
	CreateDpethStencil();
	CreateDepthStencilView();
	devcon->OMSetRenderTargets(1, &backBuffer, depthStencilView);

	devcon->RSSetViewports(1, &viewport);
}

void Window::InitD3D()
{
	CreateSwapChain();

	CreateBackBuffer();

	CreateDpethStencil();

	CreateDepthStencilView();

	SetRasterizer(D3D11_FILL_MODE::D3D11_FILL_SOLID, D3D11_CULL_NONE);


	// bind depth state
	devcon->OMSetDepthStencilState(depthStencil, 1u);

	// bind depth stensil view to OM
	devcon->OMSetRenderTargets(1u, &backBuffer, depthStencilView);


	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.Width = screen.x;
	viewport.Height = screen.y;
	devcon->RSSetViewports(1, &viewport);
}


void Window::CreateSwapChain()
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                   // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
	scd.BufferDesc.Width = static_cast<UINT>(screen.x);                   // set the back buffer width
	scd.BufferDesc.Height = static_cast<UINT>(screen.y);                 // set the back buffer height
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
	scd.OutputWindow = hwnd;                               // the window to be used
	scd.SampleDesc.Count = 8u;                              // how many multisamples
	scd.SampleDesc.Quality = 0;
	scd.Windowed = TRUE;                                   // windowed/full-screen mode
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// create a device, device context and swap chain using the information in the scd struct
	CheckFAILED(D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		swapCreateFlags,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&dev,
		NULL,
		&devcon))
}

void Window::CreateBackBuffer()
{
	// get the address of the back buffer
	ID3D11Texture2D* pBackBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);

	// use the back buffer address to create the render target
	CheckFAILED(dev->CreateRenderTargetView(pBackBuffer, NULL, &backBuffer))
		pBackBuffer->Release();
}

void Window::CreateDpethStencil()
{
	// create depth stensil state
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	//// Stencil test parameters
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	CheckFAILED(dev->CreateDepthStencilState(&dsDesc, &depthStencil))
}

void Window::CreateDepthStencilView()
{
	// create depth stensil texture
	ID3D11Texture2D* pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};

	descDepth.Width = static_cast<UINT>(screen.x);
	descDepth.Height = static_cast<UINT>(screen.y);
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 8u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	CheckFAILED(dev->CreateTexture2D(&descDepth, nullptr, &pDepthStencil))

		// create view of depth stensil texture
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0u;
	CheckFAILED(dev->CreateDepthStencilView(pDepthStencil, &descDSV, &depthStencilView))
		SafeDelete(pDepthStencil);
}

void Window::CreateRasterizer(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, bool multiSample, bool antialiasedLine)
{
	CD3D11_RASTERIZER_DESC rastDesc(fillMode, cullMode, FALSE,
		D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
		D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE, FALSE, multiSample, antialiasedLine);
	CheckFAILED(dev->CreateRasterizerState(&rastDesc, &raster))
}

void Window::SetRasterizer(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, bool multiSample, bool antialiasedLine)
{
	SafeDelete(raster);
	CreateRasterizer(fillMode, cullMode, multiSample, antialiasedLine);
	devcon->RSSetState(raster);
}

