#include "stdafx.h"
#include "Inventory.h"
#include "ExplorationRocket.h"

ExplorationRocket::ExplorationRocket(Player* m_player, Inventory* m_inventory)
{
	mp_player = m_player;
	mp_inventory = m_inventory;

	m_pos = m_player->GetForward(200.0f);
	m_basepos = m_pos;
	m_skinModel = new SkinModel;
	m_skinModel->Init(L"Assets/modelData/ExRocketDL.cmo",enFbxUpAxisZ);
	m_skinModel->UpdateWorldMatrix(m_pos, m_rot, CVector3::One());

	m_physicsStaticObject = new PhysicsStaticObject;
	//m_rot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_physicsStaticObject->CreateMeshObject(*m_skinModel, m_pos, m_rot);

	m_sprite = new Sprite;
	m_sprite->Init(L"sprite/ExRocketMenu.dds", 1280.0f, 720.0f);
	m_sprite->Update(CVector3::Zero(), CQuaternion::Identity(), { 0.8f,0.8f,0.8f }, { 0.5f,0.5f });

	m_sArrow.Init(L"sprite/ExRocketMenuArrow.dds", 1280.0f, 720.0f);

	m_popup = new Popup;
}

ExplorationRocket::~ExplorationRocket(){
	delete m_skinModel;
	delete m_sprite;
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
			m_physicsStaticObject->CreateMeshObject(*m_skinModel, m_pos, qRot);
		}
		break;
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
		if (isGotMaterial) {
			AddMaterial();
		}
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
		m_sprite->Draw();
		m_sArrow.Draw();
	}
	m_popup->Draw();
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
	m_ArrowPos.y = 0.0f;
	if (g_pad[0].IsTrigger(enButtonRight)) {

	}
	if (g_pad[0].IsTrigger(enButtonLeft)) {

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
	case Iron:
		mp_inventory->m_nIron += 100.0f;
		m_popup->Notify(en_GotMaterial);
		isGotMaterial = false;
		break;
	}
}