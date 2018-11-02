#pragma once
class FONT {
public:
	FONT();	
	~FONT();
	void SetFont(DirectX::SpriteFont* font)
	{
		m_spriteFont = font;
	}
	void Begin(RenderContext& rc);
	void End(RenderContext& rc);

	void Draw(
		wchar_t const* text,
		const CVector2& position,
		const CVector4& color = CVector4::White,
		float rotation = 0.0f,
		float scale = 1.0f,
		CVector2 pivot = { 0.5f, 0.5f }
	);
	void SetShadowParam(bool isDrawShadow, float shadowOffset, const CVector4& shadowColor)
	{
		m_isDrawShadow = isDrawShadow;
		m_shadowOffset = shadowOffset;
		m_shadowColor = shadowColor;
	}
private:
	DirectX::SpriteBatch*	m_spriteBatch = nullptr;
	DirectX::SpriteFont*	m_spriteFont = nullptr;	
	bool m_isDrawShadow = false;					
	float m_shadowOffset = 0.0f;					
	CVector4 m_shadowColor = CVector4::Black;			
	CMatrix m_scaleMat;
};