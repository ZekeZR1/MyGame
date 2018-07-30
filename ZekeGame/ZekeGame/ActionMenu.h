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
private:
	Sprite* m_ActMenu;
	Sprite* mS_Item;
	CVector3 m_ActPos = CVector3::Zero();
};

