#pragma once
class IConstructor 
{
public:
	IConstructor();
	~IConstructor();
	 void Update() ;
	 void Draw() ;
	 void DrawSprite();
	void Menu();
	void SetPosition(CVector3 pos) ;
	void PutAway(Player* m_player) ;
	bool isGoAway = false;
	bool isOpenMenu = false;
private:
	SkinModel * m_skinModel;
	CVector3 m_pos = CVector3::Zero();
	Sprite* mS_ItemMenu;
	CVector3 m_MenuPos = CVector3::Zero();
};

