#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
	DeleteGO(neko);
}


bool TestScene::Start() {
	neko = NewGO<SkinModelRender>(0, "neko");
	neko->Init(L"Assets/modelData/Player.cmo",nullptr,0,enFbxUpAxisY);
	return true;
}

void TestScene::Update() {
	static CVector3 nnn = CVector3::Zero();
	if (g_pad[0].IsPress(enButtonA)) {
		nnn.z += 10.f;

	}
	neko->SetPosition(nnn);
}

void TestScene::Render() {
}