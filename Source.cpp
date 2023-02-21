#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML.h"
#include "GameObject.h"
#include "ButtonFactory.h"

int main() {
	std::cout << "Hello World" << std::endl;

	// Factories
	ButtonFactory buttonFactory;

	// SceneTree
	GameObject root;
	GameObject child;
	Button* button = buttonFactory.getButton(sf::Color::Green, 50, 50, 100, 200);
	root.addChild(&child);
	child.addChild(button);

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