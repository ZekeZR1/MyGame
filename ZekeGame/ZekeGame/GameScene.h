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
	Player* m_player;
	bool Converting = false;
private:
	SkinModel * m_model;
	CVector3 m_spritePos = CVector3::Zero();
	float spweight = 100.0f, sphight = 100.0f;
	CVector3 m_spscale = { 1.0f,1.0f,1.0f };
	BackGround* bg;
	CVector3 modelPos = CVector3::Zero();
	//SkinModel smodel;
	Animation modelanimation;
};

extern GameScene* g_game;