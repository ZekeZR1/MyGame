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
	case en_ROCKET:
		m_nIron -= 5;
		break;
	case en_HOVER:
		m_nSilicon -= 5;
		break;
	}
}

void Inventory::ChargeFuel() {
	if (m_nFuel - 5 >= 0)
		m_nFuel -= 5;
}