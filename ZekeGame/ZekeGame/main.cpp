#include "stdafx.h"
#include "window/Window.h"

//Global
HWND g_hwnd = NULL;
GraphicsEngine* g_graphicsEngine = NULL;
Camera* camera2d = NULL;
Camera* camera3d = NULL;
CVector3 modelPos = CVector3::Zero();
SkinModel smodel;

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
	modelPos.z++;
	smodel.UpdateWorldMatrix(modelPos,CQuaternion::Identity(),CVector3::One());
	smodel.Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
	g_graphicsEngine->EndRender();
}

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	InitCamera();
	smodel.Init(L"Assets/modelData/testbox.cmo");
	while (DispatchWindowMessage()) {
		GameUpdate();
	}
}
