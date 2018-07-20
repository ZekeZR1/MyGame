#pragma once
#include "IScene.h"
#include "BackGround.h"
#include "Player.h"
class GameScene : public IScene
{
public:
	GameScene();
	~GameScene();
	void Update() override;
	void Draw() override;
	void DrawFont() override;
	Player* m_player;
	bool Converting = false;
private:
	SkinModel * m_model;
	CVector3 m_spritePos = CVector3::Zero();
	float spweight = 100.0f, sphight = 100.0f;
	CVector3 m_spscale = { 1.0f,1.0f,1.0f };
	BackGround* bg;
	CVector3 modelPos = CVector3::Zero();
	Animation modelanimation;
	//Font
	DirectX::SpriteBatch* pSpriteBatch;
	DirectX::SpriteFont* pSpriteFont;
	wchar_t mw_PosX[256];
	wchar_t mw_PosY[256];
	wchar_t mw_PosZ[256];
	int mi_x = 0;
	int mi_y = 0;
	int mi_z = 0;
};

extern GameScene* g_game;