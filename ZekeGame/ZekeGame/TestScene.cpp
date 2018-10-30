#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}


bool TestScene::Start() {
	neko.Init(L"Assets/modelData/Player.cmo");
	//neko.SetFbxUpAxis(enFbxUpAxisY);
	return true;
}

void TestScene::Update() {
	static CVector3 nnn = CVector3::Zero();

	if (g_pad[0].IsPress(enButtonA)) {
		nnn.z += 10.f;

		//neko.SetPosition(nnn);
	}
	neko.UpdateWorldMatrix(nnn, CQuaternion::Identity(), CVector3::One());

}

void TestScene::Render() {
	neko.Draw();
}