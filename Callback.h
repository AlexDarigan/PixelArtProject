#pragma once
#include "SFML/Graphics.hpp"
#include "Color.h"
#include "PixelCanvas.h"

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

	PixelCanvas* pixelCanvas;
	sf::Color color;

protected:

	virtual void onCalled() {
		std::cout << "Changing Color" << std::endl;
		pixelCanvas->setColor(color);
	}

public:

	ChangeColor(PixelCanvas* pixelCanvas, sf::Color color) {
		this->pixelCanvas = pixelCanvas;
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