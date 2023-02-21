#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML.h"

int main() {
	std::cout << "Hello World" << std::endl;

	sf::RenderWindow Window(sf::VideoMode(800, 600), "Project");
	while (Window.isOpen()) {
		sf::Event event;
		Window.pollEvent(event);
		if (event.type == sf::Event::Closed) {
			Window.close();
		}
		Window.clear();
		Window.display();
	}
}