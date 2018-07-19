#pragma once
class Player;
class GameCamera
{
public:
	GameCamera();
	~GameCamera();
	void Update(Player* player);
};

