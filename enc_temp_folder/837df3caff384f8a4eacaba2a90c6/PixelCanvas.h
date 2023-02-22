#pragma once
#include "GameObject.h"
#include "Callback.h"
#include "CollisionShape.h"



class PixelCanvas : public GameObject {

	sf::Sprite sprite;
	sf::Image image;
	sf::Texture texture;
	sf::Color currentColor;
	CollisionShape* collider = nullptr;

	void updateSprite() {
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}

protected:

	virtual void onDraw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(sprite, states);
	}

	void onEvent(sf::Event& event) { collider->process(event); }


public:

	PixelCanvas(float x, float y, float width, float height) {
		collider = new CollisionShape(this);
		image.create(width, height);
		sprite.setPosition(x, y);

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				//sf::Color color = (x + y) % 2 == 0 ? sf::Color::White : sf::Color::Black;
				image.setPixel(x, y, sf::Color::Black);
			}
		}

		updateSprite();
	}

	void setOnPressed(Callback* callback) { collider->setOnMouseLeftButtonPressed(callback); }
	void setOnMouseDragged(Callback* callback) { collider->setOnMouseDragged(callback); }
	void setColor(sf::Color color) { this->currentColor = color; }
	void setPixel() { 
		sf::Vector2i pos = App::getMousePosition();
		int x = pos.x - getPosition().x;
		int y = pos.y - getPosition().y;
		std::cout << "Setting Pixel: (" << x << "," << y << " with a color of " << currentColor.toInteger() << std::endl;
		
		// GetPixelBlock - Maybe use Paint Brush for this?
		for (int i = x; i < (x + 10); i++) {
			for (int j = y; j < (y + 10); j++) {
				image.setPixel(i, j, currentColor);
			}
		}
		
		updateSprite();
	}

	virtual void setSize(Size size) { }
	virtual void setPosition(Position position) { }
	virtual Size getSize() { return Size(image.getSize()); }
	virtual Position getPosition() { return sprite.getPosition(); }

};

class SetColor : public Callback {

	PixelCanvas* pixelCanvas;
	sf::Color color;

protected:

	virtual void onCalled() {
		std::cout << "Changing Color" << std::endl;
		pixelCanvas->setColor(color);
	}

public:

	SetColor(PixelCanvas* pixelCanvas, sf::Color color) {
		this->pixelCanvas = pixelCanvas;
		this->color = color;
	}
};

class SetPixel : public Callback {

	PixelCanvas* pixelCanvas;

protected:

	virtual void onCalled() {
		pixelCanvas->setPixel();
	}

public:

	SetPixel(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
	}
};