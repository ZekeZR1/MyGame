#include "stdafx.h"
#include "GameScene.h"
#include "BackGround.h"
#include "level\Level.h"
#include "Player.h"
#include "ActionMenu.h"

GameScene* g_game = nullptr;
extern GameCamera* camera;

GameScene::GameScene()
{
	g_game = this;
	m_ActMenu = new ActionMenu;
	bg = new BackGround;
	m_player = new Player;
	m_model = new SkinModel;
	m_model->Init(L"Assets/modelData/Space.cmo");
	//Font
	pSpriteBatch = new DirectX::SpriteBatch(g_graphicsEngine->GetD3DDeviceContext());
	pSpriteFont = new DirectX::SpriteFont(g_graphicsEngine->GetD3DDevice(), L"Assets/font/myfile.spritefont");
	//Sprite
	mS_ActState = new Sprite;
	mS_ActState->Init(L"sprite/ActState_Mining.dds", 500.0f, 500.0f);
	mv_ActSpos.x = 500.0f;
	mv_ActSpos.y = 300.0f;
	mS_ActState->Update(mv_ActSpos, CQuaternion::Identity(), CVector3::One(), { 0.5,0.5 });
	//
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
	delete mS_ActState;
	delete m_ActMenu;
	delete pSpriteBatch;
	delete pSpriteFont;
}

void GameScene::Update() {
	//座標
	CVector3 Ppos = m_player->GetPosition();
	mi_x = Ppos.x;
	_itow_s(mi_x, mw_PosX,10);
	mi_y = Ppos.y;
	_itow_s(mi_y, mw_PosY, 10);
	mi_z = Ppos.z;
	_itow_s(mi_z, mw_PosZ, 10);
	m_model->UpdateWorldMatrix(CVector3::Zero(),CQuaternion::Identity(),CVector3::One());
	m_player->Update();
	camera->Update(m_player);
	//Player近くの座標を送る
	mi_flaty = m_ActMenu->m_flatPos.y;
	_itow_s(mi_flaty, mw_flatPosY, 10);
	CVector3 DrilPos = m_player->GetPosition();
	bg->Update(DrilPos,m_ActMenu->m_flatPos, m_player);
	//ActMenu
	if (g_pad[0].IsTrigger(enButtonX)) {
		if (isOpenAct) {
			isOpenAct = false;
		}
		else {
			isOpenAct = true;
		}
	}
	if (isOpenAct) {
		m_ActMenu->Update();
	}
	if (m_player->ActState == m_player->State_Leveling) {
		mS_ActState->Init(L"sprite/ActState_Flat.dds", 500.0f, 500.0f);
	}
	if (m_player->ActState == m_player->State_Fill) {
		mS_ActState->Init(L"sprite/ActState_Fill.dds", 500.0f, 500.0f);
	}
	if (m_player->ActState == m_player->State_Mining) {
		mS_ActState->Init(L"sprite/ActState_Mining.dds", 500.0f, 500.0f);
	}
	mS_ActState->Update(mv_ActSpos, CQuaternion::Identity(), { 0.5f,0.5f,0.5f }, { 0.5,0.5 });
}

void GameScene::Draw() {
	bg->Draw();
	m_player->Draw();
	m_model->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
	mS_ActState->Draw();
	if (isOpenAct) {
		m_ActMenu->Draw();
	}
}

void GameScene::DrawFont() {
	pSpriteBatch->Begin();
	//X座標
	pSpriteFont->DrawString(pSpriteBatch, L"X", DirectX::XMFLOAT2(0.0f, 0.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosX), DirectX::XMFLOAT2(50.0f, 0.0f), CVector4::White);
	//Y座標
	pSpriteFont->DrawString(pSpriteBatch, L"Y", DirectX::XMFLOAT2(0.0f, 50.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosY), DirectX::XMFLOAT2(50.0f, 50.0f), CVector4::White);
	//Z座標
	pSpriteFont->DrawString(pSpriteBatch, L"Z", DirectX::XMFLOAT2(0.0f, 100.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosZ), DirectX::XMFLOAT2(50.0f, 100.0f), CVector4::White);
	//整地座標
	if (isOpenAct) {
		pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_flatPosY), DirectX::XMFLOAT2(640.0f, 360.0f), CVector4::Black);
	}
	pSpriteBatch->End();
}
