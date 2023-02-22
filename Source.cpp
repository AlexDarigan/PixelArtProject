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
#include "PixelCanvas.h"

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

class setPixel: public Callback { };
class getPixel : public Callback { } ;
class Tool { };
class PaintBrush : Tool {};
class EyeDropper : Tool {};
class Eraser : Tool {};
class Picker : Tool {};

using Size = sf::Vector2f;
using Position = sf::Vector2f;

int main() {
	std::cout << "Hello World" << std::endl;
	
	App* app = App::getInstance();
	
	// SceneTree
	GameObject* root = app->getRoot();
	Grid* buttons = createButtonOptions();
	Grid* pixels = createDrawingGrid();
	Grid* swatches = createColorPalette();
	
	PixelCanvas* canvas = new PixelCanvas(180, 75, 400, 400);
	

	root->addChild(buttons);
	root->addChild(canvas);
	root->addChild(swatches);

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
	Grid* buttons = new Grid(sf::Vector2f(8, 75), sf::Vector2f(50, 50), 8, 2, 4, 4);
	for (int i = 0; i < 16; i++) {
		buttons->addChild(new Button(sf::Color::White, 0, 0, 0, 0));
	}
	return buttons;
}

Grid* createDrawingGrid() {
	Grid* pixels = new Grid(sf::Vector2f(190, 75), sf::Vector2f(50, 50), 8, 8, 0, 0);
	for (int i = 0; i < 64; i++) {
		Button* button = new Button(sf::Color::White, 0, 0, 0, 0);
		PaintTarget* paintTarget = new PaintTarget(&swatchColor, button);
		button->setCallback(paintTarget);
		pixels->addChild(button);
	}
	return pixels;
}

Grid* createColorPalette() {
	Grid* swatches = new Grid(sf::Vector2f(632, 350), sf::Vector2f(50, 50), 3, 3, 4, 4);
	for (int i = 0; i < 9; i++) {
		Button* button = new Button(Colors[i], 0, 0, 0, 0);
		ChangeColor* callback = new ChangeColor(&swatchColor, Colors[i]);
		button->setCallback(callback);
		swatches->addChild(button);
	}
	return swatches;
}