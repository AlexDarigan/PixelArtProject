// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "Callback.h"
#include "PixelCanvas.h"
#include "TextInput.h"

class LoadImage : public Callback {

	PixelCanvas* pixelCanvas;
	TextInput* textInput;

protected:

	virtual void onCalled() {
		pixelCanvas->loadImage(textInput->getText());
	}

public:

	LoadImage(PixelCanvas* pixelCanvas, TextInput* textInput) {
		this->pixelCanvas = pixelCanvas;
		this->textInput = textInput;
	}
};
