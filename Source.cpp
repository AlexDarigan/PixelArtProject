#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML.h"
#include "GameObject.h"
#include "Button.h"
#include "Grid.h"
#include "Callback.h"

const sf::Color Cream(244, 244, 166);
const sf::Color Colors[9] = {
	sf::Color::Red,
	sf::Color::Blue,
	sf::Color::Green,
	sf::Color::Black,
	sf::Color::Cyan,
	sf::Color::Magenta,
	sf::Color::Yellow,
	sf::Color::White,
	Cream
};

SwatchColor swatchColor;

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
		pixels->addChild(Button::create(sf::Color::White, 0, 0, 0, 0));
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

int main() {
	std::cout << "Hello World" << std::endl;
	// Background
	sf::RectangleShape background;
	background.setFillColor(sf::Color(211, 211, 211));
	background.setSize(sf::Vector2f(800, 600));

	// SceneTree
	GameObject root;
	Grid* buttons = createButtonOptions();
	Grid* pixels = createDrawingGrid();
	Grid* swatches = createColorPalette();
	
	root.addChild(buttons);
	root.addChild(pixels);
	root.addChild(swatches);

	// Window
	sf::RenderWindow Window(sf::VideoMode(800, 600), "Project");
	while (Window.isOpen()) {
		sf::Event event;
		while (Window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { Window.close(); }
			root.process(event);
		}

		Window.clear();
		Window.draw(background);
		Window.draw(root);
		Window.display();
	}
}