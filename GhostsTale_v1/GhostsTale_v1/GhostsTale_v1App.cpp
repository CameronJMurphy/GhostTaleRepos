#include "GhostsTale_v1App.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include "Button.h"
#include "Ghost.h"
#include "Map.h"
#include "pacman.h"

using namespace std;

enum
{
	Title,
	Menu,
	Settings,
	Game,
	Win
};

GhostsTale_v1App::GhostsTale_v1App() {

}

GhostsTale_v1App::~GhostsTale_v1App() {

}

bool GhostsTale_v1App::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	//setup textures
	wallTile = new aie::Texture("./textures/grass.png");
	pacmanTexture = new aie::Texture("./textures/pacman.png");
	ghostTexture = new aie::Texture("./textures/ghost.png");
	ghostDrop = new aie::Texture("./textures/ghostDrop.svg.png");
	title = new aie::Texture("./textures/Title.png");
	settingsButtonTexture = new aie::Texture("./textures/SettingsButton.png");
	startButtonTexture = new aie::Texture("./textures/StartButton.png");
	upArrow = new aie::Texture("./textures/UpArrow.png");
	downArrow = new aie::Texture("./textures/DownArrow.png");

	player = new ghost();

	level = new Map(getWindowWidth(), getWindowHeight());

	pacman1 = new Pacman(level,200,200, 0.03);
	pacman2 = new Pacman(level, 600,600,0.02);
	pacman3 = new Pacman(level, 600, 200,0.04);
	pacman4 = new Pacman(level, 200, 600,0.035);
	

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);


	m_timer = 0;



	return true;
}

void GhostsTale_v1App::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete wallTile;
	delete pacmanTexture;
	delete ghostTexture;
	delete player;
	delete level;
	delete pacman1;
	delete pacman2;
	delete pacman3;
	delete pacman4;
}

