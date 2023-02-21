#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML.h"
#include "GameObject.h"
#include "ButtonFactory.h"
#include "GridFactory.h"

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

const sf::Color Grey(128, 128, 128, 255);

int main() {
	std::cout << "Hello World" << std::endl;

	// Background
	sf::RectangleShape background;
	background.setFillColor(Grey);
	background.setSize(sf::Vector2f(800, 600));

	// Factories
	ButtonFactory buttonFactory;
	GridFactory gridFactory;

	// SceneTree
	GameObject root;
	
	// Buttons
	Grid* buttons = gridFactory.getGrid(sf::Vector2f(8, 75), sf::Vector2f(50, 50), 8, 2, 4, 4);
	for (int i = 0; i < 16; i++) {
		buttons->addChild(buttonFactory.getButton(sf::Color::White, 0, 0, 0, 0));
	}

	Grid* swatches = gridFactory.getGrid(sf::Vector2f(642, 350), sf::Vector2f(50, 50), 3, 3, 4, 4);
	for (int i = 0; i < 9; i++) {
		swatches->addChild(buttonFactory.getButton(Colors[i], 0, 0, 0, 0));
	}

	Grid* pixels = gridFactory.getGrid(sf::Vector2f(190, 75), sf::Vector2f(50, 50), 8, 8, 0, 0);
	for (int i = 0; i < 64; i++) {
		pixels->addChild(buttonFactory.getButton(sf::Color::White, 0, 0, 0, 0));
	}

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