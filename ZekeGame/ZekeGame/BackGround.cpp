#include "stdafx.h"
#include "BackGround.h"
#include "window\Window.h"
#include "GameScene.h"
#include "Player.h"
#include "ActionMenu.h"


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

void BackGround::Update(CVector3 drilpos, CVector3 flat, Player* m_player) {
	if (m_converting) {
		delete m_physicsStaticObject;
		m_physicsStaticObject = new PhysicsStaticObject;
		m_physicsStaticObject->CreateMeshObject(smodel, CVector3::Zero(), CQuaternion::Identity());
	}
	ConvertMesh(drilpos,flat,m_player);
}

void BackGround::Draw() {
	smodel.Draw(camera3d->GetViewMatrix() , camera3d->GetProjectionMatrix());
}

void BackGround::ConvertMesh(CVector3 drilpos, CVector3 flat, Player* m_player) {
	//CMatrix mWorldMatrixInv = m_skinModelRender->GetSkinModel().GetWorldMatrix();
	CMatrix mWorldMatrixInv = smodel.GetWorldMatrix();
	mWorldMatrixInv.Inverse(mWorldMatrixInv);
	smodel.FindVertexPosition([&](CVector3* pos) {
			//�t�߂̒��_��ό`������B
			CVector3 DrilPos = drilpos;
			mWorldMatrixInv.Mul(DrilPos);
			CVector3 diff = DrilPos - *pos;
			if (diff.Length() < m_RangeOfConvert) {
				//���n
				switch (m_player->ActState) {
				case m_player->State_Leveling:
					if (abs((drilpos.y) - (flat.y)) > 25) {
						if (flat.y > drilpos.y) {
							pos->z += 6.0f;
						}
						else {
							pos->z -= 6.0f;
						}
					}
					else {
						pos->z = flat.y;
					}
					break;
				case m_player->State_Mining:
					pos->z -= 6.0f;
					break;
				case m_player->State_Fill:
					pos->z += 6.0f;
					break;
				}
			}
		//}
		/*
		if (g_pad[0].IsPress(enButtonX)) {
			//�t�߂̒��_��ό`������B
			CVector3 bodyPos = ppos;
			mWorldMatrixInv.Mul(bodyPos);
			CVector3 diff = bodyPos - *pos;
			if (diff.Length() < 250.0f) {
				pos->z += 5.0f;
				m_converting = true;
			}
		}
		*/
	});
}