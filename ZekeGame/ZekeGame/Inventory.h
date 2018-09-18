#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();
	void UseMaterial(int ordered);
	void ChargeFuel();
	int m_nIron = 100;
	int m_nSilicon = 100;
	int m_nFuel = 30;
	enum OrderedItem {
		en_NONE,
		en_ROCKET,
		en_HOVER,
		en_MINING,
		en_BASE,
	};
	OrderedItem m_ordered = en_NONE;
};

