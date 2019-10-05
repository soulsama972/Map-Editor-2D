#include "Overlay.hpp"

#define SafeDelete(x) if (x) {x->Release(); x = nullptr;}

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
			setScreenSize(fVec2(LOWORD(lParam), HIWORD(lParam)));
			for (int y = 0; y < 500; y++)
			{
				for (int x = 0; x < 98; x++)
				{
					VertexInstance in;
					in.color =  fVec4(0, 0, 0, 1);
					in.size = GetScale(fVec2(10,10));
					in.position = GetTransalte(fVec2(x * 10 + 10, y * 20 + 10), fVec2(10, 10));
					
					fCircle.ChangeInstance(x + y * 98,in);
				}
			}
			fCircle.UpdateModel();
		}
	}
	break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}



Overlay::Overlay(int with,int height)
{
	pThis = this;
	hInstance = GetModuleHandle(nullptr);
	screen = fVec2(with, height);
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
		0, 0,r.right - r.left,r.bottom - r.top,NULL,NULL, hInstance, NULL);


	ShowWindow(hwnd,SW_SHOW);
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

	line.CleanUp();
	rect.CleanUp();
	circle.CleanUp();
}

void Overlay::InitD3D()
{
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                   // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
	scd.BufferDesc.Width = static_cast<UINT>(screen.x);                   // set the back buffer width
	scd.BufferDesc.Height = static_cast<UINT>( screen.y);                 // set the back buffer height
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
	scd.OutputWindow = hwnd;                               // the window to be used
	scd.SampleDesc.Count = 8;                              // how many multisamples
	scd.Windowed = TRUE;                                   // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH ;    // allow full-screen switching
														   // create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&dev,
		NULL,
		&devcon);
	// get the address of the back buffer
	ID3D11Texture2D* pBackBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);

	// use the back buffer address to create the render target
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backBuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	devcon->OMSetRenderTargets(1, &backBuffer, NULL);


	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = screen.x;
	viewport.Height = screen.y;
	devcon->RSSetViewports(1, &viewport);
	rdy = true;
}

void Overlay::InitShapes()
{
	//rect
	VertexType vertex[] =
	{
		{{-1.0f,-1.0f,1.0f}},
		{{-1.0f,1.0f,1.0f}},
		{{1.0f,1.0f,1.0f}},
		{{1.0f,-1.0f,1.0f}},
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
		{fVec3(-1.0f,1.0f,1.0f)},
		{fVec3(1.0f,-1.0f,1.0f)},
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
		VertexCircle[i].position = fVec3(cosf(Theta), sinf(Theta), 1.0f);
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
	fCircle.InitBuffer(dev, devcon, VertexCircle, numVertex, indircle, numVertex*3, 5000, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	
	
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

void Overlay::setScreenSize(fVec2 screensize)
{
	screen = screensize;
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = screen.x;
	viewport.Height = screen.y;


	if (SUCCEEDED(backBuffer->Release()) && 
		SUCCEEDED(swapChain->ResizeBuffers(0,static_cast<UINT>( screen.x),
			static_cast<UINT>(screen.y), DXGI_FORMAT_R8G8B8A8_UNORM, 0)))
	{
		ID3D11Texture2D* pBackBuffer;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);

		// use the back buffer address to create the render target
		dev->CreateRenderTargetView(pBackBuffer, NULL, &backBuffer);
		pBackBuffer->Release();
		devcon->OMSetRenderTargets(1, &backBuffer, nullptr);

	}
	devcon->RSSetViewports(1, &viewport);

}

void Overlay::ClearTargetView(fVec4 color)
{
	devcon->ClearRenderTargetView(backBuffer, color.ToPointer());
}

void Overlay::Draw(bool cleanAfterDraw)
{
	rect.Draw();
	line.Draw();
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
	VertexInstance in;
	in.color = color;
	in.size = GetScale(p2 -p1);
	in.position = GetTransalte(p1, p2 - p1);
	line.AddInstance(in);
}

void Overlay::InsertCircle(fVec2 pos, float rad, fVec4 color, bool filled)
{
	fVec2  c = fVec2(rad, rad);
	VertexInstance in;
	in.color = color;

	in.size = GetScale(c);
	in.position = GetTransalte(pos,c);
	if(filled)
		fCircle.AddInstance(in);
	else
		circle.AddInstance(in);
}

void Overlay::InsertRect(fVec2 pos, fVec2 size, fVec4 color)
{
	VertexInstance in;
	in.color = color;
	in.size = GetScale(size);
	in.position = GetTransalte(pos, size);
	rect.AddInstance(in);
}





