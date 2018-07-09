#include "stdafx.h"
#include "window/Window.h"

//Global
HWND g_hwnd = NULL;
GraphicsEngine* g_graphicsEngine = NULL;
Camera* camera2d = NULL;
Camera* camera3d = NULL;

Sprite sprite;

void ReleaseDirectX() {
	delete g_graphicsEngine;
	delete camera2d;
	delete camera3d;
}

void InitCamera()
{
	camera2d = new Camera;
	camera2d->SetTarget(CVector3::Zero());
	camera2d->SetPosition({ 0.0f, 0.0f, -10.0f });
	camera2d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);	
	camera2d->SetNear(0.1f);
	camera2d->SetFar(1000.0f);
	camera2d->Update();

	camera3d = new Camera;
	camera3d->SetTarget({ 0.0f, 50.0f, 0.0f });			
	camera3d->SetPosition({ 0.0f, 50.0f, 500.0f });	
	camera3d->Update();
}
void GameUpdate() {
	g_graphicsEngine->BegineRender();
	sprite.Update(CVector3::Zero(), CQuaternion::Identity(), { 300.0f,300.0f,300.0f });
	sprite.Draw();
	g_graphicsEngine->EndRender();
}

INT WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	InitCamera();
	sprite.Init(L"sprite/mikyan.dds", 1000.0f, 1000.0f);
	while (DispatchWindowMessage()) {
		GameUpdate();
	}
}
