#include "stdafx.h"
#include "Fade.h"
#include "ShaderResouceView.h"
#include "CRenderContext.h"
	
Fade::Fade()
{
	m_texture.CreateFromDDSTextureFromFile(L"sprite/fade1.dds");
	m_sprite.Init(m_texture, 1366, 768);
}


Fade::~Fade()
{
}

void Fade::Update() {
	switch (m_state) {
	case enState_FadeIn:
		m_currentAlpha -= 2.0f * 1.0f / 30.0f;
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_FadeOut:
		m_currentAlpha += 2.0f * 1.0f / 30.0f;
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_Idle;
		}
		break;
	case enState_Idle:

		break;
	}
}

void Fade::PostRender(CRenderContext& rc) {
	if (m_currentAlpha > 0.0f) {
		m_sprite.SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
		m_sprite.Draw(rc, camera2d->GetViewMatrix(), camera2d->GetViewProjectionMatrix());
	}
}
