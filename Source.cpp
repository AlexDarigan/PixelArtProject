#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML.h"
#include "GameObject.h"
#include "ButtonFactory.h"
#include "GridFactory.h"

int main() {
	std::cout << "Hello World" << std::endl;

	// Factories
	ButtonFactory buttonFactory;
	GridFactory gridFactory;

	// SceneTree
	GameObject root;
	GameObject child;
	Button* button = buttonFactory.getButton(sf::Color::Green, 50, 50, 100, 200);
	root.addChild(&child);
	child.addChild(button);

	Grid* grid = gridFactory.getGrid(sf::Vector2f(500, 200), sf::Vector2f(50, 50), 3, 3, 4, 4);
	for (int i = 0; i < 9; i++) {
		grid->addChild(buttonFactory.getButton(sf::Color::Blue, 200, 200, 50, 50));
	}

	button->addChild(grid);

	// Window
	sf::RenderWindow Window(sf::VideoMode(800, 600), "Project");
	while (Window.isOpen()) {
		sf::Event event;
		Window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			Window.close();
		}
		Window.clear();
		Window.draw(root);
		Window.display();
	}
}