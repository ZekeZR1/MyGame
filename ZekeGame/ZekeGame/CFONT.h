#pragma once
class CFONT
{
public:
	CFONT();
	~CFONT();
	void Init(wchar_t text[256], CVector3 pos = CVector3::Zero(), CVector3 Scale = CVector3::One(), CVector4 color = CVector4::White);
	void Init(const wchar_t* text, CVector3 pos = CVector3::Zero(), CVector3 Scale = CVector3::One(), CVector4 color = CVector4::White);
	void Update();
	void Draw();
private:
	DirectX::SpriteBatch* pSpriteBatch;
	DirectX::SpriteFont* pSpriteFont;
	wchar_t m_text[256];
	CVector3 m_pos;
	CVector3 m_scale;
	CVector4 m_color;
};

