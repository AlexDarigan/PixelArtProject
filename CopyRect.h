// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "Callback.h"
#include "PixelCanvas.h"

class CopyRect : public Callback {

	PixelCanvas* pixelCanvas;

protected:

	virtual void onCalled() { pixelCanvas->copyRect(); }

public:

	CopyRect(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
	}
};