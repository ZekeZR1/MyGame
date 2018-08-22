#pragma once
class Inventory;
class Player;

class IConstructor 
{
public:
	IConstructor(Player* player);
	~IConstructor();
	void Update(Inventory* m_inventory) ;
	void Draw() ;
	void DrawSprite();
	void Menu();
	void Crafting(Inventory* m_inventory);
	void SetPosition(CVector3 pos) ;
	void PutAway(Player* m_player) ;
	bool isGoAway = false;
	bool isOpenMenu = false;
private:
	SkinModel * m_skinModel;
	CVector3 m_pos = CVector3::Zero();
	Sprite* mS_ItemMenu;
	CVector3 m_MenuPos = CVector3::Zero();
	int ItemNumber = 0;
	Player* mp_player = nullptr;
};

