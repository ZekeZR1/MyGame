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
	//Rate
	m_SearchRate.Init(L"sprite/testgauge.dds", 150.0f, 150.0f);
	m_ratePos.x -= 550.0f;
	m_ratePos.y += 270.0f;
	m_SearchRate.Update(m_ratePos, CQuaternion::Identity(), CVector3::One(), { 0.5,0.5 });
	m_mask.Init(L"sprite/testmask.dds", 500.0f, 500.0f);
	m_maskPos = m_ratePos;
	m_mask.Update(m_maskPos, CQuaternion::Identity(), CVector3::One(), { 0.5,0.5 });
	/*
	smodel = new SkinModel;
	smodel->Init(L"Assets/modelData/testbox.cmo");
	aniclip[0].Load(L"Assets/modelData/testbox.tka");
	aniclip[0].SetLoopFlag(true);
	modelanimation.Init(
		*smodel,
		aniclip,
		1
	);
	*/
}

GameScene::~GameScene()
{
	g_game = nullptr;
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
	if (m_pConstructor != nullptr)
		delete m_pConstructor;
	for (int i = 0; i < MAXITEM; i++) {
		if (m_items[i] != nullptr) {
			delete m_items[i];
		}
	}
}

void GameScene::Update() {
	ItemOrder();
	Craft();
	Ground();
	Menu();
	m_player->Update();
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
		m_pConstructor->Update(m_inventory);
	}
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
	//Žè‘O‚É•`‰æ‚µ‚½‚¢•¨
	m_player->DrawSprite();
	m_SearchRate.Draw();
	m_mask.Draw();
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
				m_pConstructor = new IConstructor(m_player);
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
	if (m_pConstructor->isOrderRocket) {
		m_ordered = en_ROCKET;
		m_settingOrderedItem = true;
	}
	if (m_pConstructor->isOrderHover) {
		m_ordered = en_HOVER;
		m_settingOrderedItem = true;
	}
	if (m_pConstructor->isOrderMining) {
		m_ordered = en_MINING;
		m_settingOrderedItem = true;
	}
	if (m_pConstructor->isOrderBase) {
		m_ordered = en_BASE;
		m_settingOrderedItem = true;
	}
	if (!m_settingOrderedItem) {
		mS_SettingItem->Init(L"sprite/None_Sprite.dds", 500.0f, 500.0f);
		return;
	}
	switch (m_ordered) {
	case en_ROCKET:
		mS_SettingItem->Init(L"sprite/ExRocket.dds", 250.0f, 250.0f);
		SetItem();
		break;
	case en_HOVER:
		mS_SettingItem->Init(L"sprite/Hover.dds", 250.0f, 250.0f);
		SetItem();
		break;
	case en_MINING:
		mS_SettingItem->Init(L"sprite/ItemMining.dds", 250.0f, 250.0f);
		SetItem();
		break;
	case en_BASE:
		mS_SettingItem->Init(L"sprite/Base.dds", 250.0f, 250.0f);
		SetItem();
	}

	if (!m_isOrderedItemSet)
		return;
	if (m_nItem >= MAXITEM)
		return;
	switch (m_ordered) {
	case en_ROCKET:
		m_items[m_nItem] = reinterpret_cast<Item*>(new ExplorationRocket(m_player,m_inventory));
		m_pConstructor->isOrderRocket = false;
		m_inventory->UseMaterial(en_ROCKET);
		m_nItem++;
		break;
	case en_HOVER:
		m_items[m_nItem] = reinterpret_cast<Item*>(new Hover(m_player, m_inventory));
		m_pConstructor->isOrderHover = false;
		m_inventory->UseMaterial(en_HOVER);
		m_nItem++;
		break;
	case en_MINING:
		m_items[m_nItem] = reinterpret_cast<Item*>(new MiningMachine(m_player, m_inventory));
		m_pConstructor->isOrderMining = false;
		m_inventory->UseMaterial(en_MINING);
		m_nItem++;
		break;
	case en_BASE:
		m_items[m_nItem] = reinterpret_cast<Item*>(new IBase(m_player));
		m_pConstructor->isOrderBase = false;
		m_inventory->UseMaterial(en_BASE);
		m_nItem++;
		break;
	}

	m_isOrderedItemSet = false;
}

void GameScene::SetItem() {
	if (g_pad[0].IsTrigger(enButtonB)) {
		m_settingOrderedItem = false;
		m_isOrderedItemSet = true;
	}
}