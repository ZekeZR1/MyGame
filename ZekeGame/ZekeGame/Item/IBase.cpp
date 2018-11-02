#include "stdafx.h"
#include "IBase.h"
#include "Player.h"

IBase::IBase(Player* player)
{
	mp_player = player;
	m_model.Init(L"Assets/modelData/Base.cmo", enFbxUpAxisY);
	m_pos = player->GetForward(500.0f);
	m_pos.y -= 100.0f;
	m_setPlayerPos = m_pos;
	m_rot = player->GetRot();
	m_model.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
	CQuaternion rot = CQuaternion::Identity();
	rot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_physicsStaticObject.CreateMeshObject(m_model,m_pos,rot);
}


IBase::~IBase()
{
}

void IBase::Update() {
	InOut();
	if (isIn) {
		mp_player->ChargeBattery();
	}
}

void IBase::Draw() {
	m_model.Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

void IBase::DrawSprite() {

}

void IBase::InOut() {
	if (!mp_player->isNear(m_pos, 400.0f))
		return;
	if (g_pad[0].IsTrigger(enButtonB)) {
		if (isIn) {
			isIn = false;
			m_setPlayerPos = m_pos;
			mp_player->isInBase = false;
			m_setPlayerPos.y += 500.0f;
			mp_player->SetPosition(m_setPlayerPos);
		}
		else {
			isIn = true;
			mp_player->isInBase = true;
			m_setPlayerPos = m_pos;
			m_setPlayerPos.y = m_pos.y + 100.0f;
			mp_player->SetPosition(m_setPlayerPos);
		}
	}
}