#pragma once
#include "SetPixels.h"
#include "ErasePixels.h"
#include "SampleColor.h"

class ToolBox {

	PixelCanvas* pixelCanvas;
	enum Tool;
	Tool selected = Tool::Cursor;
	const std::string ToolNames[6] = { "Cursor", "PaintBrush", "Eraser", "EyeDropper", "Picker", "Max" };

	SetPixels* setPixels;
	ErasePixels* erasePixels;
	SampleColor* sampleColor;

public:

	ToolBox(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
		setPixels = new SetPixels(pixelCanvas);
		erasePixels = new ErasePixels(pixelCanvas);
		sampleColor = new SampleColor(pixelCanvas);
	}

	const enum Tool { Cursor, PaintBrush, Eraser, EyeDropper, Picker, MAX, };

	Tool getTool() { return selected; }

	void setTool(Tool tool) {
		std::cout << "Selecting tool: " << tool << std::endl;
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

