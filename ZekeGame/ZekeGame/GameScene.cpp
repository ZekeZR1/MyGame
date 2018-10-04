#include "stdafx.h"
#include "GameScene.h"
#include "BackGround.h"
#include "Player.h"
#include "ActionMenu.h"
#include "Item/Item.h"
#include "Item/IConstructor.h"
#include "Materials\Iron.h"
#include "Inventory.h"
#include "Item/ExplorationRocket.h"
#include "ArrangeIron.h"
#include "Item/Hover.h"
#include "Item/MiningMachine.h"
#include "Item/IBase.h"
#include "Item/Windmill.h"
#include "SearchRate.h"
#include "TheShip.h"
#include "Title.h"
#include "ClearScene.h"
#include "sound/SoundEngine.h"

GameScene* g_game = nullptr;
extern GameCamera* camera;

GameScene::GameScene()
{
	g_game = this;
	
	m_inventory = new Inventory;
	m_ActMenu = new ActionMenu;
	bg = new BackGround;
	m_player = new Player;
	m_model = new SkinModel;
	m_model->Init(L"Assets/modelData/Space.cmo");
	m_model->UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_ship = new TheShip(m_player);
	//Wall
	m_wall.Init(L"Assets/modelData/Wall.cmo");
	m_wall.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_wallPhysics.CreateMeshObject(m_wall, CVector3::Zero(), CQuaternion::Identity());
	//DrilPos
	m_drilmodel = new SkinModel;
	m_drilmodel->Init(L"Assets/modelData/DrilPos.cmo",enFbxUpAxisY);
	//Sprite
	mS_ActState = new Sprite;
	mS_ActState->Init(L"sprite/None_Sprite.dds", 500.0f, 500.0f);
	mv_ActSpos.x = 500.0f;
	mv_ActSpos.y -= 250.0f;
	mS_ActState->Update(mv_ActSpos, CQuaternion::Identity(), CVector3::One(), { 0.5,0.5 });
	mS_SettingItem = new Sprite;
	mS_SettingItem->Init(L"sprite/None_Sprite.dds",500.0f, 500.0f);
	mS_SettingItem->Update(mv_ActSpos, CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
	//Items
	for (int i = 0; i < MAXITEM; i++) {
		m_items[i] = nullptr;
	}
	//Materials
	for (int i = 0; i < IRONS; i++) {
		m_irons[i] = new ArrangeIron(m_player, m_inventory);
	}

	m_sound.Init(L"Assets/sound/Buff.wav",true);
}

GameScene::~GameScene()
{
	delete m_ship;
	delete m_inventory;
	for (int i = 0; i < IRONS; i++) {
		delete m_irons[i];
	}
	delete m_player;
	delete bg;
	delete m_model;
	delete mS_ActState;
	delete m_ActMenu;
	delete m_drilmodel;
	delete m_rocket;
	if (m_pConstructor != nullptr) {
		delete m_pConstructor;
		m_pConstructor = nullptr;
	}
	for (int i = 0; i < MAXITEM; i++) {
		if (m_items[i] != nullptr) {
			delete m_items[i];
			m_items[i] = nullptr;
		}
	}
	g_game = nullptr;
}

void GameScene::Update() {
	if (g_pad[0].IsTrigger(enButtonA)) {
		m_sound.Play();
	}
	m_sound.Update();
	ItemOrder();
	CreateItem();
	Craft();
	Ground();
	Menu();
	m_player->Update();
	m_searchRate.Update();
	if (m_inventory->m_nIron >= 20) {
		if (!isSearchedIron) {
			m_searchRate.addMaterialRate();
			isSearchedIron = true;
		}
	}
	if (m_inventory->m_nSilicon >= 20) {
		if (!isSearchedSilicon) {
			m_searchRate.addMaterialRate();
			isSearchedSilicon = true;
		}
	}
	camera->Update(m_player);
	for (int i = 0; i < IRONS; i++) {
		m_irons[i]->Update();
	}

	for (int i = 0; i < m_nItem; i++) {
		if (m_items[i] != nullptr) {
			m_items[i]->Update();
		}
	}
	if (m_pConstructor != nullptr) {
		m_pConstructor->Update();
	}
	m_ship->Update();
	Clear();
}

void GameScene::Draw() {
	bg->Draw();
	m_player->Draw();
	m_model->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
	for (int i = 0; i < IRONS; i++) {
		m_irons[i]->Draw();
	}
	for (int i = 0; i < m_nItem; i++) {
		if (m_items[i] != nullptr) {
			m_items[i]->Draw();
		}
	}
	
	if (m_pConstructor != nullptr)
		m_pConstructor->Draw();
	if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_MAKEGROUND) {
		m_drilmodel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
	}
	m_ship->Draw();

	//Žè‘O‚É•`‰æ‚µ‚½‚¢•¨
	m_searchRate.DrawSprite();
	m_player->DrawSprite();
	for (int i = 0; i < m_nItem; i++) {
		if (m_items[i] != nullptr) {
			m_items[i]->DrawSprite();
		}
	}
	mS_SettingItem->Draw();
	if (m_ActMenu->isOpenAct) {
			m_ActMenu->Draw(m_inventory);
	}
	if (m_pConstructor != nullptr)
		m_pConstructor->DrawSprite();
	mS_ActState->Draw();
}

