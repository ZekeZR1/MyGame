#pragma once
#include "physics\PhysicsStaticObject.h"

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
	void SetPosition(CVector3 pos) ;
	bool isGoAway = false;
	bool isOpenMenu = false;
	bool isOrderRocket = false;
	bool isOrderHover = false;
private:
	void Menu();
	void OpenMenu();
	void CloseMenu();
	void PutAway();
	void Crafting(Inventory* m_inventory);
	SkinModel * m_skinModel;
	CVector3 m_pos = CVector3::Zero();
	Sprite* mS_ItemMenu;
	CVector3 m_MenuPos = CVector3::Zero();
	Sprite* mS_ItemPre;
	CVector3 m_ItemPrePos = CVector3::Zero();
	int ItemNumber = 0;
	Player* mp_player = nullptr;
	PhysicsStaticObject* m_physicsStaticObject;
	CFONT mf_bMaterial;
	CFONT mf_aMaterial;
	bool isDrawFont = false;
	wchar_t mw_bCraft[256];
	wchar_t mw_aCraft[256];
	CVector3 m_bFontpos = CVector3::Zero();
	CVector3 m_aFontpos = CVector3::Zero();
	bool isOpenNow = false;
};
