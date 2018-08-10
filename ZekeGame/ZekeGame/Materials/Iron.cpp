#include "stdafx.h"
#include "Iron.h"
#include "Player.h"

Iron::Iron() {
	m_skinModel = new SkinModel;
	m_skinModel->Init(L"Assets/modelData/IronOre.cmo");
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}
Iron::~Iron() {
	delete m_skinModel;
}

void Iron::Update(Player* m_player) {
	if (isNear(m_player->GetPosition())) {
		isGet = true;
	}
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void Iron::Draw() {
	m_skinModel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

bool Iron::isNear(CVector3 pos) {
	CVector3 v = pos - m_pos;
	float diff = v.Length();
	if (diff <= mf_near) {
		return true;
	}
	else {
		return false;
	}
}