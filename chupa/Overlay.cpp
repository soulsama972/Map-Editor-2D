#include "Overlay.hpp"


Overlay * Overlay::pThis = 0;
LRESULT Overlay::WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return pThis->WndProc(hwnd, msg, wParam, lParam);
}

LRESULT Overlay::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}break;
	case WM_SIZE:
	{
		if (rdy)
		{
			UpdateScreen(fVec2(LOWORD(lParam), HIWORD(lParam)));
			
		}
	}
	break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


Overlay::Overlay(int with, int height)
{
	pThis = this;
	hInstance = GetModuleHandle(nullptr);
	screen = fVec2(with, height);
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Overlay::WinProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);
	RECT r;
	SetRect(&r, 0, 0, static_cast<int>(screen.x), static_cast<int>(screen.y));
	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);

	hwnd = CreateWindowEx(NULL, L"WindowClass", L"chupa", WS_OVERLAPPEDWINDOW,
		0, 0, r.right - r.left, r.bottom - r.top, NULL, NULL, hInstance, NULL);


	ShowWindow(hwnd, SW_SHOW);
	InitD3D();
	InitShapes();

}

Overlay::~Overlay()
{
	UnregisterClass(L"WindowClass", hInstance);
	SafeDelete(backBuffer);
	SafeDelete(dev);
	SafeDelete(devcon);
	SafeDelete(swapChain);
	SafeDelete(depthStencil);
	SafeDelete(depthStencilView);
	SafeDelete(raster);
	line.CleanUp();
	rect.CleanUp();
	circle.CleanUp();
	fCircle.CleanUp();
}



void Overlay::CreateSwapChain()
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
		&devcon));
}

void Overlay::CreateBackBuffer()
{
	// get the address of the back buffer
	ID3D11Texture2D* pBackBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);

	// use the back buffer address to create the render target
	CheckFAILED(dev->CreateRenderTargetView(pBackBuffer, NULL, &backBuffer));
	pBackBuffer->Release();
}

void Overlay::CreateDpethStencil()
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

	CheckFAILED(dev->CreateDepthStencilState(&dsDesc, &depthStencil));
}

void Overlay::CreateDepthStencilView()
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
	CheckFAILED(dev->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

	// create view of depth stensil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	descDSV.Texture2D.MipSlice = 0u;
	CheckFAILED(dev->CreateDepthStencilView(pDepthStencil, &descDSV, &depthStencilView));
	SafeDelete(pDepthStencil);
}

void Overlay::CreateRasterizer(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, bool multiSample, bool antialiasedLine)
{
	CD3D11_RASTERIZER_DESC rastDesc(fillMode, cullMode, FALSE,
		D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
		D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE, FALSE, multiSample, antialiasedLine);
	CheckFAILED(dev->CreateRasterizerState(&rastDesc, &raster));
}


