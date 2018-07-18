#pragma once
#include "physics\PhysicsStaticObject.h"

class BackGround 
{
public:
	BackGround();
	~BackGround();
	void Update(CVector3 playerPos);
	void Draw();
	void ConvertMesh(CVector3 pos);
private:
	SkinModel smodel;
	CQuaternion m_rot = CQuaternion::Identity()	;
	CVector3 m_pos = CVector3::Zero();
	PhysicsStaticObject m_physicsStaticObject;
};

