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

bool ghost::moving()
{
	return isMoving;
}

void ghost::setMoving(bool answer)
{
	isMoving = answer;
}

void ghost::reset()
{
	posX = startX;
	posY = startY;
}