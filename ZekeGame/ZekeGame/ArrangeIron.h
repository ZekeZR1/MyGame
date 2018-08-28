#pragma once
#define MAXIRON 15
class Iron;

class ArrangeIron
{
public:
	ArrangeIron(Player* player, Inventory* inventory);
	~ArrangeIron();
	void Update();
	void Draw();
private:
	Iron* m_irons[MAXIRON];
	Player* mp_player;
	Inventory* mp_inventory;
};

