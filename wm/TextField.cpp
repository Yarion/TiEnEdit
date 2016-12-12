#include "TextField.h"

#include "../menu/MenuOverlay.h"
#include <VrLib/Kernel.h>
#include <VrLib/Font.h>

#include <Windows.h> // TODO: keycodes

TextField::TextField(const std::string & value, glm::ivec2 position)
{
	this->value = value;
	this->position = position;
}


void TextField::draw(MenuOverlay * overlay)
{

	overlay->drawRect(glm::vec2(128, 328), glm::vec2(128 + 37, 328 + 33), absPosition, absPosition + size); //text background
	overlay->flushVerts();

	if (focussed)
	{
		overlay->shader->setUniform(MenuOverlay::Uniforms::colorMult, glm::vec4(0.1f, 0.1f, 1, 1)); //TODO
		overlay->drawRect(glm::vec2(8, 328), glm::vec2(8 + 37, 328 + 33), absPosition, absPosition + size);
		overlay->shader->setUniform(MenuOverlay::Uniforms::colorMult, glm::vec4(1, 1, 1, 1));
	}

	glm::ivec2 windowSize = vrlib::Kernel::getInstance()->getWindowSize();

	glEnable(GL_SCISSOR_TEST);
	glScissor(absPosition.x+5, 0, size.x-15, 10000);
	overlay->drawText(value, absPosition + glm::ivec2(5, 14));

	if (focussed && (GetTickCount() / 250) % 2 == 0)
	{
		int offset = overlay->font->textlen(value.substr(0, cursor));
		overlay->drawText("|", absPosition + glm::ivec2(5 + offset-3, 13));
	}


	glDisable(GL_SCISSOR_TEST);
}

bool TextField::click(bool leftButton, const glm::ivec2 & clickPos)
{
	cursor = value.size();
	return true;
}

void TextField::keyChar(char character)
{
	if (character > 31)
	{
		value = value.substr(0, cursor) + character + value.substr(cursor);
		cursor++;
		if (onChange)
			onChange();
	}
	else if (character == 8)
	{
		if (cursor > 0)
		{
			value = value.substr(0, cursor - 1) + value.substr(cursor);
			cursor--;
			if (onChange)
				onChange();
		}
	}
}

void TextField::keyUp(int keyCode)
{
	if (keyCode == VK_DELETE && cursor < value.size() - 1)
	{
		value = value.substr(0, cursor) + value.substr(cursor + 1);
		if (onChange)
			onChange();
	}

	if (keyCode == VK_LEFT && cursor > 0)
		cursor--;
	if (keyCode == VK_RIGHT && cursor < value.size())
		cursor++;
	if (keyCode == VK_HOME)
		cursor = 0;
	if (keyCode == VK_END)
		cursor = value.size();

}