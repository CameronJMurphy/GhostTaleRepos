#pragma once

class pacman
{
private:
	float startPosX = 0;
	float startPosY = 0;

	float currentPosX = 0;
	float currentPosY = 0;
public:

	pacman();
	~pacman();

	void move(float playerPosX, float playerPosY);
};
