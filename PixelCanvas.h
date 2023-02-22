#pragma once
#include "GameObject.h"


class PixelCanvas : public GameObject {

	sf::Sprite sprite;
	sf::Image image;
	sf::Texture texture;
	sf::Color currentColor;

	void updateSprite() {
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}

protected:

	virtual void onDraw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(sprite, states);
	}

public:

	PixelCanvas(float x, float y, float width, float height) {
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

	void setColor(sf::Color color) { this->currentColor = color; }
	void setPixel() { }

};