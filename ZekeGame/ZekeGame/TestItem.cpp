#include "stdafx.h"
#include "TestItem.h"
#include "Item.h"

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
	m_skinModel->UpdateWorldMatrix(pos, CQuaternion::Identity(), CVector3::One());
}

void TestItem::Draw() {
	m_skinModel->Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

