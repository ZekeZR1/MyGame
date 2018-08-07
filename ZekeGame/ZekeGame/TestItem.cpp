#include "stdafx.h"
#include "TestItem.h"
#include "Item.h"
#include "Player.h"

TestItem::TestItem()
{
	m_skinModel = new SkinModel;
	m_skinModel->Init(L"Assets/modelData/ItemBox.cmo");
	m_pos.y += 100.0f;
	m_skinModel->UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}


TestItem::~TestItem()
{
	delete m_skinModel;
}

void TestItem::Update() {
}

void TestItem::SetPosition(CVector3 pos) {
	m_pos = pos;
	m_skinModel->UpdateWorldMatrix(pos, CQuaternion::Identity(), CVector3::One());
}

void TestItem::Draw() {
	m_skinModel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

void TestItem::PutAway(Player* m_player) {
	//プレイヤーの状態がWALK&&近くでBボタンが押されたらアイテムのメニューを開く
	if (m_player->m_enPState == m_player->PSTATE_WALK) {
		CVector3 ppos = m_player->GetPosition();
		CVector3 v = ppos - m_pos;
		float diff = v.Length();
		if (g_pad[0].IsTrigger(enButtonB)) {
			if (diff <= 100.0f) {
				isGoAway = true;
			}
		}
	}
}
