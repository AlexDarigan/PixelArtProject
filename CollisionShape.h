// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Callback.h"
#include "App.h"

class CollisionShape {

	GameObject* obj = nullptr;
	Callback* onLeftMouseButtonPressed = nullptr;
	Callback* onMouseDragged = nullptr;
	Callback* onMouseButtonReleased = nullptr;
	Callback* onCtrlV = nullptr;

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

	bool isMouseButtonReleased(sf::Event& event, sf::RectangleShape shape) {
		return
			event.type == sf::Event::MouseButtonReleased &&
			shape.getGlobalBounds().contains(App::getMousePosition().x, App::getMousePosition().y);
	}

	bool isCtrlVPressed(sf::Event& event, sf::RectangleShape shape) {
		return
			event.type == event.KeyPressed &&
			event.key.control &&
			event.key.code == sf::Keyboard::V &&
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
		else if (isMouseButtonReleased(event, bounds)) {
			if (onMouseButtonReleased != nullptr) { onMouseButtonReleased->call(); }
		}
		else if (isCtrlVPressed(event, bounds)) {
			onCtrlV->call();
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
	void setOnMouseReleased(Callback* callback) { onMouseButtonReleased = callback; }
	void setOnCtrlV(Callback* callback) { onCtrlV = callback;  }
};
