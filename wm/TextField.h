#pragma once

#include "Component.h"
#include <string>
#include <functional>
#include <VrLib/tien/Component.h>

class TextField : public Component, public vrlib::tien::EditorBuilder::TextBox
{
public:
	std::string value;
	int cursor;
	int selectionEnd;

	TextField(const std::string &value, glm::ivec2 position);

	void draw(MenuOverlay * overlay);
	virtual bool click(bool leftButton, const glm::ivec2 & clickPos) override;


	virtual void keyChar(char character) override;
	virtual void keyUp(int keyCode) override;


	std::function<void()> onChange;

	inline std::string getText() const override { return value; }
	inline void setText(const std::string &text) override { value = text; }
};