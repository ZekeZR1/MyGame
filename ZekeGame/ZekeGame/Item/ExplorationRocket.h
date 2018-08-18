#pragma once
class ExplorationRocket : Item
{
public:
	ExplorationRocket(CVector3 pos);
	~ExplorationRocket();
	virtual void Update() override;
	virtual void Draw() override;
private:
	SkinModel* m_skinModel;
	CVector3 m_pos = CVector3::Zero();
};

