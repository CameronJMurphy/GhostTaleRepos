#pragma once



class ghost
{
protected:
	float startX = 300;
	float startY = 325;
	float posX = 300;//ghost positionX
	float posY = 325; //ghost positionY
	int ghostDrops; //counter to see how many ghost drops have been collected
	bool isMoving = false;

	int tileToRight;
	int tileToLeft;
	int tileDown;
	int tileUp;
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

	void reset();
	
	
};
