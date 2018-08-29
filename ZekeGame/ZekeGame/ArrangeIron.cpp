#include "stdafx.h"
#include "Materials\Iron.h"
#include "Inventory.h"
#include "ArrangeIron.h"



ArrangeIron::ArrangeIron(Player* player, Inventory* inventory){
	mp_player = player;
	mp_inventory = inventory;

	float x = rand() % 20000;
	float z = rand() % 12000;
	m_IronsPos.x = x - 10000.0f;
	m_IronsPos.z = z - 6000.0f;

	for (int i = 0; i < MAXIRON; i++) {
		m_irons[i] = new Iron;
		float x = rand() % 700;
		float y = rand() % 200;
		y -= 100.0f;
		float z = rand() % 700;
		CVector3 pos;
		pos.x = x + m_IronsPos.x;
		pos.y = y;
		pos.z = z + m_IronsPos.z;
		m_irons[i]->SetPosition(pos);
		m_irons[i]->Update(player, inventory);
	}
}


ArrangeIron::~ArrangeIron()
{
	for (int i = 0; i < MAXIRON; i++) {
		delete m_irons[i];
	}
}

void ArrangeIron::Update() {
	for (int i = 0; i < MAXIRON; i++) {
			m_irons[i]->Update(mp_player, mp_inventory);
	}
}

void ArrangeIron::Draw() {
	for (int i = 0; i < MAXIRON; i++) {
		m_irons[i]->Draw();
	}
}