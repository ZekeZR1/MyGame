#include "stdafx.h"
#include "window/Window.h"

//Global
HWND g_hwnd = NULL;
GraphicsEngine* g_graphicsEngine = NULL;
Camera* camera2d = NULL;
Camera* camera3d = NULL;
CVector3 modelPos = CVector3::Zero();
SkinModel smodel;
Animation modelanimation;
AnimationClip aniclip[1];

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
	for (auto& pad : g_pad) {
		pad.Update();
	}
	
	if(g_pad[0].IsPress(enButtonRight)) {
		modelPos.x--;
	}
	if(g_pad[0].IsPress(enButtonLeft)) {
		modelPos.x++;
	}
	//modelPos.z++;
	modelanimation.Play(0);
	smodel.UpdateWorldMatrix(modelPos,CQuaternion::Identity(),CVector3::One());
	modelanimation.Update(1.0f / 30.0f);
}

void Render() {
	g_graphicsEngine->BegineRender();
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
	aniclip[0].Load(L"Assets/modelData/testbox.tka");
	aniclip[0].SetLoopFlag(true);
	modelanimation.Init(
		smodel,
		aniclip,
		1
		);
	while (DispatchWindowMessage()) {
		GameUpdate();
		Render();
	}
}
