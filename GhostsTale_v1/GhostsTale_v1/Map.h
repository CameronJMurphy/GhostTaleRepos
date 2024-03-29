#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Ghost.h"



class Map
{
private:
	const int MapLength = 21;
	const int MapWidth = 21;
	
	float windowX, windowY;

	int level[21][21]
	{
		// 0 = empty
		// 1 = block
		// 8 = ghost drop

		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//21
		{0,1,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,0},//20
		{0,1,8,1,1,1,1,1,1,8,1,8,1,1,1,1,1,1,8,1,0},//19
		{0,1,8,8,8,8,1,8,8,8,1,8,8,8,1,8,8,8,8,1,0},//18
		{0,1,1,8,1,8,1,8,1,1,1,1,1,8,1,8,1,8,1,1,0},//17
		{0,1,8,8,1,8,8,8,8,8,8,8,8,8,8,8,1,8,8,1,0},//16
		{0,1,8,1,1,8,1,1,1,8,1,8,1,1,1,8,1,1,8,1,0},//15
		{0,1,8,8,8,8,8,8,8,8,1,8,8,8,8,8,8,8,8,1,0},//14
		{0,1,1,1,1,8,1,0,1,1,1,1,1,0,1,8,1,1,1,1,0},//13
		{0,0,0,0,1,8,1,0,0,0,0,0,0,0,1,8,1,0,0,0,0},//12
		{1,1,1,1,1,8,1,0,1,1,1,1,1,0,1,8,1,1,1,1,1},//11
		{0,0,0,0,0,8,0,0,1,0,0,0,1,0,0,8,0,0,0,0,0},//10
		{1,1,1,1,1,8,1,0,1,1,1,1,1,0,1,8,1,1,1,1,1},//9
		{0,0,0,0,1,8,1,0,0,0,0,0,0,0,1,8,1,0,0,0,0},//8
		{0,1,1,1,1,8,1,1,1,0,1,0,1,1,1,8,1,1,1,1,0},//7
		{0,1,8,8,8,8,1,8,8,8,1,8,8,8,1,8,8,8,8,1,0},//6
		{0,1,8,1,1,8,1,8,1,1,1,1,1,8,1,8,1,1,8,1,0},//5
		{0,1,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,0},//4
		{0,1,8,1,1,8,1,1,1,8,1,8,1,1,1,8,1,1,8,1,0},//3
		{0,1,8,8,8,8,8,8,8,8,1,8,8,8,8,8,8,8,8,1,0},//2
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}//1

	};

	int baseLevel[21][21]
	{
		// 0 = empty
		// 1 = block
		// 8 = ghost drop

		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},//21
		{0,1,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,0},//20
		{0,1,8,1,1,1,1,1,1,8,1,8,1,1,1,1,1,1,8,1,0},//19
		{0,1,8,8,8,8,1,8,8,8,1,8,8,8,1,8,8,8,8,1,0},//18
		{0,1,1,8,1,8,1,8,1,1,1,1,1,8,1,8,1,8,1,1,0},//17
		{0,1,8,8,1,8,8,8,8,8,8,8,8,8,8,8,1,8,8,1,0},//16
		{0,1,8,1,1,8,1,1,1,8,1,8,1,1,1,8,1,1,8,1,0},//15
		{0,1,8,8,8,8,8,8,8,8,1,8,8,8,8,8,8,8,8,1,0},//14
		{0,1,1,1,1,8,1,0,1,1,1,1,1,0,1,8,1,1,1,1,0},//13
		{0,0,0,0,1,8,1,0,0,0,0,0,0,0,1,8,1,0,0,0,0},//12
		{1,1,1,1,1,8,1,0,1,1,1,1,1,0,1,8,1,1,1,1,1},//11
		{0,0,0,0,0,8,0,0,1,0,0,0,1,0,0,8,0,0,0,0,0},//10
		{1,1,1,1,1,8,1,0,1,1,1,1,1,0,1,8,1,1,1,1,1},//9
		{0,0,0,0,1,8,1,0,0,0,0,0,0,0,1,8,1,0,0,0,0},//8
		{0,1,1,1,1,8,1,1,1,0,1,0,1,1,1,8,1,1,1,1,0},//7
		{0,1,8,8,8,8,1,8,8,8,1,8,8,8,1,8,8,8,8,1,0},//6
		{0,1,8,1,1,8,1,8,1,1,1,1,1,8,1,8,1,1,8,1,0},//5
		{0,1,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,0},//4
		{0,1,8,1,1,8,1,1,1,8,1,8,1,1,1,8,1,1,8,1,0},//3
		{0,1,8,8,8,8,8,8,8,8,1,8,8,8,8,8,8,8,8,1,0},//2
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0}//1

	};

public:

	Map(float windowWidth, float windowHeight);

	~Map();

	void print(aie::Renderer2D* r, aie::Texture* wall, float blockSizeX, float blockSizeY, aie::Texture* drop);

	void updateMap(int posX, int posY, int change);

	int getTile(float posX, float posY);

	void resetLevel();

	bool ghostDropsRemaining();

	void teleportPlayer(ghost* player, std::string direction, float windowWidth, float windowHeight, float tileSize);

	int levelXpos(float pos);
	int levelYpos(float pos);
};
