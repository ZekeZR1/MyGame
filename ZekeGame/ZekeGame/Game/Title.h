#pragma once
#include "IScene.h"

class Title : public IScene
{
public:
	Title();
	virtual ~Title() override;
	void Update() override;
	void Draw() override;
	void DrawFont() override;
private:
	Sprite* m_sprite;
	CVector3 m_pos = CVector3::Zero();
};

