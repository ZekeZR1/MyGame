#include "stdafx.h"
#include "GameScene.h"
#include "BackGround.h"
#include "level\Level.h"
#include "Player.h"
#include "ActionMenu.h"
#include "Item/Item.h"
#include "Item/IConstructor.h"
#include "Materials\Iron.h"
#include "Inventory.h"
#include "Item/ExplorationRocket.h"

GameScene* g_game = nullptr;
IConstructor* m_pConstructor;
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
	m_inventory = new Inventory;
	m_iron = new Iron;
	g_game = this;
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
	mv_ActSpos.y = 300.0f;
	mS_ActState->Update(mv_ActSpos, CQuaternion::Identity(), CVector3::One(), { 0.5,0.5 });
	mS_SettingItem = new Sprite;
	mS_SettingItem->Init(L"sprite/None_Sprite.dds",500.0f, 500.0f);
	mS_SettingItem->Update(mv_ActSpos, CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
	//
	//smodel = new SkinModel;
	//smodel->Init(L"Assets/modelData/testbox.cmo");
	//aniclip[0].Load(L"Assets/modelData/testbox.tka");
	//aniclip[0].SetLoopFlag(true);
	//modelanimation.Init(
//		*smodel,
		//aniclip,
		//1
	//);
}

GameScene::~GameScene()
{
	/*Effect
	// �G�t�F�N�g��������܂��B�Đ����̏ꍇ�́A�Đ����I��������A�����I�ɉ������܂��B
	ES_SAFE_RELEASE(effect);
	// �G�t�F�N�g�Ǘ��p�C���X�^���X��j��
	manager->Destroy();
	// �`��p�C���X�^���X��j��
	renderer->Destroy();
	*/
	g_game = nullptr;
	delete m_inventory;
	delete m_iron;
	delete m_player;
	delete bg;
	delete m_model;
	delete mS_ActState;
	delete m_ActMenu;
	delete pSpriteBatch;
	delete pSpriteFont;
	delete m_pConstructor;
	delete m_drilmodel;
	delete m_rocket;
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
	if (m_pConstructor != nullptr) {
		if (m_pConstructor->isOrderRocket) {
			m_ordered = en_ROCKET;
			m_settingOrderedItem = true;
			//m_pConstructor->isOpenMenu = false;
			//m_player->isOpenMenuNow = false;
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
	Craft();
	Ground();
	CastFont();
	Menu();
	m_player->Update();
//Debug Draw
	m_player->CanOpenMenu(); 
	/*
	if (m_player->isOpenMenuNow) {
		char message[256];
		sprintf_s(message, "TRUEEEEEEE\n");
		OutputDebugStringA(message);
	}
	else {
		char message[256];
		sprintf_s(message, "FALSEEEE\n");
		OutputDebugStringA(message);
	}
	*/
//
	for (int i = 0; i < m_nItem; i++) {
		if (m_items[i] != nullptr) {
			m_items[i]->Update();
		}
	}

	CVector3 camerapos = camera3d->GetPosition();
	CVector3 playerpos = m_player->GetPosition();
	if (camerapos.y <= playerpos.y) {
		camerapos.y = (playerpos.y + 1.0f);
		camera3d->SetPosition(camerapos);
	}
	camera->Update(m_player);
	if (m_pConstructor != nullptr) {
		m_pConstructor->Update(m_inventory);
	}

	if (m_iron != nullptr && m_iron->isGet){
		m_inventory->m_nIron++;
		m_iron = nullptr;
}
	if (m_iron != nullptr) {
		m_iron->Update(m_player);
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
	if (m_rocket != nullptr) {
		//m_rocket->Draw();
		//m_items[0]->Draw();
	}
	/*
	if (m_items[0] != nullptr) {
		m_items[0]->Draw();
	}
	*/
	for (int i = 0; i < m_nItem; i++) {
		if (m_items[i] != nullptr) {
			m_items[i]->Draw();
		}
	}
	for (int i = 0; i < m_nItem; i++) {
		if (m_items[i] != nullptr) {
			m_items[i]->DrawSprite();
		}
	}
	if (m_pConstructor != nullptr)
		m_pConstructor->Draw();
	if (m_iron != nullptr) {
		m_iron->Draw();
	}
	if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_MAKEGROUND) {
		m_drilmodel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
	}
	//��O�ɕ`�悵������
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
	//X���W
	pSpriteFont->DrawString(pSpriteBatch, L"X", DirectX::XMFLOAT2(0.0f, 0.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosX), DirectX::XMFLOAT2(50.0f, 0.0f), CVector4::White);
	//Y���W
	pSpriteFont->DrawString(pSpriteBatch, L"Y", DirectX::XMFLOAT2(0.0f, 50.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosY), DirectX::XMFLOAT2(50.0f, 50.0f), CVector4::White);
	//Z���W
	pSpriteFont->DrawString(pSpriteBatch, L"Z", DirectX::XMFLOAT2(0.0f, 100.0f), CVector4::White);
	pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_PosZ), DirectX::XMFLOAT2(50.0f, 100.0f), CVector4::White);
	//���n���W
	if (isOpenAct) {
		//if (m_player->m_enPState == m_player->PSTATE_MAKEGROUND)
		if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_MAKEGROUND)
			pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_flatPosY), DirectX::XMFLOAT2(640.0f, 360.0f), CVector4::Black);
		if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_INVENTORY) {
			pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_Iron), DirectX::XMFLOAT2(640.0f, 360.0f), CVector4::Black);
		}
	}
	pSpriteBatch->End();
}

