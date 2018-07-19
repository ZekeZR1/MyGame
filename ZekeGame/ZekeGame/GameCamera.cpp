#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
	camera2d = new Camera;
	camera2d->SetTarget(CVector3::Zero());
	camera2d->SetPosition({ 0.0f, 0.0f, -10.0f });
	camera2d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);	//ƒJƒƒ‰‚ÌŒvŽZ•ûŽ®‚ð•½s“Š‰e‚É‚·‚éB
	camera2d->SetNear(0.1f);
	camera2d->SetFar(1000.0f);
	camera2d->Update();

	camera3d = new Camera;
	camera3d->SetTarget({ 0.0f, 20.0f, 0.0f });
	camera3d->SetPosition({ 0.0f, 350.0f, 300.0f });
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
	camera3d->SetNear(0.1f);
	camera3d->SetFar(10000.0f);
	camera3d->Update();
}


GameCamera::~GameCamera()
{
	delete camera2d;
	delete camera3d;
}

void GameCamera::Update(Player* player) {
	CVector3 toCameraPos = camera3d->GetPosition() - camera3d->GetTarget();
	camera3d->SetTarget(player->GetPosition());
	CMatrix mRot = CMatrix::Identity();
	mRot.MakeRotationY(CMath::DegToRad(3.0f) * g_pad[0].GetRStickXF());
	mRot.Mul(toCameraPos);
	CVector3 rotAxis;
	CVector3 upAxis(0.0f, 1.0f, 0.0f);
	rotAxis.Cross(upAxis, toCameraPos);
	rotAxis.Normalize();
	mRot = CMatrix::Identity();
	mRot.MakeRotationAxis(rotAxis, CMath::DegToRad(3.0f) * g_pad[0].GetRStickYF());
	mRot.Mul(toCameraPos);
	camera3d->SetPosition(camera3d->GetTarget() + toCameraPos);
	camera2d->Update();
	camera3d->Update();
}