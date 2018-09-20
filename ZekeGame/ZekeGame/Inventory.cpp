#include "stdafx.h"
#include "Item\ExplorationRocket.h"
#include "Inventory.h"

Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

void Inventory::UseMaterial(int ordered) {
	switch (ordered) {
	case Item::en_ROCKET:
		m_nIron -= 5;
		break;
	case Item::en_HOVER:
		m_nSilicon -= 5;
		break;
	case Item::en_MINING:
		m_nIron -= 5;
		break;
	case Item::en_BASE:
		m_nIron -= 10;
		break;
	case Item::en_WINDMILL:
		m_nIron -= 5;
		break;
	}
}

void Inventory::ChargeFuel() {
	if (m_nFuel - 5 >= 0)
		m_nFuel -= 5;
}