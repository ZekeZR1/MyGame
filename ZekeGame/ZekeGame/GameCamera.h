#pragma once
#include "graphics\SpringCamera.h"
class SpringCamera;
class Player;

class GameCamera
{
public:
	GameCamera();
	~GameCamera();
	void Reset();
	void Update(Player* player);
	float x = 0.0f;
	float y = 0.0f;
	Player* m_player;	
	CVector3 m_toCameraPos;	
	SpringCamera m_springCamera;
private:
	bool neko = false;
};

