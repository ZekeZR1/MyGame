#pragma once
class CFONT;
class Inventory;

class ExplorationRocket : Item
{
public:
	ExplorationRocket(Player* m_player, Inventory* m_inventory);
	~ExplorationRocket();
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DrawSprite() override;
	bool isOpenMenu = false;
private:
	void RocketControl();
	void SetMaterial();
	void Menu();
	void OpenMenu();
	void CloseMenu();
	void Exit();
	void Launch();
	void AddMaterial();
	bool isGotMaterial = false;
	SkinModel* m_skinModel;
	CVector3 m_pos = CVector3::Zero();
	CQuaternion m_rot = CQuaternion::Identity();
	CVector3 m_basepos = CVector3::Zero();
	Player* mp_player;
	Inventory* mp_inventory;
	Sprite* m_sMenu;
	Sprite m_sArrow;
	Sprite m_notify;
	CVector3 m_ArrowPos = CVector3::Zero();
	bool isOnGround = true;
	int mi_nowSearchingTime = 0;
	int mi_SearchTime = 500;
	enum SetMenu {
		en_Material,
		en_Exit,
		en_Launch,
		en_Searching,
		en_Back
	};
	SetMenu setting = en_Material;
	enum Material {
		en_Iron,
		en_Silicon
	};
	Material gotMaterial = en_Iron;

	PhysicsStaticObject* m_physicsStaticObject;
	CQuaternion qRot;
	//Popup
	Popup* m_popup;
	enum NotifyType {
		en_GotMaterial,
	};
	//Font
	CFONT m_font;
	CVector3 m_fontPos;
};

