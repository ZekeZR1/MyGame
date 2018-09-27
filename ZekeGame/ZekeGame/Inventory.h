#pragma once
class Inventory
{
public:
	Inventory();
	~Inventory();
	void UseMaterial(int ordered);
	void ChargeFuel();
	int m_nIron = 50;
	int m_nSilicon = 50;
	int m_nFuel = 50;
	Item::EnItem m_ordered = Item::en_NONE;
};

