#include "stdafx.h"
#include "Hover.h"
#include "Inventory.h"
#include "Player.h"

Hover::Hover(Player* player, Inventory* inventory)
{
	mp_player = player;
	mp_inventory = inventory;

	m_hoverModel.Init(L"Assets/modelData/Hover.cmo", enFbxUpAxisY);
	
	m_physicsStaticObject = new PhysicsStaticObject;
	m_physicsStaticObject->CreateMeshObject(m_hoverModel, m_pos, m_rot);
}


Hover::~Hover()
{
	delete m_physicsStaticObject;
}

void Hover::Update() {

}

void Hover::Draw() {
	m_hoverModel.Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
}

void Hover::DrawSprite() {

}