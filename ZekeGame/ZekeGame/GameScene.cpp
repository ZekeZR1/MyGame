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
}

void GameScene::Update() {
	m_player->Update();
	CVector3 playerPos = m_player->GetPosition();
	bg->Update(playerPos);
	CVector3 toCameraPos = camera3d->GetPosition() - camera3d->GetTarget();
	camera3d->SetTarget(m_player->GetPosition());
	CMatrix mRot = CMatrix::Identity();		
	mRot.MakeRotationY(CMath::DegToRad(1.0f) * g_pad[0].GetRStickXF());
	mRot.Mul(toCameraPos);
	CVector3 rotAxis;
	CVector3 upAxis(0.0f, 1.0f, 0.0f);
	rotAxis.Cross(upAxis, toCameraPos);
	rotAxis.Normalize();
	mRot = CMatrix::Identity();
	mRot.MakeRotationAxis(rotAxis, CMath::DegToRad(1.0f) * g_pad[0].GetRStickYF());
	mRot.Mul(toCameraPos);
	camera3d->SetPosition(camera3d->GetTarget() + toCameraPos);
}

void GameScene::Draw() {
	bg->Draw();
	m_player->Draw();
}