void GameScene::Ground() {
	DrilRange();
	if (g_pad[0].IsPress(enButtonB)) {
		if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_MAKEGROUND) {
			if (m_player->isLowBattery)
				return;
			m_player->UseBattery();
			bg->m_converting = true;
			bg->Update(forward, m_ActMenu->m_flatPos, m_player);
			m_searchRate.addGroundRate();
		}
	}
	else {
		deep = 0.0f;
	}

}

void GameScene::Menu() {
	//ActMenu
	if (m_pConstructor != nullptr && m_pConstructor->isOpenMenu) {
		m_ActMenu->isOpenAct = false;
		return;
	}
	if (g_pad[0].IsTrigger(enButtonX)) {
		if (m_ActMenu->isOpenAct) {
			//m_player->m_enPState = m_player->PSTATE_WALK;
			m_ActMenu->isOpenAct = false;
			m_player->CloseMenu();
		}
		else {
			//m_player->m_enPState = m_player->PSTATE_CRAFT;
			if (!m_player->isOpenMenuNow) {
				m_ActMenu->isOpenAct = true;
				m_player->OpenMenu();
			}
		}
	}
	if (m_ActMenu->isOpenAct) {
		m_ActMenu->Update(m_player);
	}
	if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_CRAFT) {
		if (m_pConstructor != nullptr) {
			mS_ActState->Init(L"sprite/ItemBoxUsing.dds", 500.0f, 500.0f);
		}
		else {
			mS_ActState->Init(L"sprite/ItemBoxSprite.dds", 500.0f, 500.0f);
		}
	}
	if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_INVENTORY) {
		mS_ActState->Init(L"sprite/None_Sprite.dds", 500.0f, 500.0f);
	}
	if (m_player->m_enPState == m_player->PSTATE_MAKEGROUND) {
		if (m_player->ActState == m_player->State_Leveling) {
			mS_ActState->Init(L"sprite/ActState_Flat.dds", 500.0f, 500.0f);
		}
		if (m_player->ActState == m_player->State_Fill) {
			mS_ActState->Init(L"sprite/ActState_Fill.dds", 500.0f, 500.0f);
		}
		if (m_player->ActState == m_player->State_Mining) {
			mS_ActState->Init(L"sprite/ActState_Mining.dds", 500.0f, 500.0f);
		}
	}
	if (m_player->m_enPState == m_player->PSTATE_WALK) {
		mS_ActState->Init(L"sprite/None_Sprite.dds", 500.0f, 500.0f);
	}
	mS_ActState->Update(mv_ActSpos, CQuaternion::Identity(), { 0.5f,0.5f,0.5f }, { 0.5,0.5 });
	if (g_pad[0].IsTrigger(enButtonY)) {
		m_player->m_enPState = m_player->PSTATE_WALK;
		m_ActMenu->m_enAction = m_ActMenu->ASTATE_INVENTORY;
		m_ActMenu->m_mode = 1;
	}
}

void GameScene::DrilRange() {
	forward = camera3d->GetForward();
	forward.y = 0;
	forward.Normalize();
	if (m_player->ActState == m_player->State_Leveling) {
		forward *= 0.0f;
	}
	else {
		CVector3 camerapos = camera3d->GetPosition();
		CVector3 playerpos = m_player->GetPosition();
		CVector3 toCamera = camerapos - playerpos;
		float MaxCameraHeight = 650.0f;
		forward *= (MaxCameraHeight - toCamera.y);
	}
	forward += m_player->GetPosition();
	//DrilPos
	switch (m_player->ActState) {
	case 0:
		m_drilmodel->Init(L"Assets/modelData/FlatRange.cmo", enFbxUpAxisY);
		break;
	case 1:
		m_drilmodel->Init(L"Assets/modelData/DrilPos.cmo", enFbxUpAxisY);
		if (bg->m_converting) {
			if (deep < 200)
				deep += 4.0f;
			forward.y -= deep;
		}
		break;
	case 2:
		m_drilmodel->Init(L"Assets/modelData/DrilPos.cmo", enFbxUpAxisY);
		if (bg->m_converting) {
			if (deep < 200)
				deep += 4.0f;
			forward.y += deep;
			break;
		}
	}
	m_drilmodel->UpdateWorldMatrix(forward, CQuaternion::Identity(), CVector3::One());
}

