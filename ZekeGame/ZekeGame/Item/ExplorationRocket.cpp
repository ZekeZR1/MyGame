#include "stdafx.h"
#include "ExplorationRocket.h"



ExplorationRocket::ExplorationRocket(CVector3 pos)
{
	m_skinModel = new SkinModel;
	m_skinModel->Init(L"Assets/modelData/ExplorationRocket.cmo",enFbxUpAxisY);
	m_skinModel->UpdateWorldMatrix(pos, CQuaternion::Identity(), CVector3::One());
}


ExplorationRocket::~ExplorationRocket()
{
}

void ExplorationRocket::Update() {

}

void ExplorationRocket::Draw() {
	m_skinModel->Draw(camera3d->GetViewMatrix(),camera3d->GetProjectionMatrix());
}
