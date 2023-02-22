#pragma once
#include <iostream>
#include "Callback.h"
#include "PixelCanvas.h"

class SetColor : public Callback {

	PixelCanvas* pixelCanvas;
	sf::Color color;

protected:

	virtual void onCalled() {
		std::cout << "Changing Color" << std::endl;
		pixelCanvas->setColor(color);
	}

public:

	SetColor(PixelCanvas* pixelCanvas, sf::Color color) {
		this->pixelCanvas = pixelCanvas;
		this->color = color;
	}
};