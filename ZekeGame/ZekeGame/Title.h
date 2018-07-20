#pragma once
#include "IScene.h"

class Title : public IScene
{
public:
	Title();
	~Title();
	void Update() override;
	void Draw() override;
	void DrawFont() override;
private:
	Sprite* m_sprite;
	CVector3 m_pos = CVector3::Zero();
};

