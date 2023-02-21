#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML.h"
#include "GameObject.h"


int main() {
	std::cout << "Hello World" << std::endl;

	GameObject root;
	GameObject child;
	root.addChild(&child);

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