#include "stdafx.h"
#include "GameScene.h"
#include "BackGround.h"
#include "level\Level.h"
#include "Player.h"

GameScene* g_game = nullptr;
extern GameCamera* camera;
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
	camera->Update(m_player);
	CVector3 DrilPos = m_player->GetPosition();
	bg->Update(DrilPos);
}

void GameScene::Draw() {
	bg->Draw();
	m_player->Draw();
	m_model->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}