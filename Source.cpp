// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML.h"
#include "GameObject.h"
#include "Button.h"
#include "Grid.h"
#include "Color.h"
#include "App.h"
#include "PixelCanvas.h"
#include "SetColor.h"
#include "ToolBox.h"
#include "SetTool.h"
#include "TextInput.h"
#include "SaveImage.h"
#include "LoadImage.h"

// Drawing a Rectangle
// Selection Tool
// Both use an "origin" point on pressed inside PixelCanvas
// PixelCanvas OnMouseDragged extends rectangle
// OnRelease - Rectangle is drawn
// OnRelease - Selection is copied (automatically)
// Use Ctrl+V check to copy from mouseLocation (paint pixels with an origin)

const sf::Color Cream(244, 244, 166);
const sf::Color Colors[9] = {
	sf::Color::Red, sf::Color::Blue, sf::Color::Green,
	sf::Color::Black, sf::Color::Cyan, sf::Color::Magenta,
	sf::Color::Yellow, sf::Color::White, Cream
};


Grid* createButtonOptions();
Grid* createColorPalette();
PixelCanvas* pixelCanvas = new PixelCanvas(180, 75, 400, 400);
ToolBox* toolBox = new ToolBox(pixelCanvas);

int main() {


	auto app = App::getInstance();
	auto root = app->getRoot();
	auto buttons = createButtonOptions();
	auto swatches = createColorPalette();

	// Getting tired
	sf::Font font;
	font.loadFromFile("arial.ttf");
	auto textInput = new TextInput(Size(400, 50), Position(180, 480));
	auto saveButton = new Button(sf::Color(128, 128, 128), 180, 540, 190, 50);
	auto loadButton = new Button(sf::Color(128, 128, 128), 385, 540, 195, 50);
	saveButton->setText(sf::Text("Save", font, 32));
	loadButton->setText(sf::Text("Load", font, 32));

	root->addChild(buttons);
	root->addChild(pixelCanvas);
	root->addChild(swatches);

	root->addChild(textInput);
	textInput->addChild(saveButton);
	textInput->addChild(loadButton);

	// Updating for text
	saveButton->setPosition(saveButton->getPosition());
	loadButton->setPosition(loadButton->getPosition());
	saveButton->setOnPressed(new SaveImage(pixelCanvas, textInput));
	loadButton->setOnPressed(new LoadImage(pixelCanvas, textInput));

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
	auto buttons = new Grid(sf::Vector2f(8, 75), sf::Vector2f(64, 64), ToolBox::Tool::MAX / 2, 2, 4, 4);
	for (int i = 0; i < ToolBox::Tool::MAX; i++) {
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
