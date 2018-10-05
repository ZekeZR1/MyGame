#pragma once
#include "IScene.h"
#include "sound\SoundEngine.h"
#include "FPSCounter.h"

class Sound;
class CFPSCounter;

class Title : public IScene
{
public:
	Title();
	virtual ~Title() override;
	void Update() override;
	void Draw() override;
private:
	Sprite * m_sprite;
	CVector3 m_pos = CVector3::Zero();
	Sound m_bgm;
	Sound m_start;
	bool isWaiting = false;
};
