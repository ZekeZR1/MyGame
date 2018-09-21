#include "stdafx.h"
#include "GameScene.h"
#include "Windmill.h"

Windmill::Windmill(Player* player)
{
	m_windmill.Init(L"Assets/modelData/Windmill.cmo", enFbxUpAxisY);
	m_pos = player->GetForward(500.0f);
	m_rot = player->GetRot();
	m_windmill.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
	CQuaternion rot = CQuaternion::Identity();
	rot.SetRotationDeg(CVector3::AxisX(), 90.0f);
	m_physicsStaticObject.CreateMeshObject(m_windmill, m_pos, rot);
	/*
	m_animationClips[0].Load(L"Assets/modelData/Windmill.tka");
	m_animationClips[0].SetLoopFlag(true);
	m_animation.Init(
		m_windmill,
		m_animationClips,
		1
	);
	*/
}


Windmill::~Windmill()
{
}

void Windmill::Update() {
	//m_animation.Play(0, 0.3f);
}

void Windmill::Draw() {
	m_windmill.Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}

void Windmill::DrawSprite(){

}