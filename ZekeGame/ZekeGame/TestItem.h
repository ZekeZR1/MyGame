#pragma once
#include "Item.h"
#include "Player.h"
class Player;
class TestItem : public Item
{
public:
	TestItem();
	~TestItem();
	 void Update() override;
	 void Draw() override;
	 void SetPosition(CVector3 pos) override;
	 void PutAway(Player* m_player);
	 //bool isUsing();
private:
	SkinModel * m_skinModel;
	CVector3 m_pos = CVector3::Zero();
};

