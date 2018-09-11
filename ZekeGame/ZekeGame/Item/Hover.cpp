#include "stdafx.h"
#include "Hover.h"
#include "Inventory.h"
#include "Player.h"

Hover::Hover(Player* player, Inventory* inventory)
{
	mp_player = player;
	mp_inventory = inventory;
	m_hoverModel = new SkinModel;
	m_hoverModel->Init(L"Assets/modelData/Hover.cmo", enFbxUpAxisZ);
	m_rot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_pos = mp_player->GetForward(450.0f);
	m_hoverModel->UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
	
	m_physicsStaticObject = new PhysicsStaticObject;
	m_physicsStaticObject->CreateMeshObject(*m_hoverModel, m_pos, m_rot);
}


Hover::~Hover()
{
	delete m_hoverModel;
	delete m_physicsStaticObject;
}

void Hover::Update() {
	Ride();
	Physics();
	MoveAndRotation();
}

void Hover::Draw() {
	m_hoverModel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

void Hover::DrawSprite() {

}

void Hover::MoveAndRotation() {
	if (!isRiding)
		return;

	if (isRideNow) {
		mp_player->SetPosition(m_pos);
		isRideNow = false;
	}
	else {
		m_pos = mp_player->GetPosition();
		m_pos.y -= 50.0f;
	}
	if (g_pad[0].IsPress(enButtonRB2)) {
		CVector3 pos = mp_player->GetPosition();
		if(pos.y <= 350.0f)
			pos.y += 5.0f;
		mp_player->SetPosition(pos);
	}
	if (g_pad[0].IsPress(enButtonLB2)) {
		CVector3 pos = mp_player->GetPosition();
		if(pos.y >= 0.0f)
			pos.y -= 5.0f;
		mp_player->SetPosition(pos);
	}
	m_rot = mp_player->GetRot();
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_rot.Multiply(m_rot, qRot);
	m_hoverModel->UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
}

void Hover::Physics() {
	if (isRiding) {
		if (m_physicsStaticObject != nullptr) {
			delete m_physicsStaticObject;
			m_physicsStaticObject = nullptr;
		}
	}
	else {
		if (m_physicsStaticObject == nullptr) {
			m_physicsStaticObject = new PhysicsStaticObject;
			m_physicsStaticObject->CreateMeshObject(*m_hoverModel, m_pos, m_rot);
		}
	}
}

void Hover::Ride() {
	if (g_pad[0].IsTrigger(enButtonB)) {
		if (isRiding) {
			mp_player->isRiding = false;
			CVector3 pos = mp_player->GetPosition();
			pos.y += 70.0f;
			mp_player->SetPosition(pos);
			mp_player->CloseMenu();
			isRiding = false;
		}
		else {
			if (mp_player->m_enPState != mp_player->PSTATE_WALK)
				return;
			if (!mp_player->isNear(m_pos, 300.0f))
				return;
			if (mp_player->isRiding || isRiding)
				return;
			isRiding = true;
			isRideNow = true;
			mp_player->isRiding = true;
			//Menu‚ðŠJ‚¯‚È‚¢‚æ‚¤‚É‚·‚é
			mp_player->OpenMenu();
		}
	}
}