#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	m_model.Init(L"Assets/modelData/testbox.cmo",enFbxUpAxisY);
	m_position.y += 110.0f;
	m_charaCon.Init(10.0f, 50.0f, m_position);
}


Player::~Player()
{
}

void Player::Update() {
	if (g_pad[0].IsTrigger(enButtonA)) {
		m_moveSpeed.y += 300.0f;
	}
	m_moveSpeed.x = g_pad[0].GetLStickXF() * -300.0f;
	m_moveSpeed.z = g_pad[0].GetLStickYF() * -300.0f;
	m_moveSpeed.y -= 980.0f * (1.0f / 60.0f);
	//Hands-On 4 キャラコンを使って移動する。
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);


	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Player::Draw() {
	extern Camera* camera3d;
	m_model.Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
}