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

using namespace std;

enum
{
	Title,
	Menu,
	Settings,
	Game
};

GhostsTale_v1App::GhostsTale_v1App() {

}

GhostsTale_v1App::~GhostsTale_v1App() {

}

bool GhostsTale_v1App::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	//setup textures
	wallTile = new aie::Texture("./textures/grass.png");
	pacman = new aie::Texture("./textures/pacman.png");
	ghostTexture = new aie::Texture("./textures/ghost.png");
	ghostDrop = new aie::Texture("./textures/ghostDrop.svg.png");
	title = new aie::Texture("./textures/Title.png");
	settingsButtonTexture = new aie::Texture("./textures/SettingsButton.png");
	startButtonTexture = new aie::Texture("./textures/StartButton.png");
	upArrow = new aie::Texture("./textures/UpArrow.png");
	downArrow = new aie::Texture("./textures/DownArrow.png");

	player = new ghost();

	level = new Map(getWindowWidth(), getWindowHeight());
	

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
	delete pacman;
	delete ghostTexture;
	delete player;
	delete level;
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
		//basic movement

		int currentPos = level->getTile(player->xPos(), player->yPos());

		//find out player co ords in relation to the map class
		if (input->isKeyDown(aie::INPUT_KEY_RIGHT) && player->xPos() < windowWidth)
		{
			player->moveRight();
			lastButtonPress = aie::INPUT_KEY_RIGHT;
		}
		else if (input->isKeyDown(aie::INPUT_KEY_LEFT) && player->xPos() > 0)
		{
			player->moveLeft();
			lastButtonPress = aie::INPUT_KEY_LEFT;

		}
		else if (input->isKeyDown(aie::INPUT_KEY_DOWN) && player->yPos() > 0)
		{
			player->moveDown();
			lastButtonPress = aie::INPUT_KEY_DOWN;

		}
		else if (input->isKeyDown(aie::INPUT_KEY_UP) && player->yPos() < windowHeight)
		{
			player->moveUp();
			lastButtonPress = aie::INPUT_KEY_UP;

		}
		else // this just continues the players movement even if they're not holding a key. It will continue their last button press
		{
			switch(lastButtonPress)
			{
			case(aie::INPUT_KEY_RIGHT):
				{
				if(player->xPos() < windowWidth)
					player->moveRight();
				}
				break;
			case(aie::INPUT_KEY_LEFT):
			{
				if(player->xPos() > 0)
					player->moveLeft();
			}
			break;
			case(aie::INPUT_KEY_DOWN):
			{
				if(player->yPos() > 0)
					player->moveDown();
			}
			break;
			case(aie::INPUT_KEY_UP):
			{
				if(player->yPos() < windowHeight)
					player->moveUp();
			}
			break;

			}
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

	// draw your stuff here!
	int x, y;
	aie::Input* input = aie::Input::getInstance();
	input->getMouseXY(&x, &y);
	int HalfOfWindowWidth = getWindowWidth() / 2;
	int HalfOfWindowHeight = getWindowHeight() / 2;
	Button StartButton(HalfOfWindowWidth, HalfOfWindowHeight, startButtonWidth, startButtonHeight);
	Button SettingsButton(HalfOfWindowWidth, HalfOfWindowHeight - 150, settingsButtonWidth, settingsButtonHeight);
	

	

	switch (state)
	{
	case Title:

		m_2dRenderer->drawSprite(ghostTexture, getWindowWidth() / 2 - 100, getWindowHeight() / 2 - 150, 100, 100);
		m_2dRenderer->drawSprite(pacman, getWindowWidth() / 2 - 250, getWindowHeight() / 2 - 150, 100, 100);
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
		m_2dRenderer->drawSprite(ghostTexture, player->xPos(), player->yPos(), 50, 50);
		level->print(m_2dRenderer, wallTile, getWindowHeight() / 21, getWindowHeight() / 21, ghostDrop);
		
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