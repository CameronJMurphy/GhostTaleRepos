#include "Ghost.h"
#include "Input.h"



//struct tilesSurrounding
//{
//	int left;
//	int right;
//	int down;
//	int up;
//};

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

void ghost::moveRight(int yPos, float tileSize)
{
	posX += .1;
	//for (int col = 0; col < mapLength; col++)
	//{
	//		
	//	if (yPos == col)
	//	{
	//		posY = tileSize * (col + 0.5);

	//	}

	//}
}
void ghost::moveLeft(int yPos, float tileSize)
{
	posX -= .1;
	/*for (int col = 0; col < mapLength; col++)
	{

		if (yPos == col)
		{
			posY = tileSize * (col + 0.5);

		}

	}*/
}
void ghost::moveDown(int xPos, float tileSize)
{
	posY -= .1;
	/*for (int row = 0; row < mapLength; row++)
	{

		if (xPos == row)
		{
			posX = tileSize * (row + 0.5);

		}

	}*/
}
void ghost::moveUp(int xPos, float tileSize)
{
	posY += .1;
	/*for (int row = 0; row < mapLength; row++)
	{

		if (xPos == row)
		{
			posX = tileSize * (row + 0.5);

		}

	}*/
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

//tilesSurrounding ghost::centreImage(Map* level, ghost* player, int buffer)
//{
//	tilesSurrounding centre;
//
//	centre.right = level->getTile(player->xPos() + buffer, player->yPos());
//	centre.left = level->getTile(player->xPos() - buffer, player->yPos());
//	centre.down = level->getTile(player->xPos(), player->yPos() - buffer);
//	centre.up = level->getTile(player->xPos(), player->yPos() + buffer);
//
//
//}