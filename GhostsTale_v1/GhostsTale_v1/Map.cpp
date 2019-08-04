#include "Map.h"
#include "Renderer2D.h"
#include "Texture.h"



enum
{
	empty = 0,
	block = 1,
	ghostDrop = 8
};

Map::Map(float windowWidth, float windowHeight) : windowX(windowWidth), windowY(windowHeight)
{

}

Map::~Map()
{

}

int Map::getTile(float posX, float posY)
{
	int x = (posX / windowY * MapWidth);
	int y =  (posY / windowY * MapLength);

	return level[y][x];
}

void Map::print(aie::Renderer2D* r, aie::Texture* wall,	float blockSizeX, float blockSizeY, aie::Texture* drop)
{
	float imagePosX = blockSizeX /2;
	float imagePosY = blockSizeY / 2;
	//this just takes an array of ints and turns them into images
	for (int row = 0; row < MapLength; row++)
	{
		for (int col = 0; col < MapWidth; col++)
		{
			if (level[row][col] == empty)
			{

			}
			else if (level[row][col] == block)
			{
				r->drawSprite(wall, imagePosX, imagePosY, blockSizeX, blockSizeY);//print block
			}
			else if (level[row][col] == ghostDrop)
			{
				//r->drawSprite(drop, imagePosX, imagePosY, blockSizeX, blockSizeY);//print ghost drops
				r->drawBox(imagePosX, imagePosY, blockSizeX -30, blockSizeY -30);
			}
			imagePosX += blockSizeX;
		}
		imagePosX = blockSizeX/2;//resets this so that it prints to the left side of the screen again
		imagePosY += blockSizeY;//makes the next row print one block size higher
	}
}

void Map::updateMap(int posX, int posY, int change)
{
	int x = (posX / windowY * MapWidth);
	int y = (posY / windowY * MapLength);

	level[y][x] = change;
}

void Map::resetLevel()
{
	for (int row = 0; row < MapLength; row++)
	{
		for (int col = 0; col < MapWidth; col++)
		{
			level[row][col] = baseLevel[row][col];
		}
	}
}

bool Map::ghostDropsRemaining()
{
	for (int row = 0; row < MapLength; row++)
	{
		for (int col = 0; col < MapWidth; col++)
		{
			if (level[row][col] == 8)
				return true;
		}
	}
	return false;
}

void Map::teleportPlayer(ghost* player, std::string direction,float windowWidth, float windowHeight, float tileSize)//this function teleports the player to the other side of the screen
{

	if (direction == "right")
	{
		player->setXPos(0);
		player->setYPos(windowHeight/2 + tileSize);// we add tile size because the map is off centre
	}
	else
	{
		player->setXPos(tileSize * 21);//this is the length of the map
		player->setYPos(windowHeight / 2 + tileSize);
	}
}

int Map::levelXpos(float posX)//this returns the X pos of level at position 'pos'
{
	int x = (posX / windowY * MapWidth);
	return x;
}

int Map::levelYpos(float posY) // this returns the Y pos of level at position 'pos'
{
	int y = (posY / windowY * MapLength);
	return y;
}