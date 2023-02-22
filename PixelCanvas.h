#pragma once
#include "GameObject.h"
#include "Callback.h"
#include "CollisionShape.h"
#include "ToolBox.h"

class PixelCanvas : public GameObject {

	ToolBox* toolBox;
	sf::Sprite sprite;
	sf::Image image;
	sf::Texture texture;
	sf::Color currentColor;
	CollisionShape* collider = nullptr;
	int brushSize = 10;

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

	PixelCanvas(ToolBox* toolBox, float x, float y, float width, float height) {
		this->toolBox = toolBox;
		collider = new CollisionShape(this);
		image.create(width, height);
		sprite.setPosition(x, y);

		for (auto x = 0; x < width; x++) {
			for (auto y = 0; y < height; y++) {
				//sf::Color color = (x + y) % 2 == 0 ? sf::Color::White : sf::Color::Black;
				image.setPixel(x, y, sf::Color::Black);
			}
		}

		updateSprite();
	}

	void setOnPressed(Callback* callback) { collider->setOnMouseLeftButtonPressed(callback); }
	void setOnMouseDragged(Callback* callback) { collider->setOnMouseDragged(callback); }
	void setColor(sf::Color color) { this->currentColor = color; }
	void setPixels() { 

		if (toolBox->getTool() != ToolBox::PaintBrush) {
			return;
		}

		Position relative = Position(App::getMousePosition() - sf::Vector2i(getPosition()));
		auto width = std::min(relative.x + getBrushSize(), getSize().x);
		auto height = std::min(relative.y + getBrushSize(), getSize().y);
		std::cout << "Setting Pixel: (" << relative.x << "," << relative.y << ") as " << currentColor.toInteger() << std::endl;
		
		// GetPixelBlock - Maybe use Paint Brush for this?
		for (auto i = relative.x; i < width; i++) {
			for (auto j = relative.y; j < height; j++) {
				image.setPixel(i, j, currentColor);
			}
		}
		
		updateSprite();
	}

	// Callbacks
	void erasePixel() { };
	sf::Color getPixelColor() { return sf::Color::White;  };
	void setBrushSize(int size) { brushSize = size; }
	int getBrushSize() { return brushSize; }
	
	virtual void setSize(Size size) { }
	virtual void setPosition(Position position) { }
	virtual Size getSize() { return Size(image.getSize()); }
	virtual Position getPosition() { return sprite.getPosition(); }

};

