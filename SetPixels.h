#pragma once
#include <iostream>
#include "Callback.h"
#include "PixelCanvas.h"

class SetPixels : public Callback {

	PixelCanvas* pixelCanvas;

protected:

	virtual void onCalled() {
		pixelCanvas->setPixels();
	}

public:

	SetPixels(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
	}
};