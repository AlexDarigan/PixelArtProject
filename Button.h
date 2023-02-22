#pragma once
#include "GameObject.h"
#include "Callback.h"
#include "App.h"
#include "CollisionShape.h"

class Button : public GameObject, public Color {
	
	CollisionShape* collider = nullptr;
	sf::RectangleShape shape;

protected:

	void onDraw(sf::RenderTarget& win, sf::RenderStates states) const {
		win.draw(shape, states);
	}

	void onEvent(sf::Event& event) { collider->process(event); }

public:

	Button(sf::Color color, float x = 0, float y = 0, float width = 50, float height = 50) {
		shape.setFillColor(color);
		setPosition(sf::Vector2f(x, y));
		setSize(sf::Vector2f(width, height));;
		collider = new CollisionShape(this);
	}

	void setOnMouseDragged(Callback* callback) { collider->setOnMouseDragged(callback); }
	void setOnPressed(Callback* callback) { collider->setOnMouseLeftButtonPressed(callback); }
	virtual void setSize(Size size) { shape.setSize(size); }
	virtual void setPosition(Position position) { shape.setPosition(position); }
	virtual Size getSize() { return shape.getSize(); }
	virtual Position getPosition() { return shape.getPosition(); }
	virtual void setColor(sf::Color color) { shape.setFillColor(color); }
	virtual sf::Color getColor() { return shape.getFillColor(); }
};