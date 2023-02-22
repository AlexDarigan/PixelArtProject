// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include <iostream>
#include "Callback.h"
#include "PixelCanvas.h"

class ErasePixels : public Callback {

	PixelCanvas* pixelCanvas;

protected:

	virtual void onCalled() {
		pixelCanvas->erasePixels();
	}

public:

	ErasePixels(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
	}
};