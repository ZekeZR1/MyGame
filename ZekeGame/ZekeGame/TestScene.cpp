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
	neko.Init(L"Assets/modelData/Player.cmo",enFbxUpAxisY);
	neko.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	return true;
}

void TestScene::Update() {
	if (g_pad[0].IsPress(enButtonA)) {
		static CVector3 nnn = CVector3::Zero();
		nnn.z += 10.f;
		neko.UpdateWorldMatrix(nnn,CQuaternion::Identity(),CVector3::One());
	}
}

void TestScene::Render() {
	neko.Draw();
	char message[256];
	sprintf_s(message, "TestRender by Manager\n");
	OutputDebugStringA(message);
}