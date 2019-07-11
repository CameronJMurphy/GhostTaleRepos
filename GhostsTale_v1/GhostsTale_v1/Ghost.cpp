#include "Ghost.h"
#include "Input.h"


ghost::ghost()
{
	
}

ghost::~ghost()
{
	delete this;
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
	posX += .05;
}
void ghost::moveLeft()
{
	posX -= .05;
}
void ghost::moveDown()
{
	posY -= .05;
}
void ghost::moveUp()
{
	posY += .05;
}