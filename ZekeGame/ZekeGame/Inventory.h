#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();
	void UseMaterial(int ordered);
	void ChargeFuel();
	int m_nIron = 0;
	int m_nSilicon = 0;
	int m_nFuel = 0;
	Item::EnItem m_ordered = Item::en_NONE;
};

