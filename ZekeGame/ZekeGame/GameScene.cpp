#include "stdafx.h"
#include "GameScene.h"
#include "BackGround.h"
#include "level\Level.h"
#include "Player.h"

GameScene* g_game = nullptr;
GameScene::GameScene()
{
	g_game = this;
	bg = new BackGround;
	m_player = new Player;
	m_model = new SkinModel;
	m_model->Init(L"Assets/modelData/Space.cmo");
	//smodel = new SkinModel;
	//smodel->Init(L"Assets/modelData/testbox.cmo");
	//aniclip[0].Load(L"Assets/modelData/testbox.tka");
	//aniclip[0].SetLoopFlag(true);
	//modelanimation.Init(
//		*smodel,
		//aniclip,
		//1
	//);
}


GameScene::~GameScene()
{
	g_game = nullptr;
	delete m_player;
	delete bg;
	delete m_model;
}

void GameScene::Update() {
	m_model->UpdateWorldMatrix(CVector3::Zero(),CQuaternion::Identity(),CVector3::One());
	m_player->Update();
	CVector3 DrilPos = m_player->GetPosition();
	//DrilPos.z *= 200.0f;
	bg->Update(DrilPos);
	CVector3 toCameraPos = camera3d->GetPosition() - camera3d->GetTarget();
	camera3d->SetTarget(m_player->GetPosition());
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
}

void GameScene::Draw() {
	bg->Draw();
	m_player->Draw();
	m_model->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

