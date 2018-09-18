#pragma once
#include "physics\PhysicsStaticObject.h"
#include "Player.h"
class Item
{
public:
	Item();
	virtual ~Item();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void DrawSprite() = 0;
};

