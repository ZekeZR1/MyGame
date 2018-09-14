#pragma once
#define MININGTIME 50
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
	Popup m_popup;
	Player * mp_player = nullptr;
	Sprite ms_menu;
	Inventory* mp_inventory = nullptr;
	SkinModel m_MiningMachine;
	CVector3 m_pos = CVector3::Zero();
	PhysicsStaticObject m_physicsStaticObject;
	bool isOpenMenu = false;
	bool isMining = false;
	bool isGot = false;
	int mn_mining = 0;
};