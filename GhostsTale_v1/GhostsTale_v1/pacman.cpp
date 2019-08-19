#include "pacman.h"

Pacman::Pacman(Map* m, float startX, float startY, float ms) : level(m), startPosX(startX), startPosY(startY), currentPosX(startX), currentPosY(startY), moveSpeed(ms)
{

}

Pacman::~Pacman()
{
	
}

void Pacman::move(float playerPosX, float playerPosY, float buffer, float deltaTime)
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
		currentPosX += moveSpeed * deltaTime;//move Right
		moved = true;
	}
	if (playerPosY > currentPosY && tileUp != 1)
	{
		currentPosY += moveSpeed * deltaTime;//move Up
		moved = true;
	}
	if (playerPosX < currentPosX && tileToLeft != 1)
	{
		currentPosX -= moveSpeed * deltaTime;//move Left
		moved = true;
	}
	if (playerPosY < currentPosY && tileDown != 1)
	{
		currentPosY -= moveSpeed * deltaTime;// move Down
		moved = true;
	}



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
	respawnTimer = -1;
	turnToPredator();
}

bool Pacman::isColliding(ghost* player)
{
	if (player->xPos() > currentX() - 1 && player->xPos() < currentX() + 1 &&
		player->yPos() > currentY() - 1 && player->yPos() < currentY() + 1)
	{
		return true;
	}
	else
		return false;
}

bool Pacman::isPredator()
{
	return predator;
}

void Pacman::die(float tileSize)
{
	respawnTimer = 0;
	currentPosX = 10.5 * tileSize;//storing the pacman incage
	currentPosY = 11.5 * tileSize;
	turnToPredator();
}

bool Pacman::respawnCheck()
{

	if (respawnTimer == respawnTime)
	{
		return true;
	}
	if (respawnTimer > -1 && respawnTimer < respawnTime)
	{
		respawnTimer++;
		return false;
	}
}

void Pacman::resetRespawnTimer()
{
	respawnTimer == -1;
}

void Pacman::turnToPrey()
{
	predator = false;
}

void Pacman::turnToPredator()
{
	predator = true;
	preyCurrentTime = 0;
}

bool Pacman::preyTimer(float deltaTime)
{
	if (preyCurrentTime > preyStateLength)
	{
		preyCurrentTime = 0;
		return true;
	}
	else if (preyCurrentTime <= preyStateLength)
	{
		++preyCurrentTime * deltaTime;
		return false;
	}
}