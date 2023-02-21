#pragma once
#include "GameObject.h"


class Button : public GameObject {

	sf::RectangleShape shape;

protected:

	void onDraw(sf::RenderTarget& win, sf::RenderStates states) const {
		win.draw(shape, states);
	}

public:
	Button() {}

	Button(sf::Color color, float x = 0, float y = 0, float width = 50, float height = 50) {
		shape.setFillColor(color);
		setPosition(sf::Vector2f(x, y));
		setSize(sf::Vector2f(width, height));
	};

	bool isPressed(sf::Vector2f point) {
		return shape.getGlobalBounds().contains(point);
	}

	virtual void setSize(sf::Vector2f size) { shape.setSize(size); }
	virtual void setPosition(sf::Vector2f position) { shape.setPosition(position); }
	virtual sf::Vector2f getSize() { return shape.getSize(); }
	virtual sf::Vector2f getPosition() { return shape.getPosition(); }
};