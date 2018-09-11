#include "stdafx.h"
#include "Inventory.h"
#include "ExplorationRocket.h"

ExplorationRocket::ExplorationRocket(Player* m_player, Inventory* m_inventory)
{
	mp_player = m_player;
	mp_inventory = m_inventory;

	m_pos = m_player->GetForward(300.0f);
	m_basepos = m_pos;
	m_skinModel = new SkinModel;
	m_skinModel->Init(L"Assets/modelData/ExRocketDL.cmo",enFbxUpAxisZ);
	m_skinModel->UpdateWorldMatrix(m_pos, m_rot, CVector3::One());

	m_physicsStaticObject = new PhysicsStaticObject;
	//m_rot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_physicsStaticObject->CreateMeshObject(*m_skinModel, m_pos, m_rot);

	m_sMenu = new Sprite;
	m_sMenu->Init(L"sprite/ExRocketMenu.dds", 1280.0f, 720.0f);
	m_sMenu->Update(CVector3::Zero(), CQuaternion::Identity(), { 0.8f,0.8f,0.8f }, { 0.5f,0.5f });

	m_sArrow.Init(L"sprite/ExRocketMenuArrow.dds", 1280.0f, 720.0f);

	m_popup = new Popup;
	m_fontPos = { 730.0f, 250.0f,0.0f };
}

ExplorationRocket::~ExplorationRocket(){
	delete m_skinModel;
	delete m_sMenu;
	delete m_physicsStaticObject;
	delete m_popup;
}

void ExplorationRocket::Update() {
	switch (setting) {
	case en_Searching:
		mi_nowSearchingTime++;
		m_pos.y += 10.0f;
		if (mi_nowSearchingTime == mi_SearchTime) {
			setting = en_Back;
		}
		break;
	case en_Back:
		mi_nowSearchingTime--;
		m_pos.y -= 10.0f;
		if (mi_nowSearchingTime == 0) {
			isGotMaterial = true;
			setting = en_Material;
			m_physicsStaticObject = new PhysicsStaticObject;
			m_physicsStaticObject->CreateMeshObject(*m_skinModel, m_pos, m_rot);
		}
		break;
	}
	if (isGotMaterial && isOpenMenu) {
		AddMaterial();
	}
	Menu();
	RocketControl();
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void ExplorationRocket::Menu() {
	//Menu Open and Close
	if (g_pad[0].IsTrigger(enButtonX)) {
		Exit();
	}
	if (g_pad[0].IsTrigger(enButtonB)) {
		OpenMenu();
	}
	if (!(mp_player->isNear(m_pos, 300.0f))) {
		Exit();
	}

	m_popup->Update();
}

void ExplorationRocket::Draw() {
	m_skinModel->Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
}

void ExplorationRocket::DrawSprite() {
	if (isOpenMenu) {
		m_sMenu->Draw();
		m_popup->Draw();
		m_sArrow.Draw();
		m_font.Draw();
	}
}

void ExplorationRocket::RocketControl() {
	if (!isOpenMenu)
		return;
	if (g_pad[0].IsTrigger(enButtonUp)) {
		setting = en_Material;
	}
	if (g_pad[0].IsTrigger(enButtonDown)) {
		setting = en_Launch;
		//setting = en_Exit;
	}
	m_sArrow.Update(m_ArrowPos, CQuaternion::Identity(), { 0.8f,0.8f,0.8f }, { 0.5f,0.5f });

	switch (setting) {
	case en_Material:
		SetMaterial();
		break;
	case en_Launch:
		Launch();
		break;
	case en_Searching:
		break;
	case en_Exit:
		CloseMenu();
		break;
	}
}

void ExplorationRocket::SetMaterial() {
	wchar_t mw_silicon[255] = { L"Silicon" };
	wchar_t mw_iron[255] = { L"Iron" };
	m_ArrowPos.y = 0.0f;
	if (g_pad[0].IsTrigger(enButtonRight)) {
		gotMaterial = en_Silicon;
	}
	if (g_pad[0].IsTrigger(enButtonLeft)) {
		gotMaterial = en_Iron;
	}
	switch (gotMaterial) {
	case en_Iron:
		m_font.Init(mw_iron, m_fontPos);
		break;
	case en_Silicon:
		m_font.Init(mw_silicon, m_fontPos);
	}
}

void ExplorationRocket::Exit() {
	if (!isOpenMenu) {
		return;
	}
	isOpenMenu = false;
	mp_player->isOpenMenuNow = false;
	mp_player->m_nMenu--;
	setting = en_Material;
}

void ExplorationRocket::Launch() {
	m_ArrowPos.y = -80.0f;
	//m_sprite->Init(L"sprite/ExRocketMenu.dds", 1280.0f, 720.0f);
	if (g_pad[0].IsTrigger(enButtonB)) {
		delete m_physicsStaticObject;
		setting = en_Searching;
		isOpenMenu = false;
		mp_player->CloseMenu();
	}
}

/*
	char message[256];
	sprintf_s(message, "Close and en_MATERIALLLLLLLL\n");
	OutputDebugStringA(message);
*/

void ExplorationRocket::OpenMenu() {
	if (setting != en_Material)
		return;
	if (mp_player->isNear(m_pos, 200.0f)) {
		if (!isOpenMenu) {
			if (mp_player->CanOpenMenu()) {
				char message[256];
				sprintf_s(message, "OPEN ROCKET\n");
				OutputDebugStringA(message);
				isOpenMenu = true;
				mp_player->OpenMenu();
			}
		}
	}
}

void ExplorationRocket::CloseMenu() {
	//m_sprite->Init(L"sprite/ExRocketClose.dds", 1280.0f, 720.0f);
	if (g_pad[0].IsTrigger(enButtonB)) {
		Exit();
	}
}

void ExplorationRocket::AddMaterial() {
	switch (gotMaterial) {
	case en_Iron:
		mp_inventory->m_nIron += 100.0f;
		m_popup->Notify(0);
		isGotMaterial = false;
		break;
	case en_Silicon:
		mp_inventory->m_nSilicon += 100.0f;
		m_popup->Notify(0);
		isGotMaterial = false;
		break;
	}
}