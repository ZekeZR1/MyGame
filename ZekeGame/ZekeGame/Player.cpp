#include "stdafx.h"
#include "Player.h"
#include "GameScene.h"

Player::Player()
{
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_position.y += 500.0f;
	m_charaCon.Init(30.0f, 50.0f, m_position);
}


Player::~Player()
{
}

void Player::Update() {
	Move();
	Turn();
	ChangeState();
}

void Player::Move() {
	if (m_enPState == PSTATE_WALK) {
		if (g_pad[0].IsPress(enButtonRB2)) {
			m_moveSpeedParam = 1300.0f;
		}else
			m_moveSpeedParam = 750.0f;
	}
	else {
		m_moveSpeedParam = 600.0f;
	}
	CVector3 cameraForward = camera3d->GetTarget() - camera3d->GetPosition();
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	m_moveSpeed.x = cameraForward.x * m_moveSpeedParam * g_pad[0].GetLStickYF();
	m_moveSpeed.z = cameraForward.z * m_moveSpeedParam * g_pad[0].GetLStickYF();
	CVector3 cameraRight;
	cameraRight.Cross({ 0.0f, 1.0f, 0.0f }, cameraForward);
	cameraRight.Normalize();
	m_moveSpeed += cameraRight * m_moveSpeedParam * g_pad[0].GetLStickXF();
	if (g_pad[0].IsTrigger(enButtonA)) {
		m_moveSpeed.y += 700.0f;
	}
	m_moveSpeed.y -= 50.0f;
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), 180.0f);
	qRot.Multiply(m_rotation, qRot);
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Player::Turn() {
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotation(CVector3::AxisY(), angle);
}

void Player::Draw() {
	m_model.Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
}

void Player::ChangeState() {
	if (m_enPState != PSTATE_MAKEGROUND)
		return;
	if (g_pad[0].IsTrigger(enButtonRB1)) {
		if(mi_state != 2)
			mi_state++;
	}
	if (g_pad[0].IsTrigger(enButtonLB1)) {
		if(mi_state != 0)
			mi_state--;
	}
	switch (mi_state) {
	case 0:
		ActState = State_Leveling;
		break;
	case 1:
		ActState = State_Mining;
		break;
	case 2:
		ActState = State_Fill;
		break;
	}
}

bool Player::isNear(CVector3 thatpos, float dist) {
	CVector3 t = m_position - thatpos;
	float diff = t.Length();
	if (diff < dist) {
		return true;
	}
	else {
		return false;
	}
}