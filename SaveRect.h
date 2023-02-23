// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "Callback.h"
#include "PixelCanvas.h"

class SaveRect : public Callback {

	PixelCanvas* pixelCanvas;

protected:

	virtual void onCalled() {
		pixelCanvas->saveRect();
	}

public:

	SaveRect(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
	}
};