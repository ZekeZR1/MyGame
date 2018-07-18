#include "stdafx.h"
#include "BackGround.h"
#include "window\Window.h"
#include "GameScene.h"
#include "Player.h"

BackGround::BackGround()
{
	smodel.Init(L"Assets/modelData/gameworld.cmo");
	smodel.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
	m_physicsStaticObject.CreateMeshObject(smodel, m_pos, m_rot);
}

BackGround::~BackGround()
{
}

void BackGround::Update(CVector3 playerPos) {
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
		if (g_pad[0].IsPress(enButtonA)) {
			//付近の頂点を変形させる。
			CVector3 bodyPos = ppos;
			mWorldMatrixInv.Mul(bodyPos);
			CVector3 diff = bodyPos - *pos;
			if (diff.Length() < 200.0f) {
				pos->z -= 10.0f;
			}else
			if (diff.Length() < 400.0f) {
				pos->z -= 5.0f;
			}
		}
	});
}