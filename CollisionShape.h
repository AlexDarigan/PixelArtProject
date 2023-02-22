#pragma once

#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Callback.h"
#include "App.h"

class CollisionShape {

	GameObject* obj = nullptr;
	Callback* onLeftMouseButtonPressed = nullptr;
	Callback* onMouseDragged = nullptr;

	bool isLeftMouseButtonPressed(sf::Event& event, sf::RectangleShape shape) {
		return
			event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Left &&
			shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
	}

	bool isMouseDragged(sf::Event& event, sf::RectangleShape shape) {
		return
			event.type == sf::Event::MouseMoved &&
			sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			shape.getGlobalBounds().contains(App::getMousePosition().x, App::getMousePosition().y);
	}

	sf::RectangleShape getShape() {
		sf::RectangleShape shape;
		shape.setPosition(obj->getPosition());
		shape.setSize(obj->getSize());
		return shape;
	}

protected:

	virtual void onEvent(sf::Event& event) {
		sf::RectangleShape bounds = getShape();
		if (isMouseDragged(event, bounds)) {
			if (onMouseDragged != nullptr) { onMouseDragged->call(); }
		}
		else if (isLeftMouseButtonPressed(event, bounds)) {
			if (onLeftMouseButtonPressed != nullptr) { onLeftMouseButtonPressed->call(); }
		}
	}
	
public:

	CollisionShape(GameObject* obj) {
		this->obj = obj;
	}

	void process(sf::Event& event) {
		onEvent(event);
	}

	void setOnMouseDragged(Callback* callback) { onMouseDragged = callback; }
	void setOnMouseLeftButtonPressed(Callback* callback) { onLeftMouseButtonPressed = callback; }
};
