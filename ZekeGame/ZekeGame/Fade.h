#pragma once
#include "CRenderContext.h"

class CRenderContext;

class Fade
{
public:
	Fade();
	~Fade();
	void Update();
	void PostRender(CRenderContext& rc);
	void StartFadeIn()
	{
		m_state = enState_FadeIn;
	}
	void StartFadeOut()
	{
		m_state = enState_FadeOut;
	}

	bool IsFade() const
	{
		return m_state != enState_Idle;
	}
	float GetCurrentAlpha() const
	{
		return m_currentAlpha;
	}

private:
	enum EnState {
		enState_FadeIn,		
		enState_FadeOut,		
		enState_Idle,		
	};
	ShaderResouceView m_texture;
	Sprite m_sprite;
	EnState m_state = enState_Idle;	
	float m_currentAlpha = 1.0f;
};

