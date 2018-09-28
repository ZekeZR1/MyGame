#include "stdafx.h"
#include "ClearScene.h"
#include "Title.h"


ClearScene::ClearScene()
{
	m_sprite.Init(L"sprite/Clear.dds", 1280.0f, 720.0f);
}


ClearScene::~ClearScene()
{
}


void ClearScene::Update() {
	if (g_pad[0].IsTrigger(enButtonA)) {
		currentScene = new Title;
		delete this;
	}
}

void ClearScene::Draw() {
	m_sprite.Draw();
}