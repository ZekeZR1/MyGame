#include "stdafx.h"
#include "ExplorationRocket.h"

ExplorationRocket::ExplorationRocket(Player* m_player)
{
	mp_player = m_player;
	m_pos = m_player->GetForward(200.0f);
	m_basepos = m_pos;
	m_skinModel = new SkinModel;
	//m_skinModel->Init(L"Assets/modelData/ExplorationRocket.cmo",enFbxUpAxisY);
	m_skinModel->Init(L"Assets/modelData/ExRocketDL.cmo",enFbxUpAxisY);
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());

	m_physicsStaticObject = new PhysicsStaticObject;
	qRot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_physicsStaticObject->CreateMeshObject(*m_skinModel, m_pos, qRot);

	m_sprite = new Sprite;
	m_sprite->Init(L"sprite/RocketMenu.dds", 1280.0f, 720.0f);
	m_sprite->Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
}

ExplorationRocket::~ExplorationRocket(){
	delete m_skinModel;
	delete m_sprite;
	delete m_physicsStaticObject;
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
	if (g_pad[0].IsTrigger(enButtonY)) {
		Exit();
	}
	if (g_pad[0].IsTrigger(enButtonB)) {
		OpenMenu();
	}
	if (!(mp_player->isNear(m_pos, 300.0f))) {
		Exit();
	}
}

void ExplorationRocket::Draw() {
	m_skinModel->Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
}

void ExplorationRocket::DrawSprite() {
	if (isOpenMenu) {
		m_sprite->Draw();
	}
}

void ExplorationRocket::RocketControl() {
	if (isOpenMenu) {
		if (g_pad[0].IsTrigger(enButtonUp)) {
			setting = en_Launch;
		}
		if (g_pad[0].IsTrigger(enButtonDown)) {
			setting = en_Exit;
		}
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
}

void ExplorationRocket::SetMaterial() {
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
	m_sprite->Init(L"sprite/ExRocketLaunch.dds", 1280.0f, 720.0f);
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
	m_sprite->Init(L"sprite/ExRocketClose.dds", 1280.0f, 720.0f);
	if (g_pad[0].IsTrigger(enButtonB)) {
		Exit();
	}
}