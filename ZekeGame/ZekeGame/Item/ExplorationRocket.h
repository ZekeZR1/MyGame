#pragma once
class ExplorationRocket
{
public:
	ExplorationRocket(CVector3 pos);
	~ExplorationRocket();
	void Update();
	void Draw();
private:
	SkinModel* m_skinModel;
	CVector3 m_pos = CVector3::Zero();
};

