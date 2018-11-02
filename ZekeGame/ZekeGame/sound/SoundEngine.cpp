#include "stdafx.h"
#include "SoundEngine.h"

Sound::Sound() {
	// This is only needed in Windows desktop apps
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AudioEngine_Default;
#ifdef _DEBUG
	eflags = eflags | DirectX::AudioEngine_Debug;
#endif
	audEngine = std::make_unique<DirectX::AudioEngine>(eflags);
}

Sound::~Sound() {

}

void Sound::Update() {
	if (!audEngine->Update())
	{
		// No audio device is active
		if (audEngine->IsCriticalError())
		{
		}
	}
}

void Sound::Init(const wchar_t* filepath, bool roopflag) {
	if (roopflag) {
		soundEffect = std::make_unique<DirectX::SoundEffect>(audEngine.get(), filepath);
		effect = soundEffect->CreateInstance();
	}
	else {
		soundEffect = std::make_unique<DirectX::SoundEffect>(audEngine.get(), filepath);
	}
}

void Sound::Play() {
	soundEffect->Play(0.5f, 0.f, 0.f);
}

void Sound::Play(bool roopflag) {
	if(roopflag)
		effect->Play(true);
}

void Sound::Stop() {
	effect->Stop();
}

bool Sound::isPlaying() {
	if (soundEffect->IsInUse()) {
		return true;
		/*
		char message[256];
		sprintf_s(message, "Playing sound\n");
		OutputDebugStringA(message);
		*/
	}
	else {
		return false;
		/*
		char message[256];
		sprintf_s(message, "Not playing sound\n");
		OutputDebugStringA(message);
		*/
	}
}