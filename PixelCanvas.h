// Student Name	: David Darigan
// Student ID	: C00263218

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
	int brushSize = 16;
	Position origin;
	sf::RectangleShape rectangle;
	sf::Image copiedRect;

	void updateSprite() {
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}

protected:

	virtual void onDraw(sf::RenderTarget& window, sf::RenderStates states) const {
		window.draw(sprite, states);
		window.draw(rectangle, states);
	}

	void onEvent(sf::Event& event) { collider->process(event); }


public:

	PixelCanvas(float x, float y, float width, float height) {
		collider = new CollisionShape(this);
		image.create(width, height);
		sprite.setPosition(x, y);

		const sf::Color grey = sf::Color(128, 128, 128, 255);
		for (auto x = 0; x < width; x++) {
			for (auto y = 0; y < height; y++) {
				image.setPixel(x, y, grey);
			}
		}

		updateSprite();
	}

	void setOnPressed(Callback* callback) { collider->setOnMouseLeftButtonPressed(callback); }
	void setOnMouseDragged(Callback* callback) { collider->setOnMouseDragged(callback); }
	void setOnMouseReleased(Callback* callback) { collider->setOnMouseReleased(callback); }
	void setOnCtrlV(Callback* callback) { collider->setOnCtrlV(callback); }
	void setColor(sf::Color color) { this->currentColor = color; }
	void setPixels() {

		Position relative = getRelativeMousePosition();
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

	void erasePixels() {

		Position relative = getRelativeMousePosition();
		auto width = std::min(relative.x + getBrushSize(), getSize().x);
		auto height = std::min(relative.y + getBrushSize(), getSize().y);
		std::cout << "Setting Pixel: (" << relative.x << "," << relative.y << ") as " << currentColor.toInteger() << std::endl;

		// GetPixelBlock - Maybe use Paint Brush for this?
		for (auto i = relative.x; i < width; i++) {
			for (auto j = relative.y; j < height; j++) {
				image.setPixel(i, j, sf::Color::White);
			}
		}

		updateSprite();
	}

	void drawRect(sf::Color outlineColor, sf::Color fillColor) {
		Position drag = Position(App::getMousePosition());
		rectangle.setFillColor(fillColor);
		rectangle.setOutlineColor(outlineColor);
		rectangle.setOutlineThickness(4);
		rectangle.setSize(Size(drag.x - origin.x, drag.y - origin.y));
	}

	void copyRect() {
		copiedRect = sf::Image();
		rectangle.setOutlineColor(sf::Color::Transparent);
		copiedRect.create(rectangle.getSize().x, rectangle.getSize().y);
		Position relative = rectangle.getPosition() - sprite.getPosition();
		for (int x = 0; x < rectangle.getSize().x; x++) {
			for (int y = 0; y < rectangle.getSize().y; y++) {
				sf::Color pixel = image.getPixel(x + relative.x, y + relative.y);
				copiedRect.setPixel(x, y, pixel);
			}
		}
		copiedRect.saveToFile("copy.png");
	}

	void pasteRect() {
		std::cout << "Pasting Rect" << std::endl;
		if (copiedRect.getSize().x < 0 || copiedRect.getSize().y < 0) { return; }
		std::cout << "Continue" << std::endl;

		sf::RenderTexture render;
		Position spritePos = getPosition();
		Position rectPos = rectangle.getPosition() - getPosition();

		
		render.create(getSize().x, getSize().y);

		sf::Texture texture;
		texture.loadFromImage(copiedRect);
		rectangle.setTexture(&texture);

		sprite.setPosition(0, 0);
		rectangle.setPosition(rectPos.x, rectPos.y);
		render.draw(sprite);
		render.draw(rectangle);
		render.display();

		image = render.getTexture().copyToImage();
		sprite.setPosition(spritePos.x, spritePos.y);
		rectangle.setPosition(rectPos.x, rectPos.y);
		rectangle.setFillColor(sf::Color::Transparent);
		copiedRect.create(0, 0);
		updateSprite();
	}

	void saveRect() {

		// The render goes crazy if we don't work from 0, 0 so we grab our interested positions and 
		// ..set the sprite to 0, 0 to avoid the shenanigans. Then after we draw, we set them back.i
		sf::RenderTexture render;
		Position spritePos = getPosition();
		Position rectPos = rectangle.getPosition() - getPosition();
		render.create(getSize().x, getSize().y);

		sprite.setPosition(0, 0);
		rectangle.setPosition(rectPos.x, rectPos.y);
		render.draw(sprite);
		render.draw(rectangle);
		render.display();
		
		image = render.getTexture().copyToImage();
		sprite.setPosition(spritePos.x, spritePos.y);
		rectangle.setPosition(rectPos.x, rectPos.y);
		rectangle.setFillColor(sf::Color::Transparent);
		updateSprite();
	}

	sf::Color getPixelColor() { 
		Position relative = Position(App::getMousePosition() - sf::Vector2i(getPosition()));
		return image.getPixel(relative.x, relative.y);
	}

	void loadImage(const std::string loadpath) {
		if (loadpath.empty()) { return; }
		if (!image.loadFromFile(loadpath)) { return; }
		updateSprite();
	}

	void saveImage(const std::string savepath) {
		if (savepath.empty()) { return; }
		if (!image.saveToFile(savepath)) { return;  }
		std::cout << "Saved as " << savepath << std::endl;
	}

	void setBrushSize(int size) { brushSize = size; }
	int getBrushSize() { return brushSize; }
	sf::Color getColor() { return currentColor; }
	
	virtual void setSize(Size size) { }
	virtual void setPosition(Position position) { }
	virtual Size getSize() { return Size(image.getSize()); }
	virtual Position getPosition() { return sprite.getPosition(); }
	void setOrigin() { 
		this->origin = Position(App::getMousePosition());
		rectangle.setPosition(origin);
	}
	Position getOrigin() { return origin; }
	Position getRelativeMousePosition() { return Position(App::getMousePosition() - sf::Vector2i(getPosition())); }

};
