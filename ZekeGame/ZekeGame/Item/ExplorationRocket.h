#pragma once
class ExplorationRocket : Item
{
public:
	ExplorationRocket(Player* m_player);
	~ExplorationRocket();
	virtual void Update() override;
	virtual void Draw() override;
private:
	SkinModel* m_skinModel;
	CVector3 m_pos = CVector3::Zero();
	Player* mp_player;
	bool isOnGround = true;
};

