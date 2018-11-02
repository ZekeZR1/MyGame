#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{
	
	camera2d = new Camera;
	camera2d->SetTarget(CVector3::Zero());
	camera2d->SetPosition({ 0.0f, 0.0f, -10.0f });
	camera2d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);	
	camera2d->SetNear(0.1f);
	camera2d->SetFar(1000.0f);
	camera2d->Update();
	
	camera3d = new Camera;
	camera3d->SetTarget(m_target);
	camera3d->SetPosition(m_pos);
	camera3d->SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Perspective);
	camera3d->SetNear(0.1f);
	camera3d->SetFar(50000.0f);
	camera3d->Update();
}


GameCamera::~GameCamera()
{
	delete camera2d;
	delete camera3d;
}

/*
	毎フレーム呼ばれるゲームカメラの更新
*/
void GameCamera::Update() {
	camera2d->Update();

	SkinModelRender* i_model = nullptr;
	i_model = FindGO<SkinModelRender>("model");
	m_target = i_model->GetPosition();

	CVector3 toCameraPosOld = m_toCameraPos;
	float x = g_pad[0].GetRStickXF();
	float y = g_pad[0].GetRStickYF();
	//Y軸周りの回転
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisY(), 2.0f * x);
	qRot.Multiply(m_toCameraPos);
	//X軸周りの回転。
	CVector3 axisX;
	axisX.Cross(CVector3::AxisY(), m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * y);
	qRot.Multiply(m_toCameraPos);
	CVector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}

	CVector3 pos = m_target + m_toCameraPos;

	camera3d->SetTarget(m_target);
	camera3d->SetPosition(pos);
	camera3d->Update();
}