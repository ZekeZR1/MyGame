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
	bool m_converting = false;
private:
	SkinModel smodel;
	CQuaternion m_rot = CQuaternion::Identity()	;
	CVector3 m_pos = CVector3::Zero();
	PhysicsStaticObject* m_physicsStaticObject;
};

