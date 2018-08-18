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
IConstructor* Items;
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
	// エフェクトを解放します。再生中の場合は、再生が終了した後、自動的に解放されます。
	ES_SAFE_RELEASE(effect);
	// エフェクト管理用インスタンスを破棄
	manager->Destroy();
	// 描画用インスタンスを破棄
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
	delete Items;
	delete m_drilmodel;
	delete m_rocket;
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
	if (g_pad[0].IsTrigger(enButtonStart)) {
		CVector3 rocketpos = m_player->GetPosition();
		m_rocket = new ExplorationRocket(rocketpos);
		//えーっと、出来なかった！ｗ
		//m_items[m_nItem] =  new ExplorationRocket(rocketpos);
	}
	Craft();
	Ground();
	CastFont();
	Menu();
	m_player->Update();
	CVector3 camerapos = camera3d->GetPosition();
	CVector3 playerpos = m_player->GetPosition();
	if (camerapos.y <= playerpos.y) {
		camerapos.y = (playerpos.y + 1.0f);
		camera3d->SetPosition(camerapos);
	}
	camera->Update(m_player);
	if (Items != nullptr) {
		Items->Update(m_inventory);
	}

	if (m_iron != nullptr && m_iron->isGet){
		m_inventory->Iron++;
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
		m_rocket->Draw();
	}
	if (Items != nullptr)
		Items->Draw();
	if (m_iron != nullptr) {
		m_iron->Draw();
	}
	if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_MAKEGROUND) {
		m_drilmodel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
	}
	//手前に描画したい物
	mS_ActState->Draw();
	if (isOpenAct) {
			m_ActMenu->Draw();
	}
	if (Items != nullptr)
		Items->DrawSprite();
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
			pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_flatPosY), DirectX::XMFLOAT2(640.0f, 360.0f), CVector4::Black);
		if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_INVENTORY) {
			pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_Iron), DirectX::XMFLOAT2(640.0f, 360.0f), CVector4::Black);
		}
	}

	pSpriteBatch->End();
}

void GameScene::Craft() {
	if (Items != nullptr) {
		Items->PutAway(m_player);
		if (Items->isGoAway) {
			Items = nullptr;
		}
	}
	if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_CRAFT) {
		if (g_pad[0].IsTrigger(enButtonB)) {
			//選んだアイテムを指定した座標に置く
			if (m_player->m_enPState != m_player->PSTATE_SETTING) {
				if (Items == nullptr) {
					Items = new IConstructor;
					CVector3 forward = camera3d->GetForward();
					forward.y = 0;
					forward.Normalize();
					forward *= 100.0f;
					forward += m_player->GetPosition();
					Items->SetPosition(forward);
					isOpenAct = false;
					m_player->m_enPState = m_player->PSTATE_WALK;
					m_ActMenu->m_enAction = m_ActMenu->ASTATE_INVENTORY;
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
		Items->SetPosition(forward);
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
	if (Items != nullptr && Items->isOpenMenu) {
		isOpenAct = false;
		return;
	}
	if (g_pad[0].IsTrigger(enButtonX)) {
		if (isOpenAct) {
			//m_player->m_enPState = m_player->PSTATE_WALK;
			isOpenAct = false;
		}
		else {
			//m_player->m_enPState = m_player->PSTATE_CRAFT;
			isOpenAct = true;
		}
	}
	if (isOpenAct) {
		m_ActMenu->Update(m_player);
	}
	if (m_ActMenu->m_enAction == m_ActMenu->ASTATE_CRAFT) {
		if (Items != nullptr) {
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
	_itow_s(m_inventory->Iron, mw_Iron, 10);
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