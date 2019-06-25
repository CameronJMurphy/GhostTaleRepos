#pragma once

#include "Application.h"
#include "Renderer2D.h"

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
	aie::Texture*		pacman;
	aie::Texture*		ghost;
	aie::Texture*		ghostDrop;
	aie::Texture*		title;
	aie::Texture*		settingsButton;
	aie::Texture*		startButton;
	aie::Texture*		upArrow;
	aie::Texture*		downArrow;
	

	int state = 0;

	float m_timer;

	int startButtonPosX = 650;
	int startButtonPosY = 400;
	int startButtonHeight = 600;
	int startButtonWidth = 300;

	int settingsButtonPosX = 650;
	int settingsButtonPosY = 250;
	int settingsButtonHeight = 400;
	int settingsButtonWidth = 100;

	int ghostPosX = 0;
	int ghostPosY = 0;
};