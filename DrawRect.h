// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "Callback.h"
#include "PixelCanvas.h"

class DrawRect : public Callback {

	PixelCanvas* pixelCanvas;

protected:

	virtual void onCalled() {
		pixelCanvas->drawRect();
	}

public:

	DrawRect(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
	}
};