#include "stdafx.h"
#include "TheShip.h"
#include "Player.h"


TheShip::TheShip()
{
	m_model.Init(L"Assets/modelData/Ship.cmo", enFbxUpAxisY);
	m_pos.y = 2000.0f;
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}


TheShip::~TheShip()
{
}

void TheShip::GoDown() {
	isGoDown = true;
}

void TheShip::GoUp() {
	isGoDown = false;
	isGoUp = true;
}

void TheShip::Update(Player* player) {
	if (g_pad[0].IsTrigger(enButtonB) && player->isNear(m_pos,1000.0f)) {
		isRiding = true;
		isGoUp = true;
		player->isGoUp = true;
	}
	if (isGoDown) {
		if (m_pos.y >= 300.0f) {
			m_moveSpeed.y = -30.0f;
		}
		else if (m_pos.y < 300) {
			m_moveSpeed.y = -10.0f;
		}
		if (m_pos.y <= 0.0f) {
			m_moveSpeed.y = 0.0f;
		}
	}
	if (isGoUp) {
		m_moveSpeed.y = 25.0f;
		if (m_pos.y >= 5000.0f) {
			isInSpace = true;
		}
	}
	m_pos += m_moveSpeed;
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	if (isRiding) {
		CVector3 playerpos = m_pos;
		playerpos.y = m_pos.y + 100.0f;
		player->SetPosition(playerpos);
	}
}

void TheShip::Draw() {
	m_model.Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}