#include "stdafx.h"
#include "BackGround.h"
#include "window\Window.h"

BackGround::BackGround()
{
	smodel.Init(L"Assets/modelData/gameworld.cmo");
	smodel.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
	m_physicsStaticObject.CreateMeshObject(smodel, m_pos, m_rot);
}

BackGround::~BackGround()
{
}

void BackGround::Draw() {
	extern Camera* camera3d;
	smodel.Draw(camera3d->GetViewMatrix() , camera3d->GetProjectionMatrix());
}