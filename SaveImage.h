// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "Callback.h"
#include "PixelCanvas.h"
#include "TextInput.h"

class SaveImage: public Callback {

	PixelCanvas* pixelCanvas;
	TextInput* textInput;

protected:

	virtual void onCalled() { 
		pixelCanvas->saveImage(textInput->getText());
	}

public:

	SaveImage(PixelCanvas* pixelCanvas, TextInput* textInput) {
		this->pixelCanvas = pixelCanvas;
		this->textInput = textInput;
	}
};
