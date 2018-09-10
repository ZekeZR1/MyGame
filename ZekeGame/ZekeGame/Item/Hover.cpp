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
	m_pos = mp_player->GetForward(200.0f);
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

}

void Hover::Draw() {
	m_hoverModel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

void Hover::DrawSprite() {

}