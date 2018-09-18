#pragma once
class Inventory;

class ActionMenu
{
public:
	ActionMenu();
	~ActionMenu();
	void Update(Player* m_player);
	void Draw(Inventory* mp_inventory);
	CVector3 m_flatPos = { 0.0f,100.0f,0.0f };
	enum Action {
		ASTATE_INVENTORY,
		ASTATE_CRAFT,
		ASTATE_MAKEGROUND
	};
	Action m_enAction = ASTATE_INVENTORY;
	int m_mode = 1;
	bool isOpenAct = false;
private:
	void CastFont();
	void DrawFont(Inventory* mp_inventory);
	DirectX::SpriteBatch* pSpriteBatch;
	DirectX::SpriteFont* pSpriteFont;
	wchar_t mw_flatPosY[256];
	wchar_t mw_Iron[256];
	wchar_t mw_Silicon[256];
	int mi_flaty = 0;
	Sprite mS_Item;
	Sprite ms_menu;
	CVector3 m_ActPos = CVector3::Zero();
	Inventory* mp_inventory = nullptr;
};

