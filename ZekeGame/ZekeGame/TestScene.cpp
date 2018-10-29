#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"

extern GameCamera* camera;

TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}


bool TestScene::Start() {
	neko.Init(L"sprite/Base.dds", 500, 500);
	neko.Update(CVector3::Zero(),CQuaternion::Identity(),CVector3::One());
	return true;
}

void TestScene::Update() {
}

void TestScene::Render() {
	neko.Draw();
	char message[256];
	sprintf_s(message, "TestRender by Manager\n");
	OutputDebugStringA(message);
}