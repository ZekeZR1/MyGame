#pragma once
class Windmill : public Item
{
public:
	Windmill(Player* player);
	~Windmill();
	void Update();
	void Draw();
	void DrawSprite();
private:
	SkinModel m_windmill;
	Animation m_animation;				
	//AnimationClip m_animationClips[0];	
	CVector3 m_pos;
	CQuaternion m_rot = CQuaternion::Identity();
	PhysicsStaticObject m_physicsStaticObject;
};

