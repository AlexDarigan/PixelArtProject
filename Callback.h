#pragma once
#include "SFML/Graphics.hpp"
#include "Color.h"

class Callback {

protected:

	virtual void onCalled() { std::cout << "Calling Base Callback" << std::endl; }

public:

	void call() { 
		if (this == nullptr) { return; }
		onCalled(); 
	}
};

class ChangeColor : public Callback {
	Color* swatchColor;
	sf::Color color;

protected:

	virtual void onCalled() {
		std::cout << "Changing Color" << std::endl;
		swatchColor->setColor(color);
	}

public:

	ChangeColor(Color* swatchColor, sf::Color color) {
		this->swatchColor = swatchColor;
		this->color = color;
	}

};

class PaintTarget : public Callback {
	Color* swatchColor;
	Color* target;

protected:

	virtual void onCalled() {
		target->setColor(swatchColor->getColor());
	}

public:
	PaintTarget(Color* swatchColor, Color* target) {
		this->swatchColor = swatchColor;
		this->target = target;
	}

};