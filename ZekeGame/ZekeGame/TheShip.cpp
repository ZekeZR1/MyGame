#include "stdafx.h"
#include "TheShip.h"
#include "Player.h"


TheShip::TheShip(Player* player)
{
	mp_player = player;
	m_model.Init(L"Assets/modelData/Ship.cmo", enFbxUpAxisY);
	m_pos.y = 50000.0f;
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}


TheShip::~TheShip()
{
	delete m_physics;
	m_physics = nullptr;
}

void TheShip::GoDown() {
	isGoDown = true;
	m_pos = mp_player->GetForward(3000);
	m_pos.y = 2000.0f;
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void TheShip::GoUp() {
	isGoDown = false;
	isGoUp = true;
}

void TheShip::Update() {
	if (g_pad[0].IsTrigger(enButtonB) && mp_player->isNear(m_pos,1000.0f)) {
		isRiding = true;
		isGoUp = true;
		mp_player->isGoUp = true;
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
			m_physics = new PhysicsStaticObject;
			CQuaternion rot = CQuaternion::Identity();
			rot.SetRotationDeg(CVector3::AxisX(), 90.0f);
			m_physics->CreateMeshObject(m_model, m_pos, rot);
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
		mp_player->SetPosition(playerpos);
	}
}

void TheShip::Draw() {
	m_model.Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}