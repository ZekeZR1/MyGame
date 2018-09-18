#pragma once
#include "IScene.h"
#include "BackGround.h"
#include "Player.h"
#define MAXITEM 100
#define IRONS 20

class ActionMenu;
class Iron;
class ArrangeIron;
class IConstructor;
class Inventory;
class ExplorationRocket;

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
	//void addSearchRate();
private:
	void ItemOrder();
	int SearchRate = 0;
	Sprite m_SearchRate;
	CVector3 m_ratePos = CVector3::Zero();
	IConstructor* m_pConstructor;
	ArrangeIron* m_irons[50];
	ExplorationRocket* m_rocket = nullptr;
	CVector3 forward = CVector3::Zero();
	Inventory* m_inventory;
	SkinModel * m_model;
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
	enum ItemState {
		en_STANDBY,
		en_SETTING,
		en_SET
	};
	ItemState m_itemState = en_STANDBY;
	enum OrderedItem {
		en_NONE,
		en_ROCKET,
		en_HOVER,
		en_MINING
	};
	OrderedItem m_ordered = en_NONE;
};

extern GameScene* g_game;