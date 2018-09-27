#include "stdafx.h"
#include "TheShip.h"



TheShip::TheShip()
{
	m_model.Init(L"Assets/modelData/Ship.cmo", enFbxUpAxisY);
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}


TheShip::~TheShip()
{
}


void TheShip::Update() {

}

void TheShip::Draw() {
	m_model.Draw(camera3d->GetViewMatrix(), camera3d->GetProjectionMatrix());
}