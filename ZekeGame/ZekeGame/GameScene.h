#pragma once
#include "IScene.h"
#include "BackGround.h"
#include "Player.h"
#include "SearchRate.h"

#define MAXITEM 100
#define IRONS 20
#define ITEM Item

class ActionMenu;
class Iron;
class ArrangeIron;
class IConstructor;
class Inventory;
class ExplorationRocket;
class SearchRate;
class TheShip;

class GameScene : public IScene
{
public:
	GameScene();
	virtual ~GameScene() override;
	void Update() override;
	void Draw() override;
	void Craft();
	void Ground();
	void Menu();
	bool Converting = false;
	//bool isOpenAct = false;
	void DrilRange();
	ActionMenu* m_ActMenu = nullptr;
	Player* m_player = nullptr;
private:
	TheShip* m_ship;
	void ItemOrder();
	void CreateItem();
	void SetItem();
	bool isSearchedIron = false;
	bool isSearchedSilicon = false;
	SearchRate m_searchRate;
	IConstructor* m_pConstructor = nullptr;
	ArrangeIron* m_irons[50];
	ExplorationRocket* m_rocket = nullptr;
	CVector3 forward = CVector3::Zero();
	Inventory* m_inventory;
	SkinModel * m_model;
	SkinModel m_wall;
	PhysicsStaticObject m_wallPhysics;
	CVector3 m_spritePos = CVector3::Zero();
	float spweight = 100.0f, sphight = 100.0f;
	CVector3 m_spscale = { 1.0f,1.0f,1.0f };
	BackGround* bg;
	CVector3 modelPos = CVector3::Zero();
	Animation modelanimation;
	Sprite* mS_ActState;
	CVector3 mv_ActSpos = CVector3::Zero();
	Sprite* mS_SettingItem;
	//DrilPos
	SkinModel* m_drilmodel;
	float deep = 0.0f;
	//constructor
	bool m_settingConstructor = false;
	bool m_setConstructor = false;
	//ItemList
	int m_nItem = 0;
	bool m_settingOrderedItem = false;
	bool m_isOrderedItemSet = false;
	Item* m_items[MAXITEM];
	
	ITEM::EnItem m_ordered = ITEM::en_NONE;
};

extern GameScene* g_game;

