#pragma once
class Player;
class IBase : public Item
{
public:
	IBase(Player* player);
	~IBase();
	void Update() override;
	void Draw() override;
	void DrawSprite() override;
private:
	void InOut();
	SkinModel m_model;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_setPlayerPos;
	CQuaternion m_rot = CQuaternion::Identity();
	Player* mp_player = nullptr;
	PhysicsStaticObject m_physicsStaticObject;
	bool isIn = false;
};


