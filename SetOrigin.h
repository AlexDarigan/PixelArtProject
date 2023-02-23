// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "Callback.h"
#include "PixelCanvas.h"

class SetOrigin : public Callback {

	PixelCanvas* pixelCanvas;

protected:

	virtual void onCalled() {
		pixelCanvas->setOrigin();
	}

public:

	SetOrigin(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
	}
};