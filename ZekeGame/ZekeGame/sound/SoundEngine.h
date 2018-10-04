#pragma once
class Sound {
public:
	Sound();
	~Sound();
	void Update();
	void Init(const wchar_t*, bool);
	void Play();
	void Play(bool);
	std::unique_ptr<DirectX::AudioEngine> audEngine;
	std::unique_ptr<DirectX::SoundEffect> soundEffect;
	std::unique_ptr<DirectX::SoundEffectInstance> effect;
};


