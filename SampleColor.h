#pragma once
#include <iostream>
#include "Callback.h"
#include "PixelCanvas.h"

class SampleColor: public Callback {

	PixelCanvas* pixelCanvas;
	sf::Color color;

protected:

	virtual void onCalled() {
		std::cout << "Sampling Color" << std::endl;
		pixelCanvas->setColor(pixelCanvas->getPixelColor());
	}

public:

	SampleColor(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
	}
};