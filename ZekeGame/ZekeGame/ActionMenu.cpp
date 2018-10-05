#include "stdafx.h"
#include "GameScene.h"
#include "ActionMenu.h"
#include "Player.h"
#include "Inventory.h"
#include "sound\SoundEngine.h"

Player* player;

ActionMenu::ActionMenu()
{
	mS_Item.Init(L"sprite/ItemBoxSprite.dds", 250.0f, 250.0f);
	ms_menu.Init(L"sprite/ActMenuCraft.dds", 896.0f, 504.0f);
	pSpriteBatch = new DirectX::SpriteBatch(g_graphicsEngine->GetD3DDeviceContext());
	pSpriteFont = new DirectX::SpriteFont(g_graphicsEngine->GetD3DDevice(), L"Assets/font/myfile.spritefont");
	m_se.Init(L"Assets/sound/se.wav", false);
}


ActionMenu::~ActionMenu()
{
	delete pSpriteBatch;
	delete pSpriteFont;
}

void ActionMenu::Update(Player* m_player) {
	switch (m_enAction) {
	case ASTATE_INVENTORY:
		ms_menu.Init(L"sprite/ActMenuInventory.dds", 896.0f, 504.0f);
		break;
	case ASTATE_CRAFT:
		ms_menu.Init(L"sprite/ActMenuCraft.dds", 896.0f, 504.0f);
		break;
	case ASTATE_MAKEGROUND:
		ms_menu.Init(L"sprite/ActMenuFlatSet.dds", 896.0f, 504.0f);
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
		m_se.Play();
		//m_mode = (m_mode + 1) % 3;
		if (m_mode != 2) {
			m_mode++;
		}
	}
	if (g_pad[0].IsTrigger(enButtonLeft)) {
		m_se.Play();
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
}

void ActionMenu::Draw(Inventory* mp_inventory) {
	ms_menu.Draw();
	if (m_enAction == ASTATE_CRAFT)
		mS_Item.Draw();
	DrawFont(mp_inventory);

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
	//®’nÀ•W
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