#include "stdafx.h"
#include "SpriteRender.h"



SpriteRender::SpriteRender()
{
}


SpriteRender::~SpriteRender()
{
}


bool SpriteRender::Start() {
	return true;
}

void SpriteRender::Init(const wchar_t* FilePath, float w, float h) {
	m_sprite.Init(FilePath, w, h);
}

void SpriteRender::Update() {
	m_sprite.Update(m_pos, m_rotation, m_scale, m_pivot);
}

void SpriteRender::PostRender() {
	m_sprite.Draw();
}

