#pragma once
#include "physics\PhysicsStaticObject.h"

class BackGround 
{
public:
	BackGround();
	~BackGround();
	void Update(CVector3 playerPos,CVector3 flat, Player* m_player);
	void Draw();
	void ConvertMesh(CVector3 pos,CVector3 flat,Player* m_player);
	bool m_converting = false;
	float m_RangeOfConvert = 200.0f;
private:
	SkinModel smodel;
	CQuaternion m_rot = CQuaternion::Identity()	;
	CVector3 m_pos = CVector3::Zero();
	PhysicsStaticObject* m_physicsStaticObject;
};

