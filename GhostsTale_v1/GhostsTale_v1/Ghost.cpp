#include "Ghost.h"
#include "Input.h"


ghost::ghost()
{
	
}

ghost::~ghost()
{

}

float ghost::xPos()
{
	return posX;
}

float ghost::yPos()
{
	return posY;
}

void ghost::moveRight()
{
	posX += .1;
}
void ghost::moveLeft()
{
	posX -= .1;
}
void ghost::moveDown()
{
	posY -= .1;
}
void ghost::moveUp()
{
	posY += .1;
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