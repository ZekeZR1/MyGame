#include "stdafx.h"
#include "BackGround.h"
#include "window\Window.h"
#include "GameScene.h"

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
	smodel.Draw(camera3d->GetViewMatrix() , camera3d->GetProjectionMatrix());
}

void BackGround::ConvertMesh() {
	//CMatrix mWorldMatrixInv = m_skinModelRender->GetSkinModel().GetWorldMatrix();
	CMatrix mWorldMatrixInv = smodel.GetWorldMatrix();
	mWorldMatrixInv.Inverse(mWorldMatrixInv);
	smodel.FindVertexPosition([&](CVector3* pos) {
		if (g_pad[0].IsPress(enButtonA)) {
			//���̕t�߂̒��_��ό`������B
			CVector3 bodyPos = { 0.0f,0.0f,0.0f };
														//���f�����W�n��bodyPos��ό`������B
			mWorldMatrixInv.Mul(bodyPos);
			CVector3 diff = bodyPos - *pos;
			if (diff.Length() < 40.0f) {
				//20cm���Ȃ���ό`������B
				pos->y += 0.1f;
			}
		}
	});
}