#pragma once
//#include "Map.h"
#include "entity.h"


//this class represents the player
class ghost : public entity
{
protected:
	float startX =34 * 10.5;//34 is the tile size
	float startY =34 * 9.5;//34 is the tile size
	float posX = startX;//ghost current positionX
	float posY = startY; //ghost current positionY
	int ghostDrops = 0; //counter to see how many ghost drops have been collected
	int mapLength = 21; //this is applicable to height and width
	bool collided = false; //we need to know if the player has collided with anything

	float speed = 450;

	//int ghostDropsCollected = 0;

	
public:

	

	ghost();

	~ghost();

	void moveRight(float tileSize, float deltaTime);
	void moveLeft(float tileSize, float deltaTime);
	void moveDown(float tileSize, float deltaTime);
	void moveUp(float tileSize, float deltaTime);

	float xPos() const;

	float yPos() const;

	void setXPos(float pos);
	void setYPos(float pos);

	

	void reset();

	void collectDrop();

	int currentDrops();

	void clamp(int collision, int xPos, int yPos, float tileSize);
	
	bool Collided();

	void editDropCount(int num);

};
