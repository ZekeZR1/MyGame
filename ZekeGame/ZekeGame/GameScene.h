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
private:
	Player m_player;
	BackGround* bg;
	CVector3 modelPos = CVector3::Zero();
	//SkinModel smodel;
	Animation modelanimation;
	AnimationClip aniclip[1];
};

extern GameScene* g_game;