#include "stdafx.h"

HWND g_hwnd = NULL;
GraphicsEngine* g_graphicsEngine = NULL;


LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

void InitWindow(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow,
	const TCHAR* appName){
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		MsgProc,
		0,
		0,
		GetModuleHandle(NULL),
		NULL,
		NULL,
		NULL,
		NULL,
		appName,
		NULL
	};

	RegisterClassEx(&wc);

	g_hwnd = CreateWindow(
		appName,
		appName,
		WS_OVERLAPPEDWINDOW,	
		0,					
		0,					
		1280,					
		720,					
		NULL,	
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(g_hwnd, nCmdShow);

	//DirectX
	g_graphicsEngine = new GraphicsEngine();
	g_graphicsEngine->InitDirectX(g_hwnd);
	//Bullet
	g_physics.Init();
	//Pad
	g_pad[0].Init(0);
	g_pad[1].Init(1);
	g_pad[2].Init(2);
	g_pad[3].Init(3);
}


bool DispatchWindowMessage() {
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			break;
		}
	}
	return msg.message != WM_QUIT;
}
