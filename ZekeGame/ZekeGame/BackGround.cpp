#include "stdafx.h"
#include "BackGround.h"
#include "window\Window.h"
#include "GameScene.h"
#include "Player.h"

BackGround::BackGround()
{
	smodel.Init(L"Assets/modelData/BackWorld.cmo");
	smodel.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
	m_physicsStaticObject = new PhysicsStaticObject;
	m_physicsStaticObject->CreateMeshObject(smodel, CVector3::Zero(), CQuaternion::Identity());
}

BackGround::~BackGround()
{
	delete m_physicsStaticObject;
}

void BackGround::Update(CVector3 playerPos) {
	if (m_converting) {
		delete m_physicsStaticObject;
		m_physicsStaticObject = new PhysicsStaticObject;
		m_physicsStaticObject->CreateMeshObject(smodel, CVector3::Zero(), CQuaternion::Identity());
	}
	ConvertMesh(playerPos);
}

void BackGround::Draw() {
	smodel.Draw(camera3d->GetViewMatrix() , camera3d->GetProjectionMatrix());
}

void BackGround::ConvertMesh(CVector3 ppos) {
	//CMatrix mWorldMatrixInv = m_skinModelRender->GetSkinModel().GetWorldMatrix();
	CMatrix mWorldMatrixInv = smodel.GetWorldMatrix();
	mWorldMatrixInv.Inverse(mWorldMatrixInv);
	smodel.FindVertexPosition([&](CVector3* pos) {
		if (g_pad[0].IsPress(enButtonB)) {
			//付近の頂点を変形させる。
			CVector3 bodyPos = ppos;
			mWorldMatrixInv.Mul(bodyPos);
			CVector3 diff = bodyPos - *pos;
			if (diff.Length() < 250.0f) {
				//掘る
				pos->z -= 5.0f;
				m_converting = true;
			}
		}
		if (g_pad[0].IsPress(enButtonX)) {
			//付近の頂点を変形させる。
			CVector3 bodyPos = ppos;
			mWorldMatrixInv.Mul(bodyPos);
			CVector3 diff = bodyPos - *pos;
			if (diff.Length() < 250.0f) {
				pos->z += 5.0f;
				m_converting = true;
			}
		}
	});
}