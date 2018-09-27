#pragma once
class TheShip
{
public:
	TheShip();
	~TheShip();
	void Update();
	void Draw();
private:
	SkinModel m_model;
	CVector3 m_pos = CVector3::Zero();
	//PhysicsStaticObject m_physics;
};

