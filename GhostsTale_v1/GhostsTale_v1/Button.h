#pragma once
#include "Renderer2D.h"
#include "Application.h"
#include "Texture.h"


class Button
{
private:
	int width, height, PosX, PosY;
public:

	Button(int PosX,int PosY, int width,int Height);
	
	~Button();

	void Draw(aie::Renderer2D* r, aie::Texture* texture);

	bool IsMouseOver(int mouseX, int mouseY);
	
};
