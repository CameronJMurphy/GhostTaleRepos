#include "Button.h"
#include "Texture.h"
#include "Input.h"

Button::Button(int posX, int posY, int Width, int Height)
{
	PosX = posX;
	PosY = posY;
	width = Width;
	height =  Height;
}

Button::~Button()
{

}

void Button::Draw(aie::Renderer2D* r, aie::Texture* texture)
{
	r->drawSprite(texture, PosX, PosY, width, height);
}

bool Button::IsMouseOver(int mouseX,int mouseY)
{
	aie::Input* input = aie::Input::getInstance();

	int leftSideOfButton = PosX - (width / 2);
	int rightSideOfButton = PosX + (width / 2);
	int bottomSideOfButton = PosY - (height / 2);
	int topSideOfButton = PosY + (height / 2);

	if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT) &&
		mouseX >= leftSideOfButton && mouseX <= rightSideOfButton &&
		mouseY >= bottomSideOfButton && mouseY <= topSideOfButton)
	{
		return true;
	}
	else
	{
		return false;
	}
}