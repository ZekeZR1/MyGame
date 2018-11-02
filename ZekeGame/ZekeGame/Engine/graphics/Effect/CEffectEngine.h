#pragma once
class CEffectEngine
{
public:
	CEffectEngine();
	~CEffectEngine();
	void Init(const wchar_t*);
	void Play();
	void Stop();
	void Update();
	void Draw();


private:
	::Effekseer::Manager*			g_manager = NULL;
	::EffekseerRenderer::Renderer*	g_renderer = NULL;
	::Effekseer::Effect*				g_effect = NULL;
	::Effekseer::Handle				g_handle = -1;
	::Effekseer::Vector3D			g_position;
};

