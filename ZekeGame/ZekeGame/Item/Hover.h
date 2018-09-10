#pragma once
class Player;
class Inventory;

class Hover : public Item
{
public:
	Hover(Player* player, Inventory* inventory);
	~Hover() override;
	void Update() override;
	void Draw() override;
	void DrawSprite() override;
private:
	void MoveAndRotation();
	void Physics();
	bool isRideNow = false;
	Player * mp_player = nullptr;
	Inventory* mp_inventory = nullptr;
	SkinModel* m_hoverModel;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_moveSpeed = CVector3::Zero();
	PhysicsStaticObject* m_physicsStaticObject;
	bool isRiding = false;
};

