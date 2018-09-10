#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();
	void UseMaterial(int ordered);
	int m_nIron = 100;
	int m_nSilicon = 100;
	enum OrderedItem {
		en_NONE,
		en_ROCKET,
		en_HOVER,

	};
	OrderedItem m_ordered = en_NONE;
};

