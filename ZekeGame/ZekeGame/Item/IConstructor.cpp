#include "stdafx.h"
#include "IConstructor.h"
#include "Item.h"
#include "Inventory.h"
IConstructor::IConstructor(Player* player)
{
	mp_player = player;
	m_skinModel = new SkinModel;
	m_skinModel->Init(L"Assets/modelData/Constructor.cmo", enFbxUpAxisZ);
	m_pos.y += 100.0f;
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());

	mS_ItemMenu = new Sprite;
	mS_ItemMenu->Init(L"sprite/constructor.dds", 1280.0f, 720.0f);
	mS_ItemMenu->Update(CVector3::Zero(), CQuaternion::Identity(), { 0.7f,0.7f,0.7f }, { 0.5f,0.5f });

	mS_ItemPre = new Sprite;
	mS_ItemPre->Init(L"sprite/ExRocket.dds", 500.0f, 500.0f);
	m_ItemPrePos.x -= 100.0f;
	mS_ItemPre->Update(m_ItemPrePos, CQuaternion::Identity(), { 0.5f,0.5f,0.5f }, { 0.5f,0.5f });

	m_pos = mp_player->GetForward(100.0f);
	SetPosition(m_pos);
	//LengthSQ
	m_physicsStaticObject = new PhysicsStaticObject;
	m_physicsStaticObject->CreateMeshObject(*m_skinModel, m_pos, CQuaternion::Identity());
	//Font
	m_bFontpos = { 730.0f, 400.0f,0.0f };
	m_aFontpos = { 850.0f, 400.0f,0.0f };
}


IConstructor::~IConstructor()
{
	delete m_skinModel;
	delete mS_ItemMenu;
	delete mS_ItemPre;
	delete m_physicsStaticObject;
}

void IConstructor::Update(Inventory* m_inventory){
	Menu();
	PutAway();
	Crafting(m_inventory);
}

void IConstructor::Menu() {
	//プレイヤーの状態がWALK&&近くでBボタンが押されたらアイテムのメニューを開く
	if (mp_player->m_enPState == mp_player->PSTATE_WALK) {
		if (g_pad[0].IsTrigger(enButtonB)) {
			if (!isOpenMenu) {
				OpenMenu();
				isOpenNow = true;
			}
		}
	}
	if (g_pad[0].IsTrigger(enButtonX)) {
		CloseMenu();
	}

}

void IConstructor::SetPosition(CVector3 pos) {
	m_pos = pos;
	m_skinModel->UpdateWorldMatrix(pos, CQuaternion::Identity(), CVector3::One());
}

void IConstructor::PutAway() {
	if (!isOpenMenu)
		return;
	if (g_pad[0].IsTrigger(enButtonY)) {
		CloseMenu();
		isGoAway = true;
	}
	if (!(mp_player->isNear(m_pos,100.0f))) {
		CloseMenu();
	}
}

void IConstructor::Crafting(Inventory* m_inventory) {
	if (!isOpenMenu)
		return;
	if (g_pad[0].IsTrigger(enButtonDown)) {
		if(ItemNumber!=1)
			ItemNumber++;
	}
	if (g_pad[0].IsTrigger(enButtonUp)) {
		if(ItemNumber != 0)
			ItemNumber--;
	}
	switch (ItemNumber) {
	case 0:
		isDrawFont = true;
		mS_ItemPre->Init(L"sprite/ExRocket.dds", 500.0f, 500.0f);
		_itow_s(m_inventory->m_nIron, mw_bCraft, 10);
		_itow_s(m_inventory->m_nIron - 5, mw_aCraft, 10);
		//if(m_inventory->CanCreate(ExRocket)
		if (m_inventory->m_nIron >= 5) {
			mf_bMaterial.Init((L"%d", mw_bCraft), m_bFontpos);
			mf_aMaterial.Init((L"%d", mw_aCraft), m_aFontpos);
			if (isOpenNow) {
				isOpenNow = false;
				return;
			}
			if (g_pad[0].IsTrigger(enButtonB)) {
				isOrderRocket = true;
				CloseMenu();
			}
		}
		else {
			mf_bMaterial.Init((L"%d", mw_bCraft), m_bFontpos);
			mf_aMaterial.Init((L"%d", mw_aCraft),m_aFontpos,CVector3::One(), CVector4::Red);
		}
		break;
	case 1:
		isDrawFont = true;
		mS_ItemPre->Init(L"sprite/Hover.dds", 500.0f, 500.0f);
		_itow_s(m_inventory->m_nSilicon, mw_bCraft, 10);
		_itow_s(m_inventory->m_nSilicon - 5, mw_aCraft, 10);
		//if(m_inventory->CanCreate(ExRocket)
		if (m_inventory->m_nSilicon >= 5) {
			mf_bMaterial.Init((L"%d", mw_bCraft), m_bFontpos);
			mf_aMaterial.Init((L"%d", mw_aCraft), m_aFontpos);
			if (isOpenNow) {
				isOpenNow = false;
				return;
			}
			if (g_pad[0].IsTrigger(enButtonB)) {
				isOrderHover = true;
				CloseMenu();
			}
		}
		else {
			mf_bMaterial.Init((L"%d", mw_bCraft), m_bFontpos);
			mf_aMaterial.Init((L"%d", mw_aCraft), m_aFontpos, CVector3::One(), CVector4::Red);
		}
		break;
	}
}

void IConstructor::OpenMenu() {
	if (!(mp_player->isNear(m_pos, 500.0f)))
		return;
	if (isOpenMenu)
		return;
	//if (!(mp_player->isOpenMenuNow)) 
	if (mp_player->CanOpenMenu()) {
		isOpenMenu = true;
		mp_player->OpenMenu();
		char message[256];
		sprintf_s(message, "OPEN CONST\n");
		OutputDebugStringA(message);
	}
}

void IConstructor::CloseMenu() {
	if (!isOpenMenu)
		return;
	isOpenMenu = false;
	mp_player->CloseMenu();
	char message[256];
	sprintf_s(message, "CLOSE CONST\n");
	OutputDebugStringA(message);
	ItemNumber = 0;
}

void IConstructor::Draw() {
	m_skinModel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

void IConstructor::DrawSprite() {
	if (!isOpenMenu)
		return;
	mS_ItemMenu->Draw();
	mS_ItemPre->Draw();
	if (isDrawFont) {
		mf_bMaterial.Draw();
		mf_aMaterial.Draw();
	}
}
