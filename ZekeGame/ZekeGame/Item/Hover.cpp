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
	//panel
	ms_panel.Init(L"sprite/HoverMenu.dds", 800.0f, 500.0f);
	m_panelPos.x -= 380.0f;
	m_panelPos.y -= 270.0f;
	m_panelScale = { 0.7f,0.7f,0.7f };
	ms_panel.Update(m_panelPos, CQuaternion::Identity(), m_panelScale, { 0.5,0.5 });
	m_gaugePos.x -= 400.0f;
	m_gaugePos.y -= 190.0f;
	ms_gauge.Init(L"sprite/HoverGauge.dds", 250.0f, 30.0f);
	ms_gauge.Update(m_gaugePos, CQuaternion::Identity(), m_gaugeScale,{ 0.0f,0.0f });
	ms_frame.Init(L"sprite/HoverFrame.dds", 250.0f, 30.0f);
	ms_frame.Update(m_gaugePos, CQuaternion::Identity(), m_gaugeScale, { 0.0f,0.0f });

	m_physicsStaticObject = new PhysicsStaticObject;
	m_physicsStaticObject->CreateMeshObject(*m_hoverModel, m_pos, m_rot);
}


Hover::~Hover()
{
	delete m_hoverModel;
	delete m_physicsStaticObject;
}

void Hover::Update() {
	BatteryGauge();
	UseBattery();
	Ride();
	Physics();
	MoveAndRotation();
}

void Hover::Draw() {
	m_hoverModel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

void Hover::DrawSprite() {
	if (!isRiding)
		return;
	ms_panel.Draw();
	ms_gauge.Draw();
	ms_frame.Draw();
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

void Hover::BatteryGauge() {
	if (!isRiding)
		return;
	if (::g_pad[0].IsTrigger(enButtonX)) {
		mp_inventory->ChargeFuel();
		m_isMaxBattery = true;
		m_isLowBattery = false;
		m_gaugeScale.x = 1.0f;
	}
	if (m_isLowBattery) {
		mp_player->isLowHoverBattery = true;
	}else {
		mp_player->isLowHoverBattery = false;
	}

	if (m_gaugeScale.x <= 0.0f) {
		m_isLowBattery = true;
	}else {
		m_isLowBattery = false;
	}
	if (m_gaugeScale.x >= 1.0f) {
		m_isMaxBattery = true;
	}else {
		m_isMaxBattery = false;
	};

	if (!mp_player->isMaxBattery && !m_isLowBattery) {
		mp_player->ChargeBattery();
		m_gaugeScale.x -= CHARGECOST;
	}
	m_moveSpeed = mp_player->GetMoveSpeed();
	if (m_moveSpeed.x != 0.0f || m_moveSpeed.z != 0.0f) {
		if(!m_isLowBattery)
			m_gaugeScale.x -= MOVECOST;
	}
	ms_gauge.Update(m_gaugePos, CQuaternion::Identity(), m_gaugeScale, { 0.0f,0.0f });
}

void Hover::UseBattery() {
}