#pragma once


//this class represents the player
class ghost
{
protected:
	float startX = 300;
	float startY = 325;
	float posX = 300;//ghost current positionX
	float posY = 325; //ghost current positionY
	int ghostDrops = 0; //counter to see how many ghost drops have been collected

	//we need to know what tile surround the player so we can determine movement options
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

	void setXPos(float pos);
	void setYPos(float pos);

	

	void reset();

	void collectDrop();

	int currentDrops();
	
	
};