void GhostsTale_v1App::update(float deltaTime) {

	m_timer += deltaTime;
	aie::Input* input = aie::Input::getInstance();
	const unsigned int windowHeight = getWindowHeight();
	const unsigned int windowWidth = getWindowWidth();

	if (state != Game)//While it isn't game. Ive done this to improve performance while the game is running.
	{

		system("cls");
	
		int x, y;
		input->getMouseXY(&x, &y);
		cout << "x = " << x << "y = " << y << endl;
	

		
		////////////////////	TITLE	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		


		if (state == Title)
		{
			if (input->isKeyDown(aie::INPUT_KEY_ENTER))
			{
				state = Menu;
			}
		}



		////////////////////	Menu	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (state == Menu)
		{
			int HalfOfWindowWidth = getWindowWidth() / 2;
			int HalfOfWindowHeight = getWindowHeight() / 2;
			Button StartButton(HalfOfWindowWidth, HalfOfWindowHeight, startButtonWidth, startButtonHeight);
			Button SettingsButton(HalfOfWindowWidth, HalfOfWindowHeight - 150, settingsButtonWidth, settingsButtonHeight);

			if (StartButton.IsMouseOver(x, y))
			{
				state = Game;
			}
			if (SettingsButton.IsMouseOver(x, y))
			{
				state = Settings;
			}


		}



		////////////////////	SETTINGS	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		else if (state == Settings)
		{
			if (input->isKeyDown(aie::INPUT_KEY_BACKSPACE))
			{
				state = Menu;
			}
		}
	}


	////////////////////	GAME	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	else if (state == Game)
	{
		
		tileSize = getWindowHeight() / 21;
		int currentPos = level->getTile(player->xPos(), player->yPos());
		float buffer = (getWindowHeight() / 21) / 2 - 8;//half of player size

		
		//dream code
		//tilesSurrounding TilesSurroundingCentre = centreImage(level, player, buffer);
		//tilesSurrounding TilesSurroundingTop =  topSideImage(level, player, buffer);
		//tilesSurrounding TilesSurroundingBot =  botSideImage(level, player, buffer);
		//tilesSurrounding TilesSurroundingLeft =  leftSideImage(level, player, buffer);
		//tilesSurrounding TilesSurroundingRight =  rightSideImage(level, player, buffer);

		

		//figure out what surrounding tiles of the player are, from the centre on the image
		int tileToRight = level->getTile(player->xPos() + buffer, player->yPos());
		int tileToLeft = level->getTile(player->xPos() - buffer + 3, player->yPos());
		int tileDown = level->getTile(player->xPos(), player->yPos() - buffer + 3);
		int tileUp = level->getTile(player->xPos(), player->yPos() + buffer);

		//figure out what tiles suround the top side of the image
		int tileToTopRight = level->getTile(player->xPos() + buffer, player->yPos() + buffer);
		int tileToTopLeft = level->getTile(player->xPos() - buffer, player->yPos() + buffer);
	
		//figure out what tiles suround the bottom side of the image
		int tileToBotRight = level->getTile(player->xPos() + buffer, player->yPos() - buffer);
		int tileToBotLeft = level->getTile(player->xPos() - buffer, player->yPos() - buffer);
		
		//figure out what tiles suround the left side of the image
		int tileLeftDown = level->getTile(player->xPos() - buffer, player->yPos() - buffer);
		int tileLeftUp = level->getTile(player->xPos() - buffer, player->yPos() + buffer);
		//figure out what tiles suround the right side of the image
		int tileRightDown = level->getTile(player->xPos() + buffer, player->yPos() - buffer);
		int tileRightUp = level->getTile(player->xPos() + buffer, player->yPos() + buffer);

		
		const int collisionPoints = 12;
		int collisions[collisionPoints]{ tileToRight ,tileToLeft ,tileDown ,tileUp ,tileToTopRight,tileToTopLeft,tileToBotRight,tileToBotLeft,tileLeftDown,tileLeftUp,tileRightDown,tileRightUp };
		

		


		//if the players collect all the orbs, they win
		if (level->ghostDropsRemaining() == false)
		{
			state = Win;
		}



		//if any of the pacman are touching the player, you lose the game
		if (player->xPos() > pacman1->currentX() - 1 && player->xPos() < pacman1->currentX() + 1 &&//pacman1X
			player->yPos() > pacman1->currentY() - 1 && player->yPos() < pacman1->currentY() + 1 ||//pacman1Y
			player->xPos() > pacman2->currentX() - 1 && player->xPos() < pacman2->currentX() + 1 &&//pacman2X
			player->yPos() > pacman2->currentY() - 1 && player->yPos() < pacman2->currentY() + 1 ||//pacman2Y
			player->xPos() > pacman3->currentX() - 1 && player->xPos() < pacman3->currentX() + 1 &&//pacman3X
			player->yPos() > pacman3->currentY() - 1 && player->yPos() < pacman3->currentY() + 1 ||//pacman3Y
			player->xPos() > pacman4->currentX() - 1 && player->xPos() < pacman4->currentX() + 1 &&//pacman4X
			player->yPos() > pacman4->currentY() - 1 && player->yPos() < pacman4->currentY() + 1)//pacman4Y
		{
			//reset game
			pacman1->reset();
			pacman2->reset();
			pacman3->reset();
			pacman4->reset();
			player->reset();
			level->resetLevel();//put all the ghost drops back
			lastButtonPress = 0;
		}


		

		//pacman moves towards player
		pacman1->move(player->xPos(), player->yPos(), buffer);
		pacman2->move(player->xPos(), player->yPos(), buffer);
		pacman3->move(player->xPos(), player->yPos(), buffer);
		pacman4->move(player->xPos(), player->yPos(), buffer);

		//find out player co ords in relation to the map class
		if (input->isKeyDown(aie::INPUT_KEY_RIGHT) && player->xPos() < windowWidth && tileToRight != 1
			&& tileToTopRight != 1 && tileToBotRight != 1) // if they input right, it cannot move offscreen & cant move into a Wall-tile square
		{
			player->moveRight(player->yPos(), tileSize);
			lastButtonPress = aie::INPUT_KEY_RIGHT;
			if (tileToRight == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
			{
				player->collectDrop();
				level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
				if (level->levelXpos(player->xPos()) == 20 && level->levelYpos(player->yPos()) == 11)//if your at the opening on the right side, teleport to the left side
				{
					level->teleportPlayer(player, "right", getWindowWidth(), getWindowHeight(), getWindowHeight() / 21 );
				}
			}
		}
		else if (input->isKeyDown(aie::INPUT_KEY_LEFT) && player->xPos() > 0 && tileToLeft != 1 &&
			tileToTopLeft != 1 && tileToBotLeft != 1)
		{
			player->moveLeft(player->yPos(), tileSize);
			lastButtonPress = aie::INPUT_KEY_LEFT;
			if (tileToLeft == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
			{
				player->collectDrop();
				level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
				
			}
			if (level->levelXpos(player->xPos()) == 0 && level->levelYpos(player->yPos()) == 11)//if your at the opening on the right side, teleport to the left side
			{
				level->teleportPlayer(player, "left", getWindowWidth(), getWindowHeight(),getWindowHeight() / 21);
			}
		}
		else if (input->isKeyDown(aie::INPUT_KEY_DOWN) && player->yPos() > 0 && tileDown != 1
			&& tileLeftDown != 1 && tileRightDown != 1)
		{
			player->moveDown(player->xPos(), tileSize);
			lastButtonPress = aie::INPUT_KEY_DOWN;
			if (tileDown == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
			{
				player->collectDrop();
				level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
			}
		}
		else if (input->isKeyDown(aie::INPUT_KEY_UP) && player->yPos() < windowHeight && tileUp != 1 &&
			tileLeftUp != 1 && tileRightUp != 1)
		{
			player->moveUp(player->xPos(), tileSize);
			lastButtonPress = aie::INPUT_KEY_UP;
			if (tileUp == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
			{
				player->collectDrop();
				level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
			}
		}

		else if (player->Collided() == false)// this just continues the players movement even if they're not holding a key. It will continue their last button press
		{
			switch(lastButtonPress)
			{
			case(aie::INPUT_KEY_RIGHT):
				{
				if(player->xPos() < windowWidth && tileToRight != 1)
					player->moveRight(player->yPos(), tileSize);
				if (tileToRight == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
				{
					player->collectDrop();
					level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
					
				}
				if (level->levelXpos(player->xPos()) == 20 && level->levelYpos(player->yPos()) == 11)//if your at the opening on the right side, teleport to the left side
				{
					level->teleportPlayer(player, "right", getWindowWidth(), getWindowHeight(), getWindowHeight() / 21);
				}
				}
				break;
			case(aie::INPUT_KEY_LEFT):
			{
				if(player->xPos() > 0 && tileToLeft != 1)
					player->moveLeft(player->yPos(), tileSize);
				if (tileToLeft == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
				{
					player->collectDrop();
					level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
					
				}
				if (level->levelXpos(player->xPos()) == 0 && level->levelYpos(player->yPos()) == 11)//if your at the opening on the right side, teleport to the left side
				{
					level->teleportPlayer(player, "left", getWindowWidth(), getWindowHeight(),getWindowHeight() / 21);
				}
			}
			break;
			case(aie::INPUT_KEY_DOWN):
			{
				if(player->yPos() > 0 && tileDown != 1)
					player->moveDown(player->xPos(), tileSize);
				if (tileDown == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
				{
					player->collectDrop();
					level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
				}
			}
			break;
			case(aie::INPUT_KEY_UP):
			{
				if(player->yPos() < windowHeight && tileUp != 1)
					player->moveUp(player->xPos(), tileSize);
				if (tileUp == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
				{
					player->collectDrop();
					level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
				}
			}
			break;

			}
		}
		for (int i = 0; i < collisionPoints; i++)
		{
			player->clamp(collisions[i], level->levelXpos(player->xPos()), level->levelXpos(player->yPos()), tileSize);
			if (player->Collided() == true)
			{
				i = collisionPoints;
			}
		}
		if (player->Collided() == true)
		{
			lastButtonPress = 0;
		}
	}


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}


void GhostsTale_v1App::draw() {

	// wipe the screen to the background colour
	clearScreen();


	// begin drawing sprites
	m_2dRenderer->begin();

	//float tileSize = getWindowHeight() / 21;

	// draw your stuff here!
	int x, y;
	aie::Input* input = aie::Input::getInstance();
	input->getMouseXY(&x, &y);
	int HalfOfWindowWidth = getWindowWidth() / 2;
	int HalfOfWindowHeight = getWindowHeight() / 2;
	Button StartButton(HalfOfWindowWidth, HalfOfWindowHeight, startButtonWidth, startButtonHeight);
	Button SettingsButton(HalfOfWindowWidth, HalfOfWindowHeight - 150, settingsButtonWidth, settingsButtonHeight);
	
	float tileSize = getWindowHeight() / 21;
	

	switch (state)
	{
	case Title:

		m_2dRenderer->drawSprite(ghostTexture, getWindowWidth() / 2 - 100, getWindowHeight() / 2 - 150, 100, 100);
		m_2dRenderer->drawSprite(pacmanTexture, getWindowWidth() / 2 - 250, getWindowHeight() / 2 - 150, 100, 100);
		m_2dRenderer->drawSprite(ghostDrop, getWindowWidth() / 2, getWindowHeight() / 2 - 150, 30, 30);
		m_2dRenderer->drawSprite(ghostDrop, getWindowWidth() / 2 + 100, getWindowHeight() / 2 - 150, 30, 30);
		m_2dRenderer->drawSprite(ghostDrop, getWindowWidth() / 2 + 200, getWindowHeight() / 2 -150, 30, 30);
		m_2dRenderer->drawSprite(title, getWindowWidth() / 2, getWindowHeight() - 250, 600, 300);
		m_2dRenderer->drawText(m_font, "Press Enter to continue", getWindowWidth() / 2 - 200, getWindowHeight() - 450);

		break;

	case Menu:
		//print menu
		
		StartButton.Draw(m_2dRenderer, startButtonTexture);
		SettingsButton.Draw(m_2dRenderer, settingsButtonTexture);

		break;
	case Settings:
		//print settings 

		//music up and down arrows
		m_2dRenderer->drawText(m_font, "Music volume", 650, 500);
		m_2dRenderer->drawSprite(upArrow, 650, 600, 100, 100);
		m_2dRenderer->drawSprite(downArrow, 650, 400, 100, 100);
		//FX up and down arrows
		m_2dRenderer->drawText(m_font, "FX volume", 650, 200);
		m_2dRenderer->drawSprite(upArrow, 650, 300, 100, 100);
		m_2dRenderer->drawSprite(downArrow, 650, 100, 100, 100);
		break;
	case Game:
		//startGame
		level->print(m_2dRenderer, wallTile, tileSize, tileSize, ghostDrop);
		
		m_2dRenderer->drawSprite(ghostTexture, player->xPos(), player->yPos(), tileSize, tileSize);//print ghost
		//m_2dRenderer->drawBox(player->xPos(), player->yPos(), tileSize, tileSize);
		m_2dRenderer->drawSprite(pacmanTexture, pacman1->currentX(), pacman1->currentY(), tileSize, tileSize);//print pacman1
		m_2dRenderer->drawSprite(pacmanTexture, pacman2->currentX(), pacman2->currentY(), tileSize, tileSize);//print pacman2
		m_2dRenderer->drawSprite(pacmanTexture, pacman3->currentX(), pacman3->currentY(), tileSize, tileSize);//print pacman3
		m_2dRenderer->drawSprite(pacmanTexture, pacman4->currentX(), pacman4->currentY(), tileSize, tileSize);//print pacman1
		
		
		break;

	case Win:
		m_2dRenderer->drawText(m_font, "You Win", getWindowWidth() / 2, getWindowHeight() / 2);
		break;
	}

	// output some text, uses the last used colour
	char fps[64];
	sprintf_s(fps, 64, "FPS: %i", getFPS());
	if (state != Game)
	{
		m_2dRenderer->drawText(m_font, "Press ESC to quit", 10, 10);
	}

	// done drawing sprites
	m_2dRenderer->end();
}