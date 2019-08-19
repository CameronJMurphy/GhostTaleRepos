#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Button.h"
#include "Ghost.h"
#include "Map.h"
#include "pacman.h"
#include <SFML/Audio.hpp> 


class GhostsTale_v1App : public aie::Application {
public:

	GhostsTale_v1App();
	virtual ~GhostsTale_v1App();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void playerMovement(float deltaTime);//playerMovement
	
	void playChomp();
	
	void changeVolume(int volume);
	

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
	aie::Texture*		VolumeUpTexture;
	aie::Texture*		VolumeDownTexture;
	aie::Texture*		pacmanPreyVersion;
	
	
	ghost* player;
	Map* level;
	
	Pacman* pacman[4];
	const int enemyCount = 4;
	int lastButtonPress;
	


	int state = 0;

	

	float m_timer;

	
	int startButtonHeight = 150;
	int startButtonWidth = 300;

	
	int settingsButtonHeight = 100;
	int settingsButtonWidth = 200;

	int volumeUpButtonHeight = 50;
	int volumeUpButtonWidth = 50;

	int volumeDownButtonHeight = 50;
	int volumeDownButtonWidth = 50;

	int ghostPosX = 50;
	int ghostPosY = 50;

	int HalfOfWindowWidth = getWindowWidth() / 2;
	int HalfOfWindowHeight = getWindowHeight() / 2;

	const int mapLength = 21;
	const int mapHeight = 21;

	float tileSize;

	sf::SoundBuffer chompBuffer;
	sf::Sound chompSound;
	
	sf::SoundBuffer musicBuffer;
	sf::Sound music;

};