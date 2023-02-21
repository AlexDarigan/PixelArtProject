#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML.h"

class GameObject: public sf::Drawable {

	std::vector<GameObject*> children;

	void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		onDraw(window, states);
		for (const auto& child : children) { window.draw(*child); }
	}

protected: 

	virtual void onDraw(sf::RenderTarget& window, sf::RenderStates states) const {
		// To be overriden by children objects
	}

public:

	GameObject() {	}

	void addChild(GameObject* child) {
		children.push_back(child);
	}
};

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