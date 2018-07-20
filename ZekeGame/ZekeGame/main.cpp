#include "stdafx.h"
#include "GameScene.h"
#include "Title.h"
//Global
IScene* currentScene = nullptr;
GameCamera* camera = nullptr;
/*
CVector3 modelPos = CVector3::Zero();
SkinModel smodel;
Animation modelanimation;
AnimationClip aniclip[1];
*/

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
	currentScene->DrawFont();
	g_graphicsEngine->EndRender();
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	/*
	smodel.Init(L"Assets/modelData/testbox.cmo");
	aniclip[0].Load(L"Assets/modelData/testbox.tka");
	aniclip[0].SetLoopFlag(true);
	modelanimation.Init(
		smodel,
		aniclip,
		1
		);
	*/
	currentScene = new Title;
	camera = new GameCamera;
	while (DispatchWindowMessage()) {
		GameUpdate();
		Render();
	}
}
