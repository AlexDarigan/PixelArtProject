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

// TODO:
// Create a ToolClass (which can have its own dedicated callbacks?)
//	e.g PaintTool()
//  if(selected) PaintTarget.call()?
// Maybe PaintTarget.call(), if(painttool != selected) { return; }
// PaintTarget(Tool, Target, Color)

class ToolBox {

	enum Tool;
	Tool selected = Tool::None;

public:

	const enum Tool {
		None, 
		PaintBrush,
		Eraser,
		EyeDropper,
		Picker,
		MAX,
	};

	Tool getSelected() { return selected; }
	void select(Tool tool) { 
		std::cout << "Selecting tool: " << tool << std::endl;
		selected = tool; 
	}
};

class SelectTool : public Callback {

	ToolBox* toolBox;
	ToolBox::Tool tool;

	protected:

		virtual void onCalled() { toolBox->select(tool); }

	public:

		SelectTool(ToolBox* toolBox, ToolBox::Tool tool) {
			this->toolBox = toolBox;
			this->tool = tool;
		}
};

const sf::Color Cream(244, 244, 166);
const sf::Color Colors[9] = {
	sf::Color::Red, sf::Color::Blue, sf::Color::Green,
	sf::Color::Black, sf::Color::Cyan, sf::Color::Magenta,
	sf::Color::Yellow, sf::Color::White, Cream
};

Color swatchColor;

Grid* createButtonOptions();
Grid* createColorPalette();

class Tool { };
class PaintBrush : Tool {};
class EyeDropper : Tool {};
class Eraser : Tool {};
class Picker : Tool {};

ToolBox* toolBox = new ToolBox();
PixelCanvas* pixelCanvas = new PixelCanvas(180, 75, 400, 400);

int main() {
	std::cout << "Hello World" << std::endl;
	
	App* app = App::getInstance();
	
	// SceneTree
	GameObject* root = app->getRoot();
	Grid* buttons = createButtonOptions();
	Grid* swatches = createColorPalette();
	
	SetPixels* setPixels = new SetPixels(pixelCanvas);
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
	Grid* buttons = new Grid(sf::Vector2f(8, 75), sf::Vector2f(64, 64), 5, 2, 4, 4);
	for (int i = 1; i < ToolBox::Tool::MAX; i++) {
		Button* button = new Button();
		button->setImage("PaintBrush.png");
		SelectTool* selectTool = new SelectTool(toolBox, ToolBox::Tool(i));
		button->setOnPressed(selectTool);
		buttons->addChild(button);
	}

	return buttons;
}

Grid* createColorPalette() {
	Grid* swatches = new Grid(sf::Vector2f(632, 350), sf::Vector2f(50, 50), 3, 3, 4, 4);
	for (int i = 0; i < 9; i++) {
		Button* button = new Button(Colors[i], 0, 0, 0, 0);
		SetColor* callback = new SetColor(pixelCanvas, Colors[i]);
		button->setOnPressed(callback);
		swatches->addChild(button);
	}
	return swatches;
}
