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
	BackGround* bg;
	CVector3 modelPos = CVector3::Zero();
	//SkinModel smodel;
	Animation modelanimation;
};

extern GameScene* g_game;