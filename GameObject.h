#pragma once
#include <SFML/Graphics.hpp>


class GameObject : public sf::Drawable {


	void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		onDraw(window, states);
		for (const auto& child : children) { window.draw(*child); }
	}

protected:

	std::vector<GameObject*> children;

	virtual void onDraw(sf::RenderTarget& window, sf::RenderStates states) const {
		// To be overriden by children objects
	}

	virtual void onChildAdded(GameObject* child) {

	}

	virtual void onEvent(sf::Event& event) {

	}


public:

	GameObject() {	}

	void addChild(GameObject* child) {
		children.push_back(child);
		onChildAdded(child);
	}

	void process(sf::Event &event) {
		onEvent(event);
		for (const auto& child : children) { child->process(event); }
	}

	virtual void setSize(sf::Vector2f size) {}
	virtual void setPosition(sf::Vector2f position) { }
	virtual sf::Vector2f getSize() { return sf::Vector2f(0, 0); }
	virtual sf::Vector2f getPosition() { return sf::Vector2f(0, 0); }
};