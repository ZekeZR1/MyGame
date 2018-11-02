#pragma once
#define MOVECOST 0.001
#define CHARGECOST 0.002
class Player;
class Inventory;

class Hover : public Item
{
public:
	Hover(Player* player, Inventory* inventory);
	~Hover() override;
	void Update() override;
	void Draw() override;
	void DrawSprite() override;
private:
	void Ride();
	void MoveAndRotation();
	void Physics();
	void UseBattery();
	void addFuel();
	void BatteryGauge();
	void CastFont();
	void DrawFont();
	bool isRideNow = false;
	bool m_isLowBattery = false;
	bool m_isMaxBattery = true;
	bool isOpenFuelMenu = false;
	Player * mp_player = nullptr;
	Inventory* mp_inventory = nullptr;
	SkinModel* m_hoverModel;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_moveSpeed = CVector3::Zero();
	PhysicsStaticObject* m_physicsStaticObject;
	bool isRiding = false;
	Sprite ms_panel;
	CVector3 m_panelPos = CVector3::Zero();
	CVector3 m_panelScale = CVector3::One();
	Sprite ms_gauge;
	CVector3 m_gaugePos = CVector3::Zero();
	CVector3 m_gaugeScale = CVector3::One();
	Sprite ms_frame;
	CVector3 m_framePos = CVector3::Zero();
	//FuelMenu
	Sprite ms_fuelMenu;
	CFONT mf_bFuel;
	CFONT mf_aFuel;
	wchar_t mw_bCharge[256];
	wchar_t mw_aCharge[256];
	CVector3 m_bFontpos = CVector3::Zero();
	CVector3 m_aFontpos = CVector3::Zero();
	//Font
	DirectX::SpriteBatch* pSpriteBatch;
	DirectX::SpriteFont* pSpriteFont;
	wchar_t mw_PosX[256];
	wchar_t mw_PosY[256];
	wchar_t mw_PosZ[256];
	int mi_x = 0;
	int mi_y = 0;
	int mi_z = 0;
};

