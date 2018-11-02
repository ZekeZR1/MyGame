#pragma once
class ActionMenu
{
public:
	ActionMenu();
	~ActionMenu();
	void Update(Player* m_player);
	void Craft();
	void Draw();
	CVector3 m_flatPos = { 0.0f,100.0f,0.0f };
	enum Action {
		ASTATE_INVENTORY,
		ASTATE_CRAFT,
		ASTATE_MAKEGROUND
	};
	Action m_enAction = ASTATE_INVENTORY;
	int m_mode = 1;
private:
	Sprite* m_ActMenu;
	Sprite* mS_Item;
	CVector3 m_ActPos = CVector3::Zero();
};

