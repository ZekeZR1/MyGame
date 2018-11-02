#include "stdafx.h"
#include "GameScene.h"
#include "Title.h"
#include "TestScene.h"

//Global
IScene* currentScene = nullptr;

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	//Initialize
	//InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	Engine::IEngine().Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	currentScene = new Title;
	//NewGO<TestScene>(0,nullptr);
	//MainRoop
	Engine::IEngine().GameRoop();
	//Release
	Engine::IEngine().Final();
}
