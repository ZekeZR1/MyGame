#pragma once
#include "Item.h"

class TestItem : public Item
{
public:
	TestItem();
	~TestItem();
	 void Update() override;
	 void Draw() override;
	 void SetPosition(CVector3 pos) override;
	 bool isUsing();
private:
	SkinModel * m_skinModel;
	CVector3 m_pos = CVector3::Zero();
};

