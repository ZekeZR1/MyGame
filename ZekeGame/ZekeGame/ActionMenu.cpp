#include "stdafx.h"
#include "GameScene.h"
#include "ActionMenu.h"
#include "Player.h"
#include "Inventory.h"

Player* player;

ActionMenu::ActionMenu()
{
	//Font
	m_ActMenu = new Sprite;
	mS_Item = new Sprite;
	mS_Item->Init(L"sprite/ItemBoxSprite.dds", 500.0f, 500.0f);
	mS_Item->Update(CVector3::Zero(), CQuaternion::Identity(), { 0.5,0.5,0.5 }, { 0.5f,0.5f });
	m_ActMenu->Init(L"sprite/ActMenuCraft.dds", 1280.0f, 720.0f);
	m_ActMenu->Update(m_ActPos, CQuaternion::Identity(), { 0.8f,0.8f,0.8f }, { 0.5f,0.5f });
	//m_ActMenu->Update(m_ActPos, CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });

	pSpriteBatch = new DirectX::SpriteBatch(g_graphicsEngine->GetD3DDeviceContext());
	pSpriteFont = new DirectX::SpriteFont(g_graphicsEngine->GetD3DDevice(), L"Assets/font/myfile.spritefont");
}


ActionMenu::~ActionMenu()
{
	delete m_ActMenu;
	delete mS_Item;
	delete pSpriteBatch;
	delete pSpriteFont;
}

void ActionMenu::Update(Player* m_player) {
	switch (m_enAction) {
	case ASTATE_INVENTORY:
		m_ActMenu->Init(L"sprite/ActMenuInventory.dds", 1280.0f, 720.0f);
		break;
	case ASTATE_CRAFT:
		m_ActMenu->Init(L"sprite/ActMenuCraft.dds", 1280.0f, 720.0f);
		break;
	case ASTATE_MAKEGROUND:
		m_ActMenu->Init(L"sprite/ActMenuFlatSet.dds", 1280.0f, 720.0f);
	}
	player = m_player;
	if (m_enAction == ASTATE_MAKEGROUND) {
		if (g_pad[0].IsTrigger(enButtonUp)) {
			m_flatPos.y += 10.0f;
		}
		if (g_pad[0].IsTrigger(enButtonDown)) {
			m_flatPos.y -= 10.0f;
		}
	}
	if (g_pad[0].IsTrigger(enButtonRight)) {
		m_mode = (m_mode + 1) % 3;
		//if (m_mode != 2) {
//			m_mode++;
		//}
	}
	if (g_pad[0].IsTrigger(enButtonLeft)) {
		if (m_mode != 0) {
			m_mode--;
		}
	}
	switch (m_mode) {
	case 0:
		m_player->m_enPState = m_player->PSTATE_CRAFT;
		m_enAction = ASTATE_CRAFT;
		break;
	case 1:
		m_player->m_enPState = m_player->PSTATE_WALK;
		m_enAction = ASTATE_INVENTORY;
		break;
	case 2:
		m_player->m_enPState = m_player->PSTATE_MAKEGROUND;
		m_enAction = ASTATE_MAKEGROUND;
		break;
	}
	if (m_player->m_enPState == m_player->PSTATE_CRAFT) {
		if (g_pad[0].IsTrigger(enButtonA)) {
			Craft();
		}
	}
}

void ActionMenu::Draw(Inventory* mp_inventory) {
	m_ActMenu->Draw();
	if(m_enAction == ASTATE_CRAFT)
		mS_Item->Draw();
	DrawFont(mp_inventory);
}

void ActionMenu::Craft() {
	//アイテムを選択
	if (g_pad[0].IsTrigger(enButtonUp)) {
		//Itemスーパークラス = Itemのサブクラス;
	}
	if (g_pad[0].IsTrigger(enButtonDown)) {

	}
	//選択中のアイテムを表示
	/*
	switch(???){
		case ItemBox:
			mS_Item->Init(L"spirte/ItemBox.dds(以下略)
		case ???:

	}
	*/
	//選択中のアイテムの設置予定地を表示
	if (g_pad[0].IsTrigger(enButtonB)) {

		//選んだアイテムを指定した座標に置く
		//new Item;
	}
}


void ActionMenu::CastFont() {
	mi_flaty = m_flatPos.y;
	_itow_s(mi_flaty, mw_flatPosY, 10);
	_itow_s(mp_inventory->m_nIron, mw_Iron, 10);
	_itow_s(mp_inventory->m_nSilicon, mw_Silicon, 10);
}


void ActionMenu::DrawFont(Inventory* mp_inventory) {
	mi_flaty = m_flatPos.y;
	_itow_s(mi_flaty, mw_flatPosY, 10);
	_itow_s(mp_inventory->m_nIron, mw_Iron, 10);
	_itow_s(mp_inventory->m_nSilicon, mw_Silicon, 10);
	pSpriteBatch->Begin();
	//整地座標
	if (isOpenAct) {
		if (m_enAction == ASTATE_MAKEGROUND)
			pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_flatPosY), DirectX::XMFLOAT2(640.0f, 240.0f), CVector4::White);
		if (m_enAction == ASTATE_INVENTORY) {
			pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_Iron), DirectX::XMFLOAT2(640.0f, 360.0f), CVector4::White);
			pSpriteFont->DrawString(pSpriteBatch, (L"%d", mw_Silicon), DirectX::XMFLOAT2(640.0f, 425.0f), CVector4::White);
		}
	}
	pSpriteBatch->End();
}