#include "stdafx.h"
#include "MiningMachine.h"
#include "Popup.h"
#include "Inventory.h"

MiningMachine::MiningMachine(Player* player, Inventory* inventory)
{
	mp_player = player;
	mp_inventory = inventory;
	m_MiningMachine.Init(L"Assets/modelData/MiningItem.cmo", enFbxUpAxisY);
	m_pos = player->GetForward(300.0f);
	m_MiningMachine.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	ms_menu.Init(L"sprite/MiningMachineMenu.dds", 500.0f, 300.0f);
	//ms_menu.Update(CVector3::Zero(), CQuaternion::Identity(), { 0.7f,0.7f,0.7f }, { 0.5f,0.5f });
	ms_menu.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
	m_physicsStaticObject.CreateMeshObject(m_MiningMachine, m_pos, CQuaternion::Identity());
}


MiningMachine::~MiningMachine()
{
}

void MiningMachine::OpenClose() {
	if (!mp_player->isNear(m_pos, 400.0f)) {
		isOpenMenu = false;
		mp_player->CloseMenu();
		return;
	}
	if (g_pad[0].IsTrigger(enButtonB)) {
		if (isOpenMenu) {
			isOpenMenu = false;
			mp_player->CloseMenu();
		}
		else {
			isOpenMenu = true;;
			mp_player->OpenMenu();
			if (isGot) {
				m_popup.Notify(0);
				mp_inventory->m_nFuel += 50;
				mn_mining = 0;
				isGot = false;
			}
		}
	}
	
}

void MiningMachine::Menu() {
	if (!isOpenMenu)
		return;
	if (g_pad[0].IsTrigger(enButtonA)) {
		isMining = true;
	}
}

void MiningMachine::Mining() {
	if (!isMining)
		return;
	mn_mining++;
	if (mn_mining >= MININGTIME) {
		isGot = true;
		isMining = false;
	}
}

void MiningMachine::Update() {
	OpenClose();
	Menu();
	Mining();
	m_popup.Update();
}

void MiningMachine::Draw() {
	m_MiningMachine.Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
}

void MiningMachine::DrawSprite() {
	if(isOpenMenu)
		ms_menu.Draw();
	m_popup.Draw();
}