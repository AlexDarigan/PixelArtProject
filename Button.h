#pragma once
#include "GameObject.h"
#include "Callback.h"
#include "App.h"
#include "CollisionShape.h"

class Button : public GameObject, public Color {
	
	CollisionShape* collider = nullptr;
	sf::RectangleShape shape;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Text text;

protected:

	void onDraw(sf::RenderTarget& win, sf::RenderStates states) const {
		win.draw(shape, states);
		win.draw(sprite, states);
		win.draw(text, states);
	}

	void onEvent(sf::Event& event) { collider->process(event); }


public:

	Button(sf::Color color = sf::Color::White, float x = 0, float y = 0, float width = 50, float height = 50) {
		shape.setFillColor(color);
		setPosition(sf::Vector2f(x, y));
		setSize(sf::Vector2f(width, height));;
		collider = new CollisionShape(this);
	}

	void setImage(const std::string& texturePath) {
		texture.loadFromFile(texturePath);
		sprite.setTexture(texture);
		sprite.setScale(sf::Vector2f(0.125, 0.125));
	}

	void setText(sf::Text text) { 
		text.setFillColor(sf::Color::Black);
		this->text = text; 
	}
	void setOnMouseDragged(Callback* callback) { collider->setOnMouseDragged(callback); }
	void setOnPressed(Callback* callback) { collider->setOnMouseLeftButtonPressed(callback); }
	virtual void setSize(Size size) { shape.setSize(size); }
	virtual void setPosition(Position position) { 
		shape.setPosition(position);
		sprite.setPosition(position);
		text.setPosition(getPosition() + (Size(getSize().x / 4, 0)));
	}
	virtual Size getSize() { return shape.getSize(); }
	virtual Position getPosition() { return shape.getPosition(); }
	virtual void setColor(sf::Color color) { shape.setFillColor(color); }
	virtual sf::Color getColor() { return shape.getFillColor(); }
};