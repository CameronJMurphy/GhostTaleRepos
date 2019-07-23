#include "pacman.h"

Pacman::Pacman(Map* m, float startX, float startY, float ms) : level(m), startPosX(startX), startPosY(startY), currentPosX(startX), currentPosY(startY), moveSpeed(ms)
{

}

Pacman::~Pacman()
{
	
}

void Pacman::move(float playerPosX, float playerPosY, float buffer)
{
	
	//figure out what surrounding tiles of the pacman are
	tileToRight = level->getTile(currentPosX + buffer, currentPosY);
	tileToLeft = level->getTile(currentPosX - buffer, currentPosY);
	tileDown = level->getTile(currentPosX, currentPosY - buffer);
	tileUp = level->getTile(currentPosX, currentPosY + buffer);

	bool moved = false;

	//we want the pacman to move towards the players position
	
	if (playerPosX > currentPosX && tileToRight != 1)
	{
		currentPosX += moveSpeed;//move Right
		moved = true;
	}
	if (playerPosY > currentPosY && tileUp != 1)
	{
		currentPosY += moveSpeed;//move Up
		moved = true;
	}
	if (playerPosX < currentPosX && tileToLeft != 1)
	{
		currentPosX -= moveSpeed;//move Left
		moved = true;
	}
	if (playerPosY < currentPosY && tileDown != 1)
	{
		currentPosY -= moveSpeed;// move Down
		moved = true;
	}



	//if (moved == false)
	//{

	//	if (playerPosX > currentPosX && tileToLeft != 1)//if they're to your right, move left
	//	{
	//		currentPosX -= .05;
	//	}
	//	if (playerPosY > currentPosY && tileDown != 1)//if they're above you move down
	//	{
	//		currentPosY -= .05;
	//	}
	//	if (playerPosX < currentPosX && tileToRight != 1)//if they're to your left move right
	//	{
	//		currentPosX += .05;
	//	}
	//	if (playerPosY < currentPosY && tileUp != 1)//if they're below you, move Up
	//	{
	//		currentPosY += .05;
	//	}
	//}



	//
	//if (moved == false)// if none of the above conditions are met then we try an move the pacman an alternate way
	//{
	//	////////////////IF THEY TO YOUR RIGHT
	//	if (playerPosX > currentPosX && tileUp != 1)//if they're to your right, move Up
	//	{
	//		currentPosY += .05;
	//	}
	//	else if (playerPosX > currentPosX && tileDown != 1)//if they're to your right, move Down
	//	{
	//		currentPosY -= .05;
	//	}
	//	/////////////////IF THEY'RE ABOVE YOU
	//	else if (playerPosY > currentPosY && tileToRight != 1)//if they're above you move right
	//	{
	//		currentPosX += .05;
	//	}
	//	else if (playerPosY > currentPosY && tileToLeft != 1)//if they're above you move left
	//	{
	//		currentPosX -= .05;
	//	}
	//	//////////////////IF THEY'RE TO YOUR LEFT
	//	else if (playerPosX < currentPosX && tileUp != 1)//if they're to your left move UP
	//	{
	//		currentPosY += .05;
	//	}
	//	else if (playerPosX < currentPosX && tileDown != 1)//if they're to your left move Down
	//	{
	//		currentPosY -= .05;
	//	}
	//	/////////////////IF THEY'RE BELOW YOU
	//	else if (playerPosY < currentPosY && tileToRight != 1)//if they're below you, move Right
	//	{
	//		currentPosX += .05;
	//	}
	//	else if (playerPosY < currentPosY && tileUp != 1)//if they're below you, move left
	//	{
	//		currentPosX -= .05;
	//	}
	//}

}

float Pacman::currentX()
{
	return currentPosX;
}

float Pacman::currentY()
{
	return currentPosY;
}

void Pacman::reset()
{
	currentPosX = startPosX;
	currentPosY = startPosY;
}