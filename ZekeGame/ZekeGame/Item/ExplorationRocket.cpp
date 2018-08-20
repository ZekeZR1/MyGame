#include "stdafx.h"
#include "ExplorationRocket.h"



ExplorationRocket::ExplorationRocket(Player* m_player)
{
	mp_player = m_player;
	m_pos = m_player->GetForward(200.0f);
	m_skinModel = new SkinModel;
	m_skinModel->Init(L"Assets/modelData/ExplorationRocket.cmo",enFbxUpAxisY);
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}


ExplorationRocket::~ExplorationRocket()
{
}

void ExplorationRocket::Update() {
	
	if (g_pad[0].IsTrigger(enButtonB)) {
		if (mp_player->isNear(m_pos, 200.0f)) {
			isOnGround = false;
		}
	}
	if (!isOnGround) {
		m_pos.y += 10.0f;
	}
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	
}

void ExplorationRocket::Draw() {
	m_skinModel->Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
}
