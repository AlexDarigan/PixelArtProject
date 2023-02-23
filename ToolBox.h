// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "SetPixels.h"
#include "ErasePixels.h"
#include "SampleColor.h"
#include "SetOrigin.h"
#include "DrawRect.h"
#include "SaveRect.h"

class ToolBox {

	PixelCanvas* pixelCanvas;
	enum Tool;
	Tool selected = Tool::Cursor;
	const std::string ToolNames[7] = { 
		"Cursor", "PaintBrush", "Eraser", 
		"EyeDropper", "Picker", "Rectangle", "Max" };

	SetPixels* setPixels;
	ErasePixels* erasePixels;
	SampleColor* sampleColor;
	SetOrigin* setOrigin;
	DrawRect* drawRect;
	SaveRect* saveRect;


	void setMouseCursorIcon(Tool tool) {
		App::getInstance()->setCursor(getToolName(tool) + ".png");
	}

public:

	ToolBox(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
		setPixels = new SetPixels(pixelCanvas);
		erasePixels = new ErasePixels(pixelCanvas);
		sampleColor = new SampleColor(pixelCanvas);
		setOrigin = new SetOrigin(pixelCanvas);
		drawRect = new DrawRect(pixelCanvas);
		saveRect = new SaveRect(pixelCanvas);
	}

	const enum Tool { Cursor, PaintBrush, Eraser, EyeDropper, Picker, Rectangle, MAX, };

	Tool getTool() { return selected; }

	void setTool(Tool tool) {
		App::getInstance()->setMouseVisibility(false);
		std::cout << "Selecting tool: " << getToolName(tool) << std::endl;
		setMouseCursorIcon(tool);
		switch (tool) {
		case Cursor:
			pixelCanvas->setOnPressed(nullptr);
			pixelCanvas->setOnMouseDragged(nullptr);
			break;
		case PaintBrush:
			pixelCanvas->setOnPressed(setPixels);
			pixelCanvas->setOnMouseDragged(setPixels);
			break;
		case Eraser:
			pixelCanvas->setOnPressed(erasePixels);
			pixelCanvas->setOnMouseDragged(erasePixels);
			break;
		case EyeDropper:
			pixelCanvas->setOnPressed(sampleColor);
			pixelCanvas->setOnMouseDragged(nullptr);
			break;
		case Picker:
			pixelCanvas->setOnPressed(setOrigin);
			pixelCanvas->setOnMouseDragged(nullptr);
			break;
		case Rectangle:
			pixelCanvas->setOnPressed(setOrigin);
			pixelCanvas->setOnMouseDragged(drawRect);
			pixelCanvas->setOnMouseReleased(saveRect);
			break;
		case MAX:
			break;
		}
		selected = tool;
	}

	const std::string& getToolName(Tool tool) {
		return ToolNames[tool];
	}
};

