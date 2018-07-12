#pragma once
#include "physics\PhysicsStaticObject.h"

class BackGround
{
public:
	BackGround();
	~BackGround();
	void Draw(CMatrix viewmatrix, CMatrix projectionmatrix);
private:
	SkinModel smodel;
	PhysicsStaticObject m_physicsStaticObject;
};

