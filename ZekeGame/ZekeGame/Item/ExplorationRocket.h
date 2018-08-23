#pragma once
class ExplorationRocket : Item
{
public:
	ExplorationRocket(Player* m_player);
	~ExplorationRocket();
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DrawSprite() override;
	bool isOpenMenu = false;
private:
	void RocketControl();
	void SetMaterial();
	void Menu();
	void Exit();
	void Launch();
	SkinModel* m_skinModel;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_basepos = CVector3::Zero();
	Player* mp_player;
	Sprite* m_sprite;
	bool isOnGround = true;
	int mi_nowSearchingTime = 0;
	int mi_SearchTime = 100;
	enum SetMenu {
		en_Material,
		en_Exit,
		en_Launch,
		en_Searching,
		en_Back
	};
	SetMenu setting = en_Material;
};

