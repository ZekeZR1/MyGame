#pragma once
class ActionMenu
{
public:
	ActionMenu();
	~ActionMenu();
	void Update();
	void Draw();
	CVector3 m_flatPos = { 0.0f,100.0f,0.0f };
private:
	Sprite* m_ActMenu;
	CVector3 m_ActPos = CVector3::Zero();

};

