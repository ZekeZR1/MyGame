#include "stdafx.h"
#include "Iron.h"
#include "Inventory.h"
#include "Player.h"

Iron::Iron() {
	m_skinModel = new SkinModel;
	m_skinModel->Init(L"Assets/modelData/IronOre.cmo");
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}
Iron::~Iron() {
	delete m_skinModel;
}

void Iron::Update(Player* m_player, Inventory* inventory) {
	if (isGet)
		return;
	if (isNear(m_player->GetPosition())) {
		char message[256];
		sprintf_s(message, "GET IRON!!!\n");
		OutputDebugStringA(message);
		inventory->m_nIron += 1;
		isGet = true;
	}
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void Iron::Draw() {
	if (isGet)
		return;
	m_skinModel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

void Iron::SetPosition(CVector3 pos) {
	m_pos = pos;
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
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