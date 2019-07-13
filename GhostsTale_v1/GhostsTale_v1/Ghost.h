#pragma once



class ghost
{
protected:
	float posX = 300;//ghost positionX
	float posY = 325; //ghost positionY
	int ghostDrops; //counter to see how many ghost drops have been collected
	bool isMoving = false;
public:

	ghost();

	~ghost();

	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();

	float xPos();

	float yPos();

	bool moving();

	void setMoving(bool answer);
	
	
};
