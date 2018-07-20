#include "stdafx.h"
#include "GameScene.h"
#include "BackGround.h"
#include "level\Level.h"
#include "Player.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK\Inc\SpriteBatch.h"

GameScene* g_game = nullptr;
extern GameCamera* camera;

GameScene::GameScene()
{
	g_game = this;
	bg = new BackGround;
	m_player = new Player;
	m_model = new SkinModel;
	m_model->Init(L"Assets/modelData/Space.cmo");
	//Sprite
	pSpriteBatch = new DirectX::SpriteBatch(g_graphicsEngine->GetD3DDeviceContext());
	pSpriteFont = new DirectX::SpriteFont(g_graphicsEngine->GetD3DDevice(), L"Assets/font/myfile.spritefont");
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
}

void GameScene::Update() {
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
	CVector3 DrilPos = m_player->GetPosition();
	bg->Update(DrilPos);
}

void GameScene::Draw() {
	bg->Draw();
	m_player->Draw();
	m_model->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

void GameScene::DrawFont() {
	pSpriteBatch->Begin();
	//XÀ•W
	pSpriteFont->DrawString(pSpriteBatch, L"X", DirectX::XMFLOAT2(0.0f, 0.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosX), DirectX::XMFLOAT2(50.0f, 0.0f), CVector4::White);
	//YÀ•W
	pSpriteFont->DrawString(pSpriteBatch, L"Y", DirectX::XMFLOAT2(0.0f, 50.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosY), DirectX::XMFLOAT2(50.0f, 50.0f), CVector4::White);
	//ZÀ•W
	pSpriteFont->DrawString(pSpriteBatch, L"Z", DirectX::XMFLOAT2(0.0f, 100.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosZ), DirectX::XMFLOAT2(50.0f, 100.0f), CVector4::White);
	pSpriteBatch->End();
}
