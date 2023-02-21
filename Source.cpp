#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML.h"
#include "GameObject.h"
#include "Button.h"
#include "Grid.h"
#include "Callback.h"
#include "Color.h"
#include "App.h"

// TODO:
// Create a ToolClass (which can have its own dedicated callbacks?)
//	e.g PaintTool()
//  if(selected) PaintTarget.call()?
// Maybe PaintTarget.call(), if(painttool != selected) { return; }
// PaintTarget(Tool, Target, Color)

const sf::Color Cream(244, 244, 166);
const sf::Color Colors[9] = {
	sf::Color::Red, sf::Color::Blue, sf::Color::Green,
	sf::Color::Black, sf::Color::Cyan, sf::Color::Magenta,
	sf::Color::Yellow, sf::Color::White, Cream
};

Color swatchColor;

Grid* createButtonOptions();
Grid* createDrawingGrid();
Grid* createColorPalette();

class RenderObject : public GameObject {

	sf::RectangleShape shape;
	sf::Sprite sprite;
	sf::Image texture;
	sf::Texture tex;

protected:

	virtual void onDraw(sf::RenderTarget& window, sf::RenderStates states) const {
		// To be overriden by children objects
		
		window.draw(sprite, states);
	}

public:

	RenderObject() {
		texture.create(400, 400);
		shape.setScale(sf::Vector2f(50, 50));
		shape.setPosition(sf::Vector2f(50, 50));

		for (int x = 0; x < 400; x++) {
			for (int y = 0; y < 400; y++) {
				texture.setPixel(x, y, sf::Color(x, y, 0, 150));
			}
		}
		
		tex.loadFromImage(texture);
		sprite.setTexture(tex);
		//sprite.setI
	}

};

int main() {
	std::cout << "Hello World" << std::endl;
	
	App* app = App::getInstance();
	
	// SceneTree
	GameObject* root = app->getRoot();
	Grid* buttons = createButtonOptions();
	Grid* pixels = createDrawingGrid();
	Grid* swatches = createColorPalette();
	
	

	root->addChild(buttons);
	root->addChild(pixels);
	root->addChild(swatches);

	// Texture - Saving/Loading
	// Use this for our pixels thing, add setPixelCallBack
	RenderObject obj;
	root->addChild(&obj);

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time delta = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();

	// Attempt Creating RenderTexture
	

	while (app->isOpen()) {
		sf::Event event;
		while (app->poll(event)) {
			if (event.type == sf::Event::Closed) { app->close(); }
			app->process(event);
		}
		delta += clock.restart();
		if (delta > timePerFrame) {

			app->redraw();
		}
	}
}

Grid* createButtonOptions() {
	Grid* buttons = Grid::create(sf::Vector2f(8, 75), sf::Vector2f(50, 50), 8, 2, 4, 4);
	for (int i = 0; i < 16; i++) {
		buttons->addChild(Button::create(sf::Color::White, 0, 0, 0, 0));
	}
	return buttons;
}

Grid* createDrawingGrid() {
	Grid* pixels = Grid::create(sf::Vector2f(190, 75), sf::Vector2f(50, 50), 8, 8, 0, 0);
	for (int i = 0; i < 64; i++) {
		Button* button = Button::create(sf::Color::White, 0, 0, 0, 0);
		PaintTarget* paintTarget = PaintTarget::create(&swatchColor, button);
		button->setCallback(paintTarget);
		pixels->addChild(button);
	}
	return pixels;
}

Grid* createColorPalette() {
	Grid* swatches = Grid::create(sf::Vector2f(632, 350), sf::Vector2f(50, 50), 3, 3, 4, 4);
	for (int i = 0; i < 9; i++) {
		Button* button = Button::create(Colors[i], 0, 0, 0, 0);
		ChangeColor* callback = ChangeColor::create(&swatchColor, Colors[i]);
		button->setCallback(callback);
		swatches->addChild(button);
	}
	return swatches;
}