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
	CQuaternion rot = CQuaternion::Identity();
	rot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_physicsStaticObject.CreateMeshObject(m_MiningMachine, m_pos, rot);
	ms_menu.Init(L"sprite/MiningMachineStandby.dds", 1270.0f, 720.0f);
	ms_menu.Update(CVector3::Zero(), CQuaternion::Identity(), { 0.7f,0.7f,0.7f }, { 0.5f,0.5f });
	//ms_menu.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
	m_gaugePos.y -= 50.0f;
	ms_gauge.Init(L"sprite/MiningGauge.dds", 300.0f, 50.0f);
	m_gaugeScale.x = 0.0f;
	ms_gauge.Update(m_gaugePos, CQuaternion::Identity(), m_gaugeScale, { 0.0f,0.0f });
	ms_frame.Init(L"sprite/MiningFrame.dds", 300.0f, 50.0f);
	ms_frame.Update(m_gaugePos, CQuaternion::Identity(), CVector3::One() , { 0.0f,0.0f });
}


MiningMachine::~MiningMachine()
{
}

void MiningMachine::OpenClose() {
	if (!mp_player->isNear(m_pos, 300.0f)) {
		if (isOpenMenu) {
			isOpenMenu = false;
			mp_player->CloseMenu();
		}
		return;
	}
	if (g_pad[0].IsTrigger(enButtonB)) {
		if (isOpenMenu)
			return;
		isOpenMenu = true;
		isOpendNow = true;
		mp_player->OpenMenu();
		/*l
		if (isGot) {
			m_popup.Notify(0);
			mp_inventory->m_nFuel += 50;
			mn_mining = 0;
			isGot = false;
		}
		*/
	}
	if (g_pad[0].IsTrigger(enButtonX)) {
		isOpenMenu = false;
		mp_player->CloseMenu();
	}
}
	

void MiningMachine::Menu() {
	if (!isOpenMenu) 
		return;
	if (isGot) {
		m_popup.Notify(0);
		mp_inventory->m_nFuel += 50;
		mn_mining = 0;
		m_gaugeScale.x = 0.0f;
		ms_gauge.Update(m_gaugePos, CQuaternion::Identity(), m_gaugeScale, { 0.0f,0.0f });
		isGot = false;
	}
	if (g_pad[0].IsTrigger(enButtonB)) {
		if (isOpendNow) {
			isOpendNow = false;
			return;
		}
		isMining = true;
	}
	if (isMining) {
		ms_menu.Init(L"sprite/MiningMachineMining.dds", 1270.0f, 720.0f);
		ms_menu.Update(CVector3::Zero(), CQuaternion::Identity(), { 0.7f,0.7f,0.7f }, { 0.5f,0.5f });
	}
	else {
		ms_menu.Init(L"sprite/MiningMachineStandby.dds", 1270.0f, 720.0f);
		ms_menu.Update(CVector3::Zero(), CQuaternion::Identity(), { 0.7f,0.7f,0.7f }, { 0.5f,0.5f });
	}
}

void MiningMachine::Mining() {
	if (!isMining)
		return;
	mn_mining++;
	m_gaugeScale.x = mn_mining / mn_miningTime;
	ms_gauge.Update(m_gaugePos, CQuaternion::Identity(), m_gaugeScale, { 0.0f,0.0f });
	if (mn_mining >= mn_miningTime) {
		m_gaugeScale.x = 0.0f;
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
	if (isOpenMenu) {
		ms_menu.Draw();
		ms_frame.Draw();
		ms_gauge.Draw();
	}
	m_popup.Draw();
}

void MiningMachine::CastFont() {

}