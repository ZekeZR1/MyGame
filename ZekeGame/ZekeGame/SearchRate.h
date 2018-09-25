#pragma once
class SearchRate
{
public:
	SearchRate();
	~SearchRate();
	void addSearchRate(Item::EnItem item);
	void addGroundRate();
	void addMaterialRate();
	void Update();
	void DrawSprite();
private:
	void GaugeUpdate();
	CQuaternion m_rot = CQuaternion::Identity();
	int m_searchRate = 0;
	int m_searchingBase = 0;
	int m_neko = 0;
	int m_groundSearchingTime = 0;
	Sprite m_frame;
	CVector3 m_framePos = CVector3::Zero();
	//Air
	int m_rateAir = 0;
	int m_searchingWindmill = 0;
	Sprite ms_rateAir;
	Sprite ms_frameAir;
	CVector3 m_airPos;
	CVector3 m_airScale = CVector3::One();
	//Ground
	int m_rateGround = 0;
	Sprite ms_rateGround;
	Sprite ms_frameGround;
	CVector3 m_groundPos;
	CVector3 m_groundScale = CVector3::One();
	//Material
	int m_rateMaterial = 0;
	Sprite ms_rateMaterial;
	Sprite ms_frameMaterial;
	CVector3 m_materialPos;
	CVector3 m_materialScale = CVector3::One();
};

