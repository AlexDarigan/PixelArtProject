#pragma once
#include <SFML/Graphics.hpp>

using Size = sf::Vector2f;
using Position = sf::Vector2f;

class GameObject : public sf::Drawable {

	void draw(sf::RenderTarget& window, sf::RenderStates states) const {
		onDraw(window, states);
		for (const auto& child : children) { window.draw(*child); }
	}

protected:

	std::vector<GameObject*> children;
	virtual void onDraw(sf::RenderTarget& window, sf::RenderStates states) const { }
	virtual void onChildAdded(GameObject* child) { }
	virtual void onEvent(sf::Event& event) { }

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

	virtual void setSize(Size size) { }
	virtual void setPosition(Position position) { }
	virtual Size getSize() { return Size(0, 0); }
	virtual Position getPosition() { return Position(0, 0); }
};