void GameScene::Craft() {
	if (m_pConstructor != nullptr) {
		m_pConstructor->PutAway(m_player);
		if (m_pConstructor->isGoAway) {
			m_pConstructor = nullptr;
		}
	}
	//test
	if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_CRAFT) {
		if (g_pad[0].IsTrigger(enButtonB)) {
			if (m_pConstructor == nullptr) {
				m_pConstructor = new IConstructor(m_player);
				CVector3 ConstructorPos = m_player->GetForward(100.0f);
				m_pConstructor->SetPosition(ConstructorPos);
				m_player->m_enPState = m_player->PSTATE_WALK;
				m_ActMenu->m_enAction = m_ActMenu->ASTATE_INVENTORY;
				char message[256];
				sprintf_s(message, "CLOSE Act\n");
				OutputDebugStringA(message);
				//m_player->isOpenMenuNow = false;
				if(isOpenAct){
					isOpenAct = false;
					m_player->CloseMenu();
				}
			}
		}
	}
	/*
	if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_CRAFT) {
		if (g_pad[0].IsTrigger(enButtonB)) {
			//�I�񂾃A�C�e�����w�肵�����W�ɒu��
			if (m_player->m_enPState != m_player->PSTATE_SETTING) {
				if (m_pConstructor == nullptr) {
					m_pConstructor = new IConstructor(m_player);
					CVector3 forward = camera3d->GetForward();
					forward.y = 0;
					forward.Normalize();
					forward *= 100.0f;
					forward += m_player->GetPosition();
					m_pConstructor->SetPosition(forward);
					isOpenAct = false;
					m_player->m_enPState = m_player->PSTATE_WALK;
					m_ActMenu->m_enAction = m_ActMenu->ASTATE_INVENTORY;
					char message[256];
					sprintf_s(message, "CLOSE Act\n");
					OutputDebugStringA(message);
					m_player->isOpenMenuNow = false;
				}
			}
		}
	}
	
	if (m_player->m_enPState == m_player->PSTATE_SETTING) {
		CVector3 forward = camera3d->GetForward();
		forward.y = 0;
		forward.Normalize();
		forward *= 100.0f;
		forward += m_player->GetPosition();
		m_pConstructor->SetPosition(forward);
	}
	*/
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
	//Walk�Ɉڍs
	if (g_pad[0].IsTrigger(enButtonY)) {
		m_player->m_enPState = m_player->PSTATE_WALK;
		m_ActMenu->m_enAction = m_ActMenu->ASTATE_INVENTORY;
		m_ActMenu->m_mode = 1;
	}
}
void GameScene::CastFont() {
	//�v���C���[���W
	CVector3 Ppos = m_player->GetPosition();
	mi_x = Ppos.x;
	_itow_s(mi_x, mw_PosX, 10);
	mi_y = Ppos.y;
	_itow_s(mi_y, mw_PosY, 10);
	mi_z = Ppos.z;
	_itow_s(mi_z, mw_PosZ, 10);
	//���n���W
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

