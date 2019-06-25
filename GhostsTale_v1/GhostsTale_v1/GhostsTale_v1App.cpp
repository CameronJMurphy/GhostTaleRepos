#include "GhostsTale_v1App.h"

#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>
#include <Windows.h>
#include <WinUser.h>

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
	ghost = new aie::Texture("./textures/ghost.png");
	ghostDrop = new aie::Texture("./textures/ghostDrop.svg.png");
	title = new aie::Texture("./textures/Title.png");
	settingsButton = new aie::Texture("./textures/SettingsButton.png");
	startButton = new aie::Texture("./textures/StartButton.png");
	upArrow = new aie::Texture("./textures/UpArrow.png");
	downArrow = new aie::Texture("./textures/DownArrow.png");
	

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	//printTitle();

	m_timer = 0;


	return true;
}

void GhostsTale_v1App::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete wallTile;
	delete pacman;
	delete ghost;
}

void GhostsTale_v1App::update(float deltaTime) {

	m_timer += deltaTime;

	POINT mousePos;
	GetCursorPos(&mousePos);

	// input example
	aie::Input* input = aie::Input::getInstance();

	

	if (state == Title)
	{
		if (input->isKeyDown(aie::INPUT_KEY_ENTER))
		{
			state = Menu;
		}
	}
	else if (state == Menu)
	{
		if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		{
			state = Settings;
		}
		if (input->isKeyDown(aie::INPUT_KEY_UP))
		{
			state = Game;
		}
		if (input->isKeyDown(aie::INPUT_MOUSE_BUTTON_LEFT))//if you click start, turn state to "Game"
		{
			cout << "What";
			//To tell if they clicked the start button
			if (mousePos.x >= startButtonPosX && mousePos.x <= (startButtonPosX + startButtonWidth))
			{
				cout << "made it this far";
				if (mousePos.y >= startButtonPosY && mousePos.y <= (startButtonPosY + startButtonHeight))
				{
					cout << "we made it";
					state = Game;
				}
			}
		}
	}
	else if (state == Settings)
	{
		if (input->isKeyDown(aie::INPUT_KEY_BACKSPACE))
		{
			state = Menu;
		}
	}
	else if (state == Game)
	{
		if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		{
			ghostPosX += 100;
		}
		if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		{
			ghostPosX -= 100;
		}
		if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		{
			ghostPosY += 100;
		}
		if (input->isKeyDown(aie::INPUT_KEY_UP))
		{
			ghostPosY -= 100;
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
	switch (state)
	{
	case Title:

		m_2dRenderer->drawSprite(ghost, 600, 200, 100, 100);
		m_2dRenderer->drawSprite(pacman, 420, 200, 100, 100);
		m_2dRenderer->drawSprite(ghostDrop, 700, 200, 30, 30);
		m_2dRenderer->drawSprite(ghostDrop, 800, 200, 30, 30);
		m_2dRenderer->drawSprite(ghostDrop, 900, 200, 30, 30);
		m_2dRenderer->drawSprite(title, 650, 500, 600, 300);
		m_2dRenderer->drawText(m_font, "Press Enter to continue", 450, 320);

		break;

	case Menu:
		//print menu
		m_2dRenderer->drawSprite(ghost,650, 600, 100, 100);
		m_2dRenderer->drawSprite(startButton, startButtonPosX, startButtonPosY, startButtonHeight, startButtonWidth);
		m_2dRenderer->drawSprite(settingsButton, settingsButtonPosX, settingsButtonPosY, settingsButtonHeight, settingsButtonWidth);
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
		cout << "hello";
		m_2dRenderer->drawSprite(ghost, ghostPosX, ghostPosY, 100, 100);
		break;
	}

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 10, 10);

	// done drawing sprites
	m_2dRenderer->end();
}