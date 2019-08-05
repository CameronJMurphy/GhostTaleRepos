#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Button.h"
#include "Ghost.h"
#include "Map.h"
#include "pacman.h"


class GhostsTale_v1App : public aie::Application {
public:

	GhostsTale_v1App();
	virtual ~GhostsTale_v1App();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	


protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	aie::Texture*		wallTile;
	aie::Texture*		pacmanTexture;
	aie::Texture*		ghostTexture;
	aie::Texture*		ghostDrop;
	aie::Texture*		title;
	aie::Texture*		settingsButtonTexture;
	aie::Texture*		startButtonTexture;
	aie::Texture*		upArrow;
	aie::Texture*		downArrow;
	
	ghost* player;
	Map* level;
	Pacman* pacman1;
	Pacman* pacman2;
	Pacman* pacman3;
	Pacman* pacman4;

	int lastButtonPress;
	
	

	int state = 0;

	float m_timer;

	int startButtonPosX = getWindowWidth() / 2;
	int startButtonPosY = getWindowWidth() / 2;
	int startButtonHeight = 150;
	int startButtonWidth = 300;

	int settingsButtonPosX = getWindowWidth() / 2;
	int settingsButtonPosY = getWindowWidth() / 2 - 100;
	int settingsButtonHeight = 100;
	int settingsButtonWidth = 200;

	int ghostPosX = 50;
	int ghostPosY = 50;

	int HalfOfWindowWidth = getWindowWidth() / 2;
	int HalfOfWindowHeight = getWindowHeight() / 2;

	const int mapLength = 21;
	const int mapHeight = 21;

	float tileSize;
	
	
	
	/*struct tilesSurrounding
	{
		int left;
		int right;
		int down;
		int up;
	};*/
	

};