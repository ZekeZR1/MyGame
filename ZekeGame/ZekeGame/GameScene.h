#pragma once
#include "IScene.h"
#include "BackGround.h"
#include "Player.h"
//#include "ActionMenu.h"
class ActionMenu;
class Iron;

class GameScene : public IScene
{
public:
	GameScene();
	~GameScene();
	void Update() override;
	void Draw() override;
	void DrawFont() override;
	void Craft();
	void Ground();
	void Menu();
	void CastFont();
	bool Converting = false;
	bool isOpenAct = false;
	ActionMenu* m_ActMenu = nullptr;
	Player* m_player = nullptr;
private:
	/*Effect
	::EffekseerRenderer::Renderer* renderer = ::EffekseerRendererDX11::Renderer::Create(g_graphicsEngine->GetD3DDevice(), g_graphicsEngine->GetD3DDeviceContext(), 100);
	::Effekseer::Manager* manager = ::Effekseer::Manager::Create(100);
	Effekseer::Effect* effect;
	Effekseer::Handle handle;
	*/
	Iron* m_iron;
	SkinModel * m_model;
	CVector3 m_spritePos = CVector3::Zero();
	float spweight = 100.0f, sphight = 100.0f;
	CVector3 m_spscale = { 1.0f,1.0f,1.0f };
	BackGround* bg;
	CVector3 modelPos = CVector3::Zero();
	Animation modelanimation;
	Sprite* mS_ActState;
	CVector3 mv_ActSpos = CVector3::Zero();
	//DrilPos
	SkinModel* m_drilmodel;
	//Font
	DirectX::SpriteBatch* pSpriteBatch;
	DirectX::SpriteFont* pSpriteFont;
	wchar_t mw_PosX[256];
	wchar_t mw_PosY[256];
	wchar_t mw_PosZ[256];
	wchar_t mw_flatPosY[256];
	int mi_x = 0;
	int mi_y = 0;
	int mi_z = 0;
	int mi_flaty = 0;
};

extern GameScene* g_game;