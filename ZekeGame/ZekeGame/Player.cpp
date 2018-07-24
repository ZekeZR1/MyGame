#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	m_position.y += 500.0f;
	m_charaCon.Init(30.0f, 50.0f, m_position);
}


Player::~Player()
{
}

void Player::Turn() {
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotation.SetRotation(CVector3::AxisY(), angle);
}

void Player::Update() {
	Turn();
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
		m_moveSpeed.y += 600.0f;
	}
	m_moveSpeed.y -= 30.0f;
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), 180.0f);	
	qRot.Multiply(m_rotation, qRot);
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Player::Draw() {
	m_model.Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
}

