#pragma once
#include "Player.h"
class Item
{
public:
	Item();
	virtual ~Item();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	//bool isUsing = false;
	//virtual void SetPosition(CVector3 pos) = 0;
	//bool isGoAway = false;
	//virtual void PutAway(Player* m_player) = 0; 
};

