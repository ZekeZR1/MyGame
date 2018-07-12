#include "stdafx.h"
#include "BackGround.h"
#include "window\Window.h"

BackGround::BackGround()
{
	smodel.Init(L"Assets/modelData/gameworld.cmo");
	smodel.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_physicsStaticObject.CreateMeshObject(smodel, CVector3::Zero(), CQuaternion::Identity());
}

BackGround::~BackGround()
{
}

void BackGround::Draw(CMatrix viewmatrix, CMatrix projectionmatrix) {
	smodel.Draw(viewmatrix, projectionmatrix);
}