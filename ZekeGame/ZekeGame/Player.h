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
	void DrawSprite();
	void ChangeState();
	void ChargeBattery();
	bool isNear(CVector3 thatpos, float dist);
	void UseBattery();
	bool isOpenMenuNow = false;
	bool OpenMenuNow = false;
	void OpenMenu();
	void CloseMenu();
	bool CanOpenMenu();
	bool isLowHoverBattery = false;
	CQuaternion GetRot() {
		return m_rotation;
	}
	unsigned int m_nMenu = 0;
	CVector3 GetForward(float param) {
		CVector3 forward = camera3d->GetForward();
		forward.y = 0;
		forward.Normalize();
		forward *= param;
		forward += m_position;
		return forward;
	}
	void SetPosition(CVector3 pos) {
		m_position = pos;
		m_charaCon->SetPosition(m_position);
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
		PSTATE_WALK,
		PSTATE_CRAFT,
		PSTATE_MAKEGROUND,
		PSTATE_SETTING,
		PSTATE_RIDING
	};
	PlayerState m_enPState = PSTATE_WALK;
	bool isRiding = false;
	bool isMaxBattery = true;
	bool isLowBattery = false;
	CVector3 GetMoveSpeed() {
		return m_moveSpeed;
	}
private:
	int mi_state = 0;
	int m_battery = 1000;
	float mf_batteryX = 300.0f;
	float mf_batteryY = 50.0f;
	void CharaconUpdate();
	void Gauge();
	bool isCharaConRide = false;
	Sprite* ms_battery;
	Sprite ms_bFrame;
	CVector3 m_batteryPos = CVector3::Zero();
	CVector3 m_bFramePos = CVector3::Zero();
	CVector3 m_batteryScale = CVector3::One();
	SkinModel m_model;
	CVector3 m_position = CVector3::Zero();
	CQuaternion m_rotation;
	//float m_moveSpeedParam = 600.0f;
	float m_moveSpeedParam = 7000.0f;
	CVector3 m_moveSpeed = CVector3::Zero();
	Animation m_animation;
	AnimationClip m_animationClip[1];
	CharacterController* m_charaCon;
};

