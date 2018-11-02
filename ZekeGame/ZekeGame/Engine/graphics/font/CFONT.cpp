#include "stdafx.h"
#include "CFONT.h"



CFONT::CFONT()
{

	pSpriteBatch = new DirectX::SpriteBatch(g_graphicsEngine->GetD3DDeviceContext());
	pSpriteFont = new DirectX::SpriteFont(g_graphicsEngine->GetD3DDevice(), L"Assets/font/myfile.spritefont");
}


CFONT::~CFONT()
{
	delete pSpriteBatch;
	delete pSpriteFont;
}

void CFONT::Init(
	const wchar_t* text,
	CVector3 pos,
	CVector3 scale,
	CVector4 color
) {
	wcscpy(m_text, text);
	m_pos = pos;
	m_scale = scale;
	m_color = color;
}


void CFONT::Init(
	wchar_t text[256],
	CVector3 pos,
	CVector3 scale,
	CVector4 color
	) {
	wcscpy(m_text, text);
	m_pos = pos;
	m_scale = scale;
	m_color = color;
}


void CFONT::Update() {

}

void CFONT::Draw() {
	pSpriteBatch->Begin();
	pSpriteFont->DrawString(pSpriteBatch, (L"%s",m_text), DirectX::XMFLOAT2(m_pos.x, m_pos.y), m_color);
	pSpriteBatch->End();
}