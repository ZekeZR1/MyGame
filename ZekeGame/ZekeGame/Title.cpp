#include "stdafx.h"
#include "Title.h"
#include "GameScene.h"


Title::Title()
{
}


Title::~Title()
{
}

void Title::Update() {
	if (g_pad[0].IsTrigger(enButtonA)) {
		currentScene = new Title;
		delete this;
	}
}

void Title::Draw() {

}