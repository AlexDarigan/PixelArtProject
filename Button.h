#pragma once
#include "GameObject.h"
#include "Callback.h"
#include "App.h"

class Button : public GameObject, public Color {
	
	Callback* callback = nullptr;
	sf::RectangleShape shape;

	bool isPressed(sf::Event& event) {
		return
			event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Left &&
			shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y);
	}

	bool isMouseDragged(sf::Event& event) {
		return
			event.type == sf::Event::MouseMoved &&
			sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			shape.getGlobalBounds().contains(App::getMousePosition().x, App::getMousePosition().y);
	}


protected:

	void onDraw(sf::RenderTarget& win, sf::RenderStates states) const {
		win.draw(shape, states);
	}

	void onEvent(sf::Event& event) {
		if (isPressed(event)) {
			std::cout << "Left Clicked" << std::endl;
			callback->call();
			if (callback != nullptr) { callback->call(); }
		}
		else if (isMouseDragged(event)) {
			std::cout << "Mouse Dragged" << std::endl;
			if (callback != nullptr) { callback->call(); }
		}
	}

public:

	Button(sf::Color color, float x = 0, float y = 0, float width = 50, float height = 50) {
		shape.setFillColor(color);
		setPosition(sf::Vector2f(x, y));
		setSize(sf::Vector2f(width, height));;
	}

	bool isPressed(sf::Vector2f point) { return shape.getGlobalBounds().contains(point); }
	void setCallback(Callback* callback) { this->callback = callback; }
	virtual void setSize(sf::Vector2f size) { shape.setSize(size); }
	virtual void setPosition(sf::Vector2f position) { shape.setPosition(position); }
	virtual sf::Vector2f getSize() { return shape.getSize(); }
	virtual sf::Vector2f getPosition() { return shape.getPosition(); }
	virtual void setColor(sf::Color color) { shape.setFillColor(color); }
	virtual sf::Color getColor() { return shape.getFillColor(); }
};