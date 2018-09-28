#pragma once

class TheShip
{
public:
	TheShip();
	~TheShip();
	void Update(Player* player);
	void Draw();
	void GoDown();
	void GoUp();
	bool isRiding = false;
	bool isInSpace;
private:
	bool isGoDown = false;
	bool isGoUp = false;
	SkinModel m_model;
	CVector3 m_pos = CVector3::Zero();
	CVector3 m_moveSpeed = CVector3::Zero();
	//PhysicsStaticObject m_physics;
};

