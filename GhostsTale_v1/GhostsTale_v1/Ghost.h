#pragma once


class ghost
{
protected:
	float posX = 0;//ghost positionX
	float posY = 0; //ghost positionY
	int ghostDrops; //counter to see how many ghost drops have been collected
public:

	ghost();

	~ghost();

	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();

	float xPos();

	float yPos();
	
};
