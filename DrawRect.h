// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "Callback.h"
#include "PixelCanvas.h"

class DrawRect : public Callback {

	PixelCanvas* pixelCanvas;
	bool filledRect;

protected:

	virtual void onCalled() {
		sf::Color fillColor = filledRect ? pixelCanvas->getColor() : sf::Color::Transparent;
		sf::Color outlineColor = filledRect ? sf::Color::Transparent : sf::Color::Black;
		pixelCanvas->drawRect(outlineColor, fillColor);
	}

public:

	DrawRect(PixelCanvas* pixelCanvas, bool filledRect) {
		this->pixelCanvas = pixelCanvas;
		this->filledRect = filledRect;
	}
};