#include "stdafx.h"
#include "IConstructor.h"
#include "Item.h"
#include "Inventory.h"

IConstructor::IConstructor(Player* player)
{
	mp_player = player;
	m_skinModel = new SkinModel;
	m_skinModel->Init(L"Assets/modelData/Constructor.cmo", enFbxUpAxisY);
	m_pos.y += 100.0f;
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());

	mS_ItemMenu = new Sprite;
	mS_ItemMenu->Init(L"sprite/constructor.dds", 1280.0f, 720.0f);
	mS_ItemMenu->Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });

	mS_ItemPre = new Sprite;
	mS_ItemPre->Init(L"sprite/ExRocket.dds", 500.0f, 500.0f);
	mS_ItemPre->Update(m_ItemPrePos, CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
}


IConstructor::~IConstructor()
{
	delete m_skinModel;
	delete mS_ItemMenu;
	delete mS_ItemPre;
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
				OpenMenu();
		}
	}
	if (!isOpenMenu)
		return;
	if (g_pad[0].IsTrigger(enButtonY)) {
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
	if (g_pad[0].IsTrigger(enButtonA)) {
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
		mS_ItemPre->Init(L"sprite/None_Sprite.dds", 500.0f, 500.0f);
		break;
	case 1:
		mS_ItemPre->Init(L"sprite/ExRocket.dds", 500.0f, 500.0f);
		if (g_pad[0].IsTrigger(enButtonB)) {
			if (m_inventory->m_nIron >= 10) {
				isOrderRocket = true;
				CloseMenu();
			}
			else {
				//Materialが足りぬぞ
			}
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
}
