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
		m_nIron -= 10;
		break;
	}
}
