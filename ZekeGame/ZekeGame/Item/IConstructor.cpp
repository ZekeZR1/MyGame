#include "stdafx.h"
#include "IConstructor.h"
#include "Item.h"


IConstructor::IConstructor()
{
	m_skinModel = new SkinModel;
	m_skinModel->Init(L"Assets/modelData/ItemBox.cmo");
	m_pos.y += 100.0f;
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	mS_ItemMenu = new Sprite;
	mS_ItemMenu->Init(L"sprite/constructor.dds", 1280.0f, 720.0f);
	mS_ItemMenu->Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
}


IConstructor::~IConstructor()
{
	delete m_skinModel;
	delete mS_ItemMenu;
}

void IConstructor::Update() {
	if (isOpenMenu) {
		Menu();
	}
}

void IConstructor::Draw() {
	m_skinModel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

void IConstructor::DrawSprite() {
	if (isOpenMenu) {
		mS_ItemMenu->Draw();
	}
}

void IConstructor::Menu() {
	if (g_pad[0].IsTrigger(enButtonA)) {
		isGoAway = true;
	}
}


void IConstructor::SetPosition(CVector3 pos) {
	m_pos = pos;
	m_skinModel->UpdateWorldMatrix(pos, CQuaternion::Identity(), CVector3::One());
}

void IConstructor::PutAway(Player* m_player) {
	//プレイヤーの状態がWALK&&近くでBボタンが押されたらアイテムのメニューを開く
	CVector3 ppos = m_player->GetPosition();
	CVector3 v = ppos - m_pos;
	float diff = v.Length();
	if (m_player->m_enPState == m_player->PSTATE_WALK) {
		if (g_pad[0].IsTrigger(enButtonB)) {
			if (diff <= 100.0f) {
				if (isOpenMenu) {
					isOpenMenu = false;
				}
				else {
					isOpenMenu = true;
				}
				//isGoAway = true;
			}
		}
	}
	if (diff > 100.0f) {
		isOpenMenu = false;
	}
}
