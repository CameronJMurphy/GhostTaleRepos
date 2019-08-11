#pragma once

#include "Map.h"
#include "entity.h"

class Pacman : public entity
{
private:
	float startPosX = 200;
	float startPosY = 200;

	float currentPosX = 200;
	float currentPosY = 200;

	int tileToRight;
	int tileToLeft;
	int tileDown;
	int tileUp;

	Map* level;

	float moveSpeed = 0.03;

	bool predator = true;

	int preyCurrentTime = 0;
	int preyStateLength = 10000;

	int respawnTimer = -1;
	int respawnTime = 4000;

public:

	Pacman(Map* m, float startX, float startY, float ms);
	~Pacman();

	void move(float playerPosX, float playerPosY, float buffer, float deltaTime);
	
	float currentX();
	float currentY();

	void reset();

	bool isColliding(ghost* player);

	bool isPredator();

	void turnToPrey();
	void turnToPredator();
	
	void die();

	bool respawnCheck();

	void resetRespawnTimer();

	bool preyTimer();

};
