#include "stdafx.h"
#include "Title.h"
#include "GameScene.h"
#include "sound/SoundEngine.h"
#include "FPSCounter.h"

extern GameCamera* camera;
extern CFPSCounter* FPS;

Title::Title()
{
	m_sprite = new Sprite;
	m_sprite->Init(L"sprite/Title.dds", 1280.0f,720.0f);
	m_sprite->Update({ 0.0f,0.0f,0.0f }, CQuaternion::Identity(), CVector3::One(), { 0.5f,0.5f });
	m_bgm.Init(L"Assets/sound/title.wav",true); 
	m_start.Init(L"Assets/sound/start.wav",false);
}
Title::~Title()
{
	delete m_sprite;
}

void Title::Update() {
	m_bgm.Play(true);
	if (g_pad[0].IsTrigger(enButtonA)) {
		m_start.Play();
		isWaiting = true;
	}
	if (!m_start.isPlaying() && isWaiting) {
		currentScene = new GameScene;
		delete this;
	}
}

void Title::Draw() {
	m_sprite->Draw();
	//FPS->Draw();
}
