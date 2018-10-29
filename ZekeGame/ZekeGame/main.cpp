#include "stdafx.h"
#include "GameScene.h"
#include "Title.h"
#include "FPSCounter.h"
#include "TestScene.h"

//Global
IScene* currentScene = nullptr;
GameCamera* camera = nullptr;
CFPSCounter* FPS = nullptr;

void ReleaseDirectX() {
	delete g_graphicsEngine;
	delete camera;
	delete FPS;
}

void GameUpdate() {
	for (auto& pad : g_pad) {
		pad.Update();
	}

	//currentScene->Update();

	GameObjectManager().Execute();

	//output frame late to debug message
	char message[256];
	float fps = FPS->GetFPS();
	sprintf_s(message, "%f\n", fps);
	OutputDebugStringA(message);
}

void Render() {
	//g_graphicsEngine->BegineRender();
	//currentScene->Draw();
	//g_graphicsEngine->EndRender();
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	//currentScene = new Title;
	NewGO<TestScene>(0,nullptr);
	camera = new GameCamera;
	FPS = new CFPSCounter(10);
	while (DispatchWindowMessage()) {
		GameUpdate();
		Render();
	}
}
