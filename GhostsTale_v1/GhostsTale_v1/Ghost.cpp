#include "Ghost.h"
#include "Input.h"



ghost::ghost()
{
	
}

ghost::~ghost()
{

}

float ghost::xPos() const
{
	return posX;
}

float ghost::yPos() const 
{
	return posY;
}

void ghost::moveRight(float tileSize, float deltaTime)
{
	posX += speed * deltaTime;
	
}
void ghost::moveLeft(float tileSize, float deltaTime)
{
	posX -= speed * deltaTime;
	
}
void ghost::moveDown(float tileSize, float deltaTime)
{
	posY -= speed * deltaTime;
	
}
void ghost::moveUp(float tileSize, float deltaTime)
{
	posY += speed * deltaTime;
	
}

void ghost::reset()
{
	posX = startX;
	posY = startY;
}

void ghost::collectDrop()
{
	++ghostDrops;
}

int ghost::currentDrops()
{
	return ghostDrops;
}

void ghost::setXPos(float newPos)
{
	posX = newPos;
}
void ghost::setYPos(float newPos)
{
	posY = newPos;
}

void ghost::clamp(int collision,int xPos, int yPos, float tileSize)
{
	if (collision == 1)
	{
		collided = true;

		for (int col = 0; col < mapLength; col++)
		{
			for (int row = 0; row < mapLength; row++)
			{
				if (yPos == col && xPos == row)
				{
					posY = tileSize * (col + 0.5);
					posX = tileSize * (row + 0.5);
					break;
				}
			}
		}
	}
	else
	{
		collided = false;
	}
}

bool ghost::Collided()
{
	return collided;
}

