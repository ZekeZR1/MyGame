#pragma once
#include "character\CharacterController.h"
class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw();
	void SetPosition(CVector3 pos) {
		m_position = pos;
		m_charaCon.SetPosition(m_position);
	}
	CVector3 GetPosition() {
		return m_position;
	}
private:
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation;
	CVector3 m_moveSpeed = CVector3::Zero();
	Animation m_animation;
	AnimationClip m_animationClip[1];
	CharacterController m_charaCon;
};

