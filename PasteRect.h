// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "Callback.h"
#include "PixelCanvas.h"

class PasteRect : public Callback {

	PixelCanvas* pixelCanvas;

protected:

	virtual void onCalled() { pixelCanvas->pasteRect(); }

public:

	PasteRect(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
	}
};