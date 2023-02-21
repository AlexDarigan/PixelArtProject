#pragma once
#include <SFML/Graphics.hpp>


class GameObject : public sf::Drawable {

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