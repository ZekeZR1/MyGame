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
	SkinModel m_model;
	CVector3 m_pos = CVector3::Zero();
	Player* mp_player = nullptr;
	PhysicsStaticObject m_physicsStaticObject;
};


