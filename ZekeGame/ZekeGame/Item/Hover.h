#pragma once
class Player;
class Inventory;

class Hover : public Item
{
public:
	Hover(Player* player, Inventory* inventory);
	~Hover();
	void Update() override;
	void Draw() override;
	void DrawSprite() override;
private:
	Player * mp_player = nullptr;
	Inventory* mp_inventory = nullptr;
	SkinModel m_hoverModel;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	PhysicsStaticObject* m_physicsStaticObject;
};