void GameScene::Craft() {
	if (m_pConstructor != nullptr) {
		if (m_pConstructor->isGoAway) {
			delete m_pConstructor;
			m_pConstructor = nullptr;
		}
	}
	if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_CRAFT) {
		if (g_pad[0].IsTrigger(enButtonB)) {
			if (m_pConstructor == nullptr) {
				m_pConstructor = new IConstructor(m_player,m_inventory);
				m_player->m_enPState = m_player->PSTATE_WALK;
				m_ActMenu->m_enAction = m_ActMenu->ASTATE_INVENTORY;
				char message[256];
				sprintf_s(message, "CLOSE Act\n");
				OutputDebugStringA(message);
				if (m_ActMenu->isOpenAct) {
					m_ActMenu->isOpenAct = false;
					m_player->CloseMenu();
				}
			}
		}
	}
}

void GameScene::ItemOrder() {
		if (m_pConstructor == nullptr)
			return;
		if (m_pConstructor->isOrder[ITEM::en_ROCKET]) {
			m_ordered = ITEM::en_ROCKET;
			mS_SettingItem->Init(L"sprite/ExRocket.dds", 250.0f, 250.0f);
			m_settingOrderedItem = true;
			SetItem();
		}
		if (m_pConstructor->isOrder[ITEM::en_HOVER]) {
			m_ordered = ITEM::en_HOVER;
			mS_SettingItem->Init(L"sprite/Hover.dds", 250.0f, 250.0f);
			m_settingOrderedItem = true;
			SetItem();
		}
		if (m_pConstructor->isOrder[ITEM::en_MINING]) {
			m_ordered = ITEM::en_MINING;
			mS_SettingItem->Init(L"sprite/ItemMining.dds", 250.0f, 250.0f);
			m_settingOrderedItem = true;
			SetItem();
		}
		if (m_pConstructor->isOrder[ITEM::en_BASE]) {
			m_ordered = ITEM::en_BASE;
			mS_SettingItem->Init(L"sprite/Base.dds", 250.0f, 250.0f);
			m_settingOrderedItem = true;
			SetItem();
		}
		if (m_pConstructor->isOrder[ITEM::en_WINDMILL]) {
			m_ordered = ITEM::en_WINDMILL;
			mS_SettingItem->Init(L"sprite/Windmill.dds", 250.0f, 250.0f);
			m_settingOrderedItem = true;
			SetItem();
		}
}

void GameScene::CreateItem() {
	if (!m_isOrderedItemSet)
		return;
	if (m_nItem >= MAXITEM)
		return;
	switch (m_ordered) {
	case ITEM::en_ROCKET:
		m_items[m_nItem] = reinterpret_cast<Item*>(new ExplorationRocket(m_player, m_inventory));
		m_pConstructor->isOrder[ITEM::en_ROCKET] = false;
		m_inventory->UseMaterial(ITEM::en_ROCKET);
		m_ordered = ITEM::en_NONE;
		m_nItem++;
		break;
	case ITEM::en_HOVER:
		m_items[m_nItem] = reinterpret_cast<Item*>(new Hover(m_player, m_inventory));
		m_pConstructor->isOrder[ITEM::en_HOVER] = false;
		m_inventory->UseMaterial(ITEM::en_HOVER);
		m_nItem++;
		break;
	case ITEM::en_MINING:
		m_items[m_nItem] = reinterpret_cast<Item*>(new MiningMachine(m_player, m_inventory));
		m_pConstructor->isOrder[ITEM::en_MINING] = false;
		m_inventory->UseMaterial(ITEM::en_MINING);
		m_nItem++;
		break;
	case ITEM::en_BASE:
		m_items[m_nItem] = reinterpret_cast<Item*>(new IBase(m_player));
		m_pConstructor->isOrder[ITEM::en_BASE] = false;
		m_inventory->UseMaterial(ITEM::en_BASE);
		m_nItem++;
		break;
	case ITEM::en_WINDMILL:
		m_items[m_nItem] = reinterpret_cast<Item*>(new Windmill(m_player));
		m_pConstructor->isOrder[ITEM::en_WINDMILL] = false;
		m_inventory->UseMaterial(ITEM::en_WINDMILL);
		m_searchRate.addSearchRate(Item::en_WINDMILL);
		m_nItem++;
		break;
	}
	m_isOrderedItemSet = false;
}

void GameScene::SetItem() {
	if (g_pad[0].IsTrigger(enButtonB)) {
		m_settingOrderedItem = false;
		m_isOrderedItemSet = true;
		mS_SettingItem->Init(L"sprite/None_Sprite.dds", 500.0f, 500.0f);
	}
}

void GameScene::Clear() {
	//if (m_searchRate.isAllMax && !isGameClear) {
	if(g_pad[0].IsTrigger(enButtonLB1)){
		isGameClear = true;
		m_ship->GoDown();
	}
	if (m_ship->isInSpace) {
		camera->Reset();
		currentScene = new ClearScene;
		delete this;
	}
}