#pragma once
#define NUMITEM 4
#include "physics\PhysicsStaticObject.h"

class Inventory;
class Player;

class IConstructor
{
public:
	IConstructor(Player* player,Inventory* inventory);
	~IConstructor();
	void Update();
	void Draw();
	void DrawSprite();
	void SetPosition(CVector3 pos) {
		m_pos = pos;
		m_skinModel->UpdateWorldMatrix(pos, CQuaternion::Identity(), CVector3::One());
	};
	bool isOpenMenu = false;
	bool isGoAway = false;
	bool isOrder[NUMITEM] = { false };
private:
	void Menu();
	void OpenMenu();
	void CloseMenu();
	void PutAway();
	void Crafting();
	void Choise();
	void SetRocket();
	void SetHover();
	void SetMining();
	void SetBase();
	void SetWindmill();
	SkinModel * m_skinModel;
	CVector3 m_pos = CVector3::Zero();
	Sprite* mS_ItemMenu;
	CVector3 m_MenuPos = CVector3::Zero();
	Sprite* mS_ItemPre;
	CVector3 m_ItemPrePos = CVector3::Zero();
	int ItemNumber = 0;
	Player* mp_player = nullptr;
	PhysicsStaticObject* m_physicsStaticObject;
	CFONT mf_itemName;
	CFONT mf_materialName;
	CFONT mf_bMaterial;
	CFONT mf_aMaterial;
	bool isDrawFont = false;
	wchar_t mw_bCraft[256];
	wchar_t mw_aCraft[256];
	CVector3 m_bFontpos = CVector3::Zero();
	CVector3 m_aFontpos = CVector3::Zero();
	CVector3 m_mNamePos = CVector3::Zero();
	CVector3 m_iNamePos = CVector3::Zero();
	bool isOpenNow = false;
	Inventory* mp_inventory;
};

