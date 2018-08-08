#pragma once
class ItemManager
{
public:
	ItemManager();
	~ItemManager();
	enum Item {
		PROBE,
		ROVER,
		NUM_ITEM
	};
	bool ItemFlags[NUM_ITEM];
};

