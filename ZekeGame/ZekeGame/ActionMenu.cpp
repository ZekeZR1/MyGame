#include "stdafx.h"
#include "GameScene.h"
#include "ActionMenu.h"

ActionMenu::ActionMenu()
{
	//Font
	m_ActMenu = new Sprite;
	m_ActMenu->Init(L"sprite/ActMenu.dds", 1280.0f, 720.0f);
	m_ActMenu->Update(m_ActPos, CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
}


ActionMenu::~ActionMenu()
{
	delete m_ActMenu;
}

void ActionMenu::Update() {
	if (g_pad[0].IsTrigger(enButtonUp)) {
		m_flatPos.y += 10.0f;
	}
	if (g_pad[0].IsTrigger(enButtonDown)) {
		m_flatPos.y -= 10.0f;
	}
}

void ActionMenu::Draw() {
	m_ActMenu->Draw();
}

