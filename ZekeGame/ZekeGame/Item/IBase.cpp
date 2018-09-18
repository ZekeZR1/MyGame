#include "stdafx.h"
#include "IBase.h"
#include "Player.h"

IBase::IBase(Player* player)
{
	mp_player = player;
	m_model.Init(L"Assets/modelData/Base.cmo", enFbxUpAxisY);
	m_pos = player->GetForward(500.0f);
	m_pos.y -= 100.0f;
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	CQuaternion rot = CQuaternion::Identity();
	rot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_physicsStaticObject.CreateMeshObject(m_model,m_pos,rot);
}


IBase::~IBase()
{
}

void IBase::Update() {

}

void IBase::Draw() {
	m_model.Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

void IBase::DrawSprite() {

}