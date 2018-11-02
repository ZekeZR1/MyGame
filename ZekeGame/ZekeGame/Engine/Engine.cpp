#include "stdafx.h"
#include "Engine.h"
#include "Engine/FPSCounter.h"
#include "GameCamera.h"

CFPSCounter* FPS = nullptr;
GameCamera* camera = nullptr;

Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::Init(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	//SetCurrentDirectory("Resource");
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	GameObjectManager().Init(32);
	FPS = new CFPSCounter(10);
	//camera = new GameCamera;
}

void Engine::Release() {
	delete g_graphicsEngine;
	delete camera;
	delete FPS;
}

void Engine::Update() {
	for (auto& pad : g_pad) {
		pad.Update();
	}

	GameObjectManager().Execute();
	//camera->Update();
	//output frame late to debug message
	char message[256];
	float fps = FPS->GetFPS();
	sprintf_s(message, "%f\n", fps);
	OutputDebugStringA(message);
}

void Engine::GameRoop() {
	while (DispatchWindowMessage()) {
		Update();
	}
}

void Engine::Final() {
	Release();
}

