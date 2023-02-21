#pragma once
#include "SFML/Graphics.hpp"
#include "SwatchColor.h"

class Callback {

protected:

	virtual void onCalled() {
		std::cout << "Calling Base Callback" << std::endl;
	}

public:

	void call() {
		this->onCalled();
	}
};

class ChangeColor : public Callback {
	static ChangeColor changeColors[100];
	static int count;
	SwatchColor* swatchColor;
	sf::Color color;

protected:

	virtual void onCalled() {
		std::cout << "Calling Derived Callback" << std::endl;
		swatchColor->setColor(color);
		std::cout << "set color of swatch";
	}

public:
	ChangeColor() {}

	ChangeColor(SwatchColor* swatchColor, sf::Color color) {
		this->swatchColor = swatchColor;
		this->color = color;
	}

	static ChangeColor* getChangeColorCallback(SwatchColor* swatchColor, sf::Color color);
};

ChangeColor* ChangeColor::getChangeColorCallback(SwatchColor* swatchColor, sf::Color color) {
	ChangeColor changeColorCallback(swatchColor, color);
	changeColors[count] = changeColorCallback;
	count++;
	return (ChangeColor*)&changeColors[count - 1];
}

int ChangeColor::count = 0;
ChangeColor ChangeColor::changeColors[100] = {};
