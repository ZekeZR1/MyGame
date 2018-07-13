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
}

void GameScene::Update() {
	m_player.Update();
	//modelanimation.Play(0);
	//smodel->UpdateWorldMatrix(modelPos,CQuaternion::Identity(),CVector3::One());
	//modelanimation.Update(1.0f / 30.0f);
}

void GameScene::Draw() {
	//extern Camera* camera3d;
	//smodel->Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
	//bg->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
	bg->Draw();
	m_player.Draw();
}