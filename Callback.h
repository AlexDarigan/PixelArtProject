#pragma once
#include "SFML/Graphics.hpp"
#include "SwatchColor.h"

class Callback {

protected:

	virtual void onCalled() {
		std::cout << "Calling Base Callback" << std::endl;
	}

public:

	void call() { onCalled(); }
};

class ChangeColor : public Callback {
	static ChangeColor changeColors[100];
	static int count;
	SwatchColor* swatchColor;
	sf::Color color;

protected:

	virtual void onCalled() {
		std::cout << "Setting Color" << std::endl;
		swatchColor->setColor(color);
	}

public:
	static ChangeColor* create(SwatchColor* swatchColor, sf::Color color);
};


int ChangeColor::count = 0;
ChangeColor ChangeColor::changeColors[100] = {};
ChangeColor* ChangeColor::create(SwatchColor* swatchColor, sf::Color color) {
	ChangeColor changeColorCallback;
	changeColorCallback.swatchColor = swatchColor;
	changeColorCallback.color = color;
	changeColors[count] = changeColorCallback;
	count++;
	return (ChangeColor*)&changeColors[count - 1];
}

