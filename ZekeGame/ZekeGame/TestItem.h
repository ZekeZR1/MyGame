#pragma once
#include "Item.h"

class TestItem : public Item
{
public:
	TestItem();
	~TestItem();
	virtual void Update() override;
	virtual void Draw() override;
	virtual void SetPosition(CVector3 pos) override;
private:
	SkinModel * m_skinModel;
	CVector3 m_pos = CVector3::Zero();
};

