#pragma once
class Item
{
public:
	Item();
	~Item();
	virtual void Update() = 0;
	virtual void Draw() = 0;
	bool isUsing = false;
	virtual void SetPosition(CVector3 pos) = 0;
};

