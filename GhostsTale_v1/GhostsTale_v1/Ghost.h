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
	int mapLength = 21;
	bool collided = false;

	/*struct tilesSurrounding
	{
		int left;
		int right;
		int down;
		int up;
	};*/


	
public:

	

	ghost();

	~ghost();

	void moveRight(int yPos, float tileSize);
	void moveLeft(int yPos, float tileSize);
	void moveDown(int xPos, float tileSize);
	void moveUp(int xPos, float tileSize);

	float xPos() const;

	float yPos() const;

	void setXPos(float pos);
	void setYPos(float pos);

	

	void reset();

	void collectDrop();

	int currentDrops();

	void clamp(int collision, int xPos, int yPos, float tileSize);

	//tilesSurrounding centreImage(Map* level, ghost* player, int buffer);
	
	bool Collided();
};
