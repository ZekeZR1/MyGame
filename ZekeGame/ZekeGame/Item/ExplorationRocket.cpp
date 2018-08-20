#include "stdafx.h"
#include "ExplorationRocket.h"



ExplorationRocket::ExplorationRocket(Player* m_player)
{
	mp_player = m_player;
	m_pos = m_player->GetForward(200.0f);
	m_skinModel = new SkinModel;
	m_skinModel->Init(L"Assets/modelData/ExplorationRocket.cmo",enFbxUpAxisY);
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	m_sprite = new Sprite;
	m_sprite->Init(L"sprite/RocketMenu.dds", 1280.0f, 720.0f);
	m_sprite->Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
}

ExplorationRocket::~ExplorationRocket()
{
}

void ExplorationRocket::Update() {
	if (!isOnGround) {
		m_pos.y += 10.0f;
	}
	Menu();
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void ExplorationRocket::Draw() {
	m_skinModel->Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
	if (isOpenMenu) {
		m_sprite->Draw();
	}
}

void ExplorationRocket::Menu() {
	if (g_pad[0].IsTrigger(enButtonB)) {
		if (isOpenMenu) {
			isOpenMenu = false;
		}
		else {
			isOpenMenu = true;
		}
		//if (mp_player->isNear(m_pos, 200.0f)) {
//			isOnGround = false;
		//}
	}
}
