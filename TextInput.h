#pragma once
#include "GameObject.h"


class TextInput : public GameObject {

	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;
	bool isFocused = false;

	bool isAlphaNumericTextEntered(sf::Event& event) {
		return
			event.type == event.TextEntered &&
			(isalnum(event.text.unicode) || event.text.unicode == '.');
	}

	bool isBackSpace(sf::Event& event) {
		return
			event.type == event.KeyPressed &&
			event.key.code == sf::Keyboard::Backspace;
	}

protected:

	virtual void onDraw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(shape);
		window.draw(text);
	}

	virtual void onEvent(sf::Event& event) {
		if (isAlphaNumericTextEntered(event)) {
			text.setString(text.getString() + char(event.text.unicode));
		}
		else if (isBackSpace(event) && text.getString().getSize() > 0) {
			std::string oldText = text.getString();
			oldText.pop_back();
			text.setString(oldText);
		}
	}

public:

	TextInput(Size size, Position position, int textSize = 32, const std::string& fontPath = "arial.ttf") {
		shape.setFillColor(sf::Color::White);
		font.loadFromFile(fontPath);
		text.setFont(font);
		text.setCharacterSize(textSize);
		text.setFillColor(sf::Color::Black);
		setSize(size);
		setPosition(position);
	}

	std::string getText() { return text.getString();  }
	virtual void setSize(Size size) { shape.setSize(size); }
	virtual void setPosition(Position position) {
		shape.setPosition(position);
		text.setPosition(position);
	}
};