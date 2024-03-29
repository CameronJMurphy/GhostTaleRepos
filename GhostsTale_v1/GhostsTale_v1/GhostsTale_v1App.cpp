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
#include <assert.h>

using namespace std;

enum
{
	Title,
	Menu,
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
	wallTile = new aie::Texture("./bin/textures/grass.png");
	pacmanTexture = new aie::Texture("./bin/textures/pacman.png");
	ghostTexture = new aie::Texture("./bin/textures/ghost.png");
	ghostDrop = new aie::Texture("./bin/textures/ghostDrop.svg.png");
	title = new aie::Texture("./bin/textures/Title.png");
	settingsButtonTexture = new aie::Texture("./bin/textures/SettingsButton.png");
	startButtonTexture = new aie::Texture("./bin/textures/StartButton.png");
	VolumeUpTexture = new aie::Texture("./bin/textures/VolumeUp.png");
	VolumeDownTexture = new aie::Texture("./bin/textures/VolumeDown.png");
	pacmanPreyVersion = new aie::Texture("./bin/textures/pacmanPrey.png");

	player = new ghost();

	level = new Map(getWindowWidth(), getWindowHeight());

	pacman[0] = new Pacman(level, 200, 200, 100);
	pacman[1] = new Pacman(level, 600, 600, 125);
	pacman[2] = new Pacman(level, 600, 200, 80);
	pacman[3] = new Pacman(level, 200, 600, 90);
	
	
	

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("./bin/font/consolas.ttf", 32);

	
	//assert (chompBuffer.loadFromFile("F:/aieBootstrap-master/GhostTaleRepos/GhostsTale_v1/GhostsTale_v1/bin/sounds/pacman_chomp.wav"));
	bool chompBufferWorked = chompBuffer.loadFromFile("./bin/sounds/pacman_chomp.wav");
	assert(chompBufferWorked);
	chompSound.setBuffer(chompBuffer);
	chompSound.setVolume(3);

	//assert(musicBuffer.loadFromFile("F:/aieBootstrap-master/GhostTaleRepos/GhostsTale_v1/GhostsTale_v1/bin/sounds/music.wav"));
	bool musicBufferWorked = musicBuffer.loadFromFile("./bin/sounds/music.wav");
	assert(musicBufferWork);
	music.setBuffer(musicBuffer);
	music.setVolume(9);

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
	for (int i = 0; i < enemyCount; ++i)
	{
		delete pacman[i];
	}
}

void GhostsTale_v1App::update(float deltaTime) {

	m_timer += deltaTime;
	aie::Input* input = aie::Input::getInstance();
	const unsigned int windowHeight = getWindowHeight();
	const unsigned int windowWidth = getWindowWidth();

	
	int counter = 0;
	for (int i = aie::INPUT_KEY_0; i <= aie::INPUT_KEY_9; ++i)//if the user press between 0 and 9 it will change the volume of the music and sound effects
	{
		if (input->isKeyDown(i))
		{
			chompSound.setVolume(counter / 3);
			music.setVolume(counter);
			counter = 0;
		}
		++counter;
	}

	if (music.getStatus() == sf::SoundSource::Status::Stopped)//this stops overlap of music
	{
		music.play();
	}

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


		}


	}


	////////////////////	GAME	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	else if (state == Game)
	{
		
		float buffer = (getWindowHeight() / 21) / 2;//half of pacmans size, this is used for the pacmans collision


		//if the players collect all the orbs, they win
		if (level->ghostDropsRemaining() == false)
		{
			state = Win;
		}

		if (player->currentDrops() == 50)//every 50 orbs collected pacman turn to prey
		{
			player->editDropCount(0);
			for (int i = 0; i < enemyCount; ++i)
			{
				pacman[i]->turnToPrey();
				
			}
		}
		for (int i = 0; i < enemyCount; ++i)
		{
			if (pacman[i]->isPredator() == false)//check to see if at least one of the pacman are in a prey state
			{

				if (pacman[i]->preyTimer(deltaTime))
				{
					pacman[i]->turnToPredator();
				}

			}
		}
		//++counter;

		//if any of the pacman are touching the player, you lose the game

		for (int i = 0; i < enemyCount; ++i)
		{
			if (pacman[i]->isColliding(player) && pacman[i]->isPredator() == true)
			{
				//reset game
				for (int i = 0; i < enemyCount; ++i)
				{
					pacman[i]->reset();
				}
				player->reset();
				level->resetLevel();//put all the ghost drops back
				lastButtonPress = 0;
				break;
			}
			else if (pacman[i]->isColliding(player) && pacman[i]->isPredator() == false)
			{
				pacman[i]->die(tileSize);
			}
		}

		//if the pacman are dead, they need to respawn after 5 seconds
		for (int i = 0; i < enemyCount; ++i)
		{
			//this sees if the pacman is ready to spawn, if not it ticks up its respawn timer
			if (pacman[i]->respawnCheck() == true)
			{
				pacman[i]->reset();
			}
		}
		

		//pacman moves towards player
		for (int i = 0; i < enemyCount; ++i)
		{
			pacman[i]->move(player->xPos(), player->yPos(), buffer, deltaTime);
		}

		//playerMovement handles the movement the collision of players
		playerMovement(deltaTime);
		

		
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

	Button VolumeUp(HalfOfWindowWidth, HalfOfWindowHeight, volumeUpButtonWidth, volumeUpButtonHeight);
	Button VolumeDown(HalfOfWindowWidth, HalfOfWindowHeight - 150, volumeDownButtonWidth, volumeDownButtonHeight);

	
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
		//SettingsButton.Draw(m_2dRenderer, settingsButtonTexture);

		break;
	case Game:
		//startGame
		level->print(m_2dRenderer, wallTile, tileSize, tileSize, ghostDrop);
		
		m_2dRenderer->drawSprite(ghostTexture, player->xPos(), player->yPos(), tileSize, tileSize);//print ghost
		
		for (int i =0; i < enemyCount; ++i)
		{
			if (pacman[i]->isPredator() == true)
			{
				m_2dRenderer->drawSprite(pacmanTexture, pacman[i]->currentX(), pacman[i]->currentY(), tileSize, tileSize);//print pacman
			}
			else
			{
				m_2dRenderer->drawSprite(pacmanPreyVersion, pacman[i]->currentX(), pacman[i]->currentY(), tileSize, tileSize);//print pacman
			}

		}
		
		

		
		break;

	case Win:
		m_2dRenderer->drawText(m_font, "You Win", getWindowWidth() / 2.5, getWindowHeight() / 2);
		break;
	}

	// output some text, uses the last used colour
	char fps[64];
	sprintf_s(fps, 64, "FPS: %i", getFPS());
	if (state != Game)
	{
		m_2dRenderer->drawText(m_font, "Press between 0 & 9 to change volume", 35, 20);
	}

	// done drawing sprites
	m_2dRenderer->end();
}


void GhostsTale_v1App::playerMovement(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	const unsigned int windowHeight = getWindowHeight();
	const unsigned int windowWidth = getWindowWidth();

	tileSize = getWindowHeight() / 21;
	int currentPos = level->getTile(player->xPos(), player->yPos());
	float buffer = (getWindowHeight() / 21) / 2 - .0001;//half of player size


	int tilePlayerIsOn = level->getTile(player->xPos(), player->yPos());

	//figure out what surrounding tiles of the player are, from the centre on the image
	int tileToRight = level->getTile(player->xPos() + buffer, player->yPos());
	int tileToLeft = level->getTile(player->xPos() - buffer, player->yPos());
	int tileDown = level->getTile(player->xPos(), player->yPos() - buffer);
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

	const int collisionPoints = 8;
	int collisions[collisionPoints]{tileToTopRight,tileToTopLeft,tileToBotRight,tileToBotLeft,tileLeftDown,tileLeftUp,tileRightDown,tileRightUp };
	
	
		

	if (player->Collided() == false)
	{
		if (input->isKeyDown(aie::INPUT_KEY_RIGHT) && player->xPos() < windowWidth//tileToRight != 1
			&& tileToTopRight != 1 && tileToBotRight != 1) // if they input right, it cannot move offscreen & cant move into a Wall-tile square
		{
			player->moveRight(tileSize, deltaTime);
			lastButtonPress = aie::INPUT_KEY_RIGHT;

			if (tilePlayerIsOn == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
			{
				player->collectDrop(); // add 1 to the players ghost drop collection
				playChomp(); //this is a sound effect
				level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
				if (level->levelXpos(player->xPos()) == 20 && level->levelYpos(player->yPos()) == 11)//if your at the opening on the right side, teleport to the left side
				{
					level->teleportPlayer(player, "right", getWindowWidth(), getWindowHeight(), getWindowHeight() / 21);
				}
			}
		}
		else if (input->isKeyDown(aie::INPUT_KEY_LEFT) && player->xPos() > 0 //tileToLeft != 1 
			&& tileToTopLeft != 1 && tileToBotLeft != 1)
		{
			player->moveLeft(tileSize, deltaTime);
			lastButtonPress = aie::INPUT_KEY_LEFT;

			if (tilePlayerIsOn == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
			{
				player->collectDrop();
				playChomp(); //this is a sound effect
				level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space

			}
			if (level->levelXpos(player->xPos()) == 0 && level->levelYpos(player->yPos()) == 11)//if your at the opening on the right side, teleport to the left side
			{
				level->teleportPlayer(player, "left", getWindowWidth(), getWindowHeight(), getWindowHeight() / 21);
			}
		}
		else if (input->isKeyDown(aie::INPUT_KEY_DOWN) && player->yPos() > 0//tileDown != 1
			&& tileLeftDown != 1 && tileRightDown != 1)
		{
			player->moveDown(tileSize, deltaTime);
			lastButtonPress = aie::INPUT_KEY_DOWN;
			if (tilePlayerIsOn == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
			{
				player->collectDrop();
				playChomp(); //this is a sound effect
				level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
			}
		}
		else if (input->isKeyDown(aie::INPUT_KEY_UP) && player->yPos() < windowHeight //tileUp != 1 
			&& tileLeftUp != 1 && tileRightUp != 1)
		{
			player->moveUp(tileSize, deltaTime);
			lastButtonPress = aie::INPUT_KEY_UP;
			if (tilePlayerIsOn == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
			{
				player->collectDrop();
				playChomp(); //this is a sound effect
				level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
			}
		}

		else// this just continues the players movement even if they're not holding a key. It will continue their last button press
		{
			switch (lastButtonPress)
			{
			case(aie::INPUT_KEY_RIGHT):
			{
				if (player->xPos() < windowWidth && tileToTopRight != 1 && tileToBotRight != 1)
					player->moveRight(tileSize, deltaTime);
				if (tilePlayerIsOn == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
				{
					player->collectDrop();
					playChomp(); //this is a sound effect
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
				if (player->xPos() > 0 && tileToTopLeft != 1 && tileToBotLeft != 1)
					player->moveLeft(tileSize, deltaTime);
				if (tilePlayerIsOn == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
				{
					player->collectDrop();
					playChomp(); //this is a sound effect
					level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space

				}
				if (level->levelXpos(player->xPos()) == 0 && level->levelYpos(player->yPos()) == 11)//if your at the opening on the right side, teleport to the left side
				{
					level->teleportPlayer(player, "left", getWindowWidth(), getWindowHeight(), getWindowHeight() / 21);
				}
			}
			break;
			case(aie::INPUT_KEY_DOWN):
			{
				if (player->yPos() > 0 && tileLeftDown != 1 && tileRightDown != 1)
					player->moveDown(tileSize, deltaTime);
				if (tilePlayerIsOn == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
				{
					player->collectDrop();
					playChomp(); //this is a sound effect
					level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
				}
			}
			break;
			case(aie::INPUT_KEY_UP):
			{
				if (player->yPos() < windowHeight && tileLeftUp != 1 && tileRightUp != 1)
					player->moveUp(tileSize, deltaTime);
				if (tilePlayerIsOn == 8)//if the tile they just moved to had a ghost drop, increase ghost drop count
				{
					player->collectDrop();
					playChomp(); //this is a sound effect
					level->updateMap(player->xPos(), player->yPos(), 0);//change to the map's 8 to a 0, this displays a blank space
				}
			}
			break;

			}
		}
	}
	for (int i = 0; i < collisionPoints; i++)
	{
		player->clamp(collisions[i], level->levelXpos(player->xPos()), level->levelXpos(player->yPos()), tileSize);
		if (player->Collided() == true)
		{
			break;
		}
	}
	if (player->Collided() == true)
	{
		lastButtonPress = 0;
	}
}


void GhostsTale_v1App::playChomp()
{
	if (chompSound.getStatus() == sf::SoundSource::Status::Stopped)
	{
		chompSound.play();
	}
}

void GhostsTale_v1App::changeVolume(int volume)
{
	chompSound.setVolume(volume / 3);
	music.setVolume(volume);
}
