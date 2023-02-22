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
#include "SetColor.h"
#include "SetPixels.h"
#include "ToolBox.h"
#include "SetTool.h"

const sf::Color Cream(244, 244, 166);
const sf::Color Colors[9] = {
	sf::Color::Red, sf::Color::Blue, sf::Color::Green,
	sf::Color::Black, sf::Color::Cyan, sf::Color::Magenta,
	sf::Color::Yellow, sf::Color::White, Cream
};


Grid* createButtonOptions();
Grid* createColorPalette();

ToolBox* toolBox = new ToolBox();
PixelCanvas* pixelCanvas = new PixelCanvas(180, 75, 400, 400);

int main() {
	std::cout << "Hello World" << std::endl;
	
	auto app = App::getInstance();
	
	// SceneTree
	auto root = app->getRoot();
	auto buttons = createButtonOptions();
	auto swatches = createColorPalette();
	
	auto setPixels = new SetPixels(pixelCanvas);
	pixelCanvas->setOnMouseDragged(setPixels);
	pixelCanvas->setOnPressed(setPixels);

	root->addChild(buttons);
	root->addChild(pixelCanvas);
	root->addChild(swatches);

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time delta = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();

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
	auto buttons = new Grid(sf::Vector2f(8, 75), sf::Vector2f(64, 64), 5, 2, 4, 4);
	for (int i = 1; i < ToolBox::Tool::MAX; i++) {
		auto button = new Button();
		auto selectTool = new SetTool(toolBox, ToolBox::Tool(i));
		button->setImage(toolBox->getToolName(ToolBox::Tool(i)) + ".png");
		button->setOnPressed(selectTool);
		buttons->addChild(button);
	}

	return buttons;
}

Grid* createColorPalette() {
	auto swatches = new Grid(sf::Vector2f(632, 350), sf::Vector2f(50, 50), 3, 3, 4, 4);
	for (int i = 0; i < 9; i++) {
		auto button = new Button(Colors[i], 0, 0, 0, 0);
		auto callback = new SetColor(pixelCanvas, Colors[i]);
		button->setOnPressed(callback);
		swatches->addChild(button);
	}
	return swatches;
}
