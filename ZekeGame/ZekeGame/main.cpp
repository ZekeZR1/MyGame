#include "stdafx.h"
#include "GameScene.h"
#include "Title.h"
#include "FPSCounter.h"

//Global
IScene* currentScene = nullptr;
GameCamera* camera = nullptr;
CFPSCounter* FPS = nullptr;

void ReleaseDirectX() {
	delete g_graphicsEngine;
	delete camera;
}

void GameUpdate() {
	for (auto& pad : g_pad) {
		pad.Update();
	}
	currentScene->Update();
}

void Render() {
	g_graphicsEngine->BegineRender();
	currentScene->Draw();
	g_graphicsEngine->EndRender();
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	currentScene = new Title;
	camera = new GameCamera;
	FPS = new CFPSCounter(10);
	while (DispatchWindowMessage()) {
		GameUpdate();
		Render();
	}
}
