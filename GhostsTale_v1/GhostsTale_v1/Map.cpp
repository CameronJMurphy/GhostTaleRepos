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
	int x = posX / windowX * MapWidth;
	int y = posY / windowY * MapLength;

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
				r->drawSprite(drop, imagePosX, imagePosY, blockSizeX, blockSizeY);//print ghost drops
			}
			imagePosX += blockSizeX;
		}
		imagePosX = blockSizeX/2;//resets this so that it prints to the left side of the screen again
		imagePosY += blockSizeY;//makes the next row print one block size higher
	}
}

void Map::updateMap(int posX, int posY, int change)
{

}