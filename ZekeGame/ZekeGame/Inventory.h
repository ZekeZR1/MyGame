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
	Item::EnItem m_ordered = Item::en_NONE;
};