void Overlay::InitD3D()
{
	CreateSwapChain();

	CreateBackBuffer();

	CreateDpethStencil();

	CreateDepthStencilView();

	SetRasterizer(D3D11_FILL_MODE::D3D11_FILL_SOLID, D3D11_CULL_NONE);
	rdy = true;

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

void Overlay::InitShapes()
{
	//rect
	VertexType vertex[] =
	{
		{{-1.0f,-1.0f,0.0f}},
		{{-1.0f,1.0f,0.0f}},
		{{1.0f,1.0f,0.0f}},
		{{1.0f,-1.0f,0.0f}},
	};

	unsigned int ind[] =
	{
		0,1,2,
		0,2,3
	};
	rect.InitBuffer(dev, devcon, vertex, 4, ind, 6, 5000, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//line
	VertexType VertexLine[] =
	{
		{fVec3(-1.0f,1.0f,0.0f)},
		{fVec3(1.0f,-1.0f,0.0f)},
	};
	unsigned int indLine[] =
	{
		0,1
	};
	line.InitBuffer(dev, devcon, VertexLine, 2, ind, 2, 5000, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//filled circle
	const int numPoint = 72;
	const int numVertex = numPoint;
	float doublePi = 2.0f * PI;

	VertexType VertexCircle[numVertex];
	unsigned int indircle[(numVertex -1)* 3];
	for (int i = 0; i < numVertex; i++)
	{
		float Theta = i * doublePi / numPoint;
		VertexCircle[i].position = fVec3(cosf(Theta), sinf(Theta), 0.0f);
	}
	for (int i = 0; i < (numVertex-1) * 3; i++)
	{
		if(i < 3)
			indircle[i] = i;

		else if (i % 3 == 0)
			indircle[i] = 0;
		else if (i % 3 == 1)
			indircle[i] = indircle[i-2];
		else if (i % 3 == 2)
			indircle[i] = indircle[i - 1] + 1;
	}
	fCircle.InitBuffer(dev, devcon, VertexCircle, numVertex, indircle, (numVertex-1)*3, 5000, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	
	//hallow circle

	unsigned int hallowCrircleInd[numVertex+1];
	for (int i = 0; i < numVertex; i++)
	{
		float Theta = i * doublePi / numPoint;
		VertexCircle[i].position = fVec3(cosf(Theta), sinf(Theta), 1.0f);
		hallowCrircleInd[i] = i;
	}	
	hallowCrircleInd[numVertex] = 0;
	circle.InitBuffer(dev, devcon, VertexCircle, numVertex, hallowCrircleInd, numVertex+1, 5000, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
}

void Overlay::UpdateScreen(fVec2 screensize)
{
	if (screensize.GetLength() == 0)
		return;
	screen = screensize;
	viewport.Width = screen.x;
	viewport.Height = screen.y;

	SafeDelete(backBuffer);
	SafeDelete(depthStencil);
	SafeDelete(depthStencilView);
	CheckFAILED(swapChain->ResizeBuffers(0, static_cast<UINT>(screen.x), static_cast<UINT>(screen.y), DXGI_FORMAT_R8G8B8A8_UNORM, 0));


	CreateBackBuffer();
	CreateDpethStencil();
	CreateDepthStencilView();
	devcon->OMSetRenderTargets(1, &backBuffer,depthStencilView);

	devcon->RSSetViewports(1, &viewport);

}

void Overlay::ClearTargetView(fVec4 color)
{
	devcon->ClearRenderTargetView(backBuffer, color.ToPointer());
	devcon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0u);
}

void Overlay::Draw(bool cleanAfterDraw)
{
	line.Draw();
	rect.Draw();
	circle.Draw();
	fCircle.Draw();

	if (cleanAfterDraw)
	{
		rect.ClearInstance();
		line.ClearInstance();
		circle.ClearInstance();
		fCircle.ClearInstance();
	}
}

void Overlay::Render()
{
	swapChain->Present(0, 0);
}

void Overlay::InsertLine(fVec2 p1, fVec2 p2, fVec4 color)
{
	Matrix4x4 s;
	VertexInstance in;
	in.color = color;
	in.normal = fVec3(0, 0, -1);

	fVec2 scale = GetScale(p2 -p1);
	fVec2 translate = GetTransalte(p1, p2 - p1);

	in.matrix.Translate(fVec3(translate.x, translate.y, 0.0f).ToPointer());
	s._11 = scale.x;
	s._22 = scale.y;

	in.matrix = in.matrix * s;

	line.AddInstance(in);
}

void Overlay::InsertCircle(fVec2 pos, float rad, fVec4 color, bool filled)
{
	Matrix4x4 s;
	fVec2  c = fVec2(rad, rad);
	VertexInstance in;
	in.color = color;
	in.normal = fVec3(0.0, 0.4, -0.1);

	fVec2 scale = GetScale(c);
	fVec2 translate = GetTransalte(pos,c);

	in.matrix.Translate(fVec3(translate.x, translate.y, 0.0f).ToPointer());
	s._11 = scale.x;
	s._22 = scale.y;

	in.matrix = in.matrix * s;

	if(filled)
		fCircle.AddInstance(in);
	else
		circle.AddInstance(in);
}

void Overlay::InsertRect(fVec2 pos, fVec2 size, fVec4 color)
{
	Matrix4x4 s;
	VertexInstance in;
	in.color = color;
	in.normal = fVec3(0, 0, -1);
	fVec2 scale = GetScale(size);
	fVec2 translate = GetTransalte(pos, size);

	in.matrix.Translate(fVec3(translate.x, translate.y, 0.0f).ToPointer());
	s._11 = scale.x;
	s._22 = scale.y;
	in.matrix = in.matrix * s;
	rect.AddInstance(in);
}

void Overlay::SetRasterizer(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, bool multiSample, bool antialiasedLine)
{
	SafeDelete(raster);
	CreateRasterizer(fillMode, cullMode, multiSample, antialiasedLine);
	devcon->RSSetState(raster);
}




