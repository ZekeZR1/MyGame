#pragma once
class Item
{
public:
	Item();
	~Item();
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

