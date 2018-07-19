#include "stdafx.h"
#include "Title.h"
#include "GameScene.h"


Title::Title()
{
	m_sprite = new Sprite;
	m_sprite->Init(L"sprite/mikyan.dds", 300.0f, 300.0f);
	m_sprite->Update({ 0.0f,0.0f,0.0f }, CQuaternion::Identity(), CVector3::One(), CVector2::Zero());
}


Title::~Title()
{
	delete m_sprite;
}

void Title::Update() {
	if (g_pad[0].IsTrigger(enButtonA)) {
		currentScene = new GameScene;
		delete this;
	}
}

void Title::Draw() {
	m_sprite->Draw();
}