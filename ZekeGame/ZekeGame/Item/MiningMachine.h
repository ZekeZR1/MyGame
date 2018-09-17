#pragma once
class Player;
class Inventory;

class MiningMachine : public Item{
public:
	MiningMachine(Player* player,Inventory* inventory);
	~MiningMachine();
	void Update() override;
	void Draw() override;
	void DrawSprite() override;
private:
	void OpenClose();
	void Menu();
	void Mining();
	void CastFont();
	Popup m_popup;
	Player * mp_player = nullptr;
	Sprite ms_menu;
	Sprite ms_frame;
	Sprite ms_gauge;
	CVector3 m_gaugePos = CVector3::Zero();
	CVector3 m_gaugeScale = CVector3::One();
	Inventory* mp_inventory = nullptr;
	SkinModel m_MiningMachine;
	CVector3 m_pos = CVector3::Zero();
	PhysicsStaticObject m_physicsStaticObject;
	bool isOpenMenu = false;
	bool isMining = false;
	bool isGot = false;
	bool isOpendNow = true;
	float  mn_mining = 0.0;
	float  mn_miningTime = 500.0f;
};