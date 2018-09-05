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

GameScene* g_game = nullptr;
extern GameCamera* camera;

GameScene::GameScene()
{
	/*Effect
	manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
	manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
	manager->SetRingRenderer(renderer->CreateRingRenderer());
	manager->SetTrackRenderer(renderer->CreateTrackRenderer());
	manager->SetModelRenderer(renderer->CreateModelRenderer());

	manager->SetTextureLoader(renderer->CreateTextureLoader());
	manager->SetCoordinateSystem(Effekseer::CoordinateSystem::RH);
	*/
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
	//Font
	pSpriteBatch = new DirectX::SpriteBatch(g_graphicsEngine->GetD3DDeviceContext());
	pSpriteFont = new DirectX::SpriteFont(g_graphicsEngine->GetD3DDevice(), L"Assets/font/myfile.spritefont");
	//Sprite
	mS_ActState = new Sprite;
	mS_ActState->Init(L"sprite/None_Sprite.dds", 500.0f, 500.0f);
	mv_ActSpos.x = 500.0f;
	mv_ActSpos.y = 280.0f;
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
	/*Effect
	// エフェクトを解放します。再生中の場合は、再生が終了した後、自動的に解放されます。
	ES_SAFE_RELEASE(effect);
	// エフェクト管理用インスタンスを破棄
	manager->Destroy();
	// 描画用インスタンスを破棄
	renderer->Destroy();
	*/
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
	delete pSpriteBatch;
	delete pSpriteFont;
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
	/*Effect
	if (g_pad[0].IsTrigger(enButtonA)) {
		//effect = Effekseer::Effect::Create(manager, filepath);
		handle = manager->Play(effect, 0.0f,0.0f,0.0f);
	}
	renderer->SetProjectionMatrix(::Effekseer::Matrix44);
	renderer->SetCameraMatrix(camera3d->GetViewMatrix());
	manager->AddLocation(handle, ::Effekseer::Vector3D);
	manager->Update();
	*/
	ItemOrder();
	Craft();
	Ground();
	CastFont();
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
	/*Effect
	renderer->BeginRendering();
	manager->Draw();
	renderer->EndRendering();
	*/
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
	//手前に描画したい物
	for (int i = 0; i < m_nItem; i++) {
		if (m_items[i] != nullptr) {
			m_items[i]->DrawSprite();
		}
	}
	mS_ActState->Draw();
	mS_SettingItem->Draw();
	if (isOpenAct) {
			m_ActMenu->Draw();
	}
	if (m_pConstructor != nullptr)
		m_pConstructor->DrawSprite();
}

void GameScene::DrawFont() {
	pSpriteBatch->Begin();
	//X座標
	pSpriteFont->DrawString(pSpriteBatch, L"X", DirectX::XMFLOAT2(0.0f, 0.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosX), DirectX::XMFLOAT2(50.0f, 0.0f), CVector4::White);
	//Y座標
	pSpriteFont->DrawString(pSpriteBatch, L"Y", DirectX::XMFLOAT2(0.0f, 50.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosY), DirectX::XMFLOAT2(50.0f, 50.0f), CVector4::White);
	//Z座標
	pSpriteFont->DrawString(pSpriteBatch, L"Z", DirectX::XMFLOAT2(0.0f, 100.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosZ), DirectX::XMFLOAT2(50.0f, 100.0f), CVector4::White);
	//整地座標
	if (isOpenAct) {
		//if (m_player->m_enPState == m_player->PSTATE_MAKEGROUND)
		if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_MAKEGROUND)
			//360
			pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_flatPosY), DirectX::XMFLOAT2(640.0f, 240.0f), CVector4::White);
		if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_INVENTORY) {
			pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_Iron), DirectX::XMFLOAT2(640.0f, 360.0f), CVector4::White);
		}
	}
	pSpriteBatch->End();
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
				if(isOpenAct){
					isOpenAct = false;
					m_player->CloseMenu();
				}
			}
		}
	}
}

void GameScene::Ground() {
	DrilRange();
	if (g_pad[0].IsPress(enButtonB)) {
		if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_MAKEGROUND) {
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
		isOpenAct = false;
		return;
	}
	if (g_pad[0].IsTrigger(enButtonX)) {
		if (isOpenAct) {
			//m_player->m_enPState = m_player->PSTATE_WALK;
			isOpenAct = false;
			m_player->CloseMenu();
		}
		else {
			//m_player->m_enPState = m_player->PSTATE_CRAFT;
			if (!m_player->isOpenMenuNow) {
				isOpenAct = true;
				m_player->OpenMenu();
			}
		}
	}
	if (isOpenAct) {
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
	//Walkに移行
	if (g_pad[0].IsTrigger(enButtonY)) {
		m_player->m_enPState = m_player->PSTATE_WALK;
		m_ActMenu->m_enAction = m_ActMenu->ASTATE_INVENTORY;
		m_ActMenu->m_mode = 1;
	}
}

void GameScene::CastFont() {
	//プレイヤー座標
	CVector3 Ppos = m_player->GetPosition();
	mi_x = Ppos.x;
	_itow_s(mi_x, mw_PosX, 10);
	mi_y = Ppos.y;
	_itow_s(mi_y, mw_PosY, 10);
	mi_z = Ppos.z;
	_itow_s(mi_z, mw_PosZ, 10);
	//整地座標
	mi_flaty = m_ActMenu->m_flatPos.y;
	_itow_s(mi_flaty, mw_flatPosY, 10);
	_itow_s(m_inventory->m_nIron, mw_Iron, 10);
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

void GameScene::ItemOrder() {
	if (m_pConstructor != nullptr) {
		if (m_pConstructor->isOrderRocket) {
			m_ordered = en_ROCKET;
			m_settingOrderedItem = true;
		}
	}
	if (m_settingOrderedItem) {
		switch (m_ordered) {
		case en_ROCKET:
			mS_SettingItem->Init(L"sprite/ExRocket.dds", 500.0f, 500.0f);
			if (g_pad[0].IsTrigger(enButtonB)) {
				m_settingOrderedItem = false;
				m_isOrderedItemSet = true;
			}
			break;
		}
	}
	else {
		mS_SettingItem->Init(L"sprite/None_Sprite.dds", 500.0f, 500.0f);
	}
	if (m_isOrderedItemSet) {
		CVector3 rocketpos = m_player->GetPosition();
		if (m_nItem < MAXITEM) {
			m_items[m_nItem] = reinterpret_cast<Item*>(new ExplorationRocket(m_player));
			m_pConstructor->isOrderRocket = false;
			m_inventory->UseMaterial(en_ROCKET);
			m_nItem++;
		}
		m_isOrderedItemSet = false;
	}
}