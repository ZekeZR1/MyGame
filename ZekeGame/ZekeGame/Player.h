#pragma once
#include "character\CharacterController.h"
class Player
{
public:
	Player();
	~Player();
	void Update();
	void Move();
	void Turn();
	void Draw();
	void ChangeState();
	void SetPosition(CVector3 pos) {
		m_position = pos;
		m_charaCon.SetPosition(m_position);
	}
	CVector3 GetPosition() {
		return m_position;
	}
	enum ActionState {
		State_Leveling,
		State_Mining,
		State_Fill
	};
	ActionState ActState = State_Mining;
	enum PlayerState {
		PSTATE_CRAFT,
		PSTATE_MAKEGROUND,
		PSTATE_RIDING
	};

	PlayerState m_enPState = PSTATE_CRAFT;
private:
	int mi_state = 0;
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation;
	float m_moveSpeedParam = 600.0f;
	CVector3 m_moveSpeed = CVector3::Zero();
	Animation m_animation;
	AnimationClip m_animationClip[1];
	CharacterController m_charaCon;
};

