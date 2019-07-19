#pragma once

#include "Map.h"

class Pacman
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

public:

	Pacman(Map* m, float startX, float startY);
	~Pacman();

	void move(float playerPosX, float playerPosY, float buffer);
	
	float currentX();
	float currentY();

	void reset();
	
};
