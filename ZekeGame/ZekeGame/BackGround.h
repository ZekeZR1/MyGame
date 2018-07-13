#pragma once
#include "physics\PhysicsStaticObject.h"

class BackGround 
{
public:
	BackGround();
	~BackGround();
	void Draw();
private:
	SkinModel smodel;
	CQuaternion m_rot = CQuaternion::Identity()	;
	CVector3 m_pos = CVector3::Zero();
	PhysicsStaticObject m_physicsStaticObject;
};

