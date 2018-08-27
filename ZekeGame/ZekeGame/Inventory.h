#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();
	void UseMaterial(int ordered);
	int m_nIron = 0;
	enum OrderedItem {
		en_NONE,
		en_ROCKET,
	};
	OrderedItem m_ordered = en_NONE;
};

