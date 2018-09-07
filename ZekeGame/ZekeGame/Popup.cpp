#include "stdafx.h"
#include "Popup.h"

Popup::Popup()
{
	m_sprite = new Sprite;
	m_sprite->Init(L"sprite/NotiGotMaterial.dds", 400.0f, 200.0f);
	//ms_notify.Init(L"sprite/NotiGotMaterial.dds", 400.0f, 200.0f);
	m_pos.x = 400.0f;
	m_pos.y = 280.0f;
	//ms_notify.Update(m_pos, CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
	m_sprite->Update(m_pos, CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
}

Popup::~Popup()
{
}

void Popup::Update() {
	if (!isNotifying)
		return;

	mi_writing++;
	if (mi_writing >= 20) {
		mi_writing = 0;
		isNotifying = false;
	}
}

void Popup::Notify(int type) {
	switch (type) {
	case en_GotMaterial:
		//ms_notify.Init(L"sprite/NotiGotMaterial.dds", 500.0f, 300.0f);
		m_sprite->Init(L"sprite/NotiGotMaterial.dds", 500.0f, 300.0f);
		//ms_notify.Update(m_pos, CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
		m_sprite->Update(m_pos, CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
		isNotifying = true;
		break;
	default:
		isNotifying = true;
	}
}

void Popup::Draw() {
	if (!isNotifying)
		return;
	m_sprite->Draw();
	char message[256];
	sprintf_s(message, "DRAWING POPUP\n");
	OutputDebugStringA(message);
}
