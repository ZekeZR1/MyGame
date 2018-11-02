#pragma once
class Sound {
public:
	Sound();
	~Sound();
	void Update();
	void Init(const wchar_t*, bool);
	void Play();
	bool isPlaying();
	void Play(bool);
	void Stop();
	std::unique_ptr<DirectX::AudioEngine> audEngine;
	std::unique_ptr<DirectX::SoundEffect> soundEffect;
	std::unique_ptr<DirectX::SoundEffectInstance> effect;
};


