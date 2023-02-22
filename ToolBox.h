#pragma once
#include "SetPixels.h"
#include "ErasePixels.h"
#include "SampleColor.h"

class ToolBox {

	PixelCanvas* pixelCanvas;
	enum Tool;
	Tool selected = Tool::Cursor;
	const std::string ToolNames[6] = { "Cursor", "PaintBrush", "Eraser", "EyeDropper", "Picker", "Max" };

public:

	ToolBox(PixelCanvas* pixelCanvas) {
		this->pixelCanvas = pixelCanvas;
	}

	const enum Tool { Cursor, PaintBrush, Eraser, EyeDropper, Picker, MAX, };

	Tool getTool() { return selected; }

	void setTool(Tool tool) {
		std::cout << "Selecting tool: " << tool << std::endl;
		switch (tool) {
		case Cursor:
			break;
		case PaintBrush:
			pixelCanvas->setOnPressed(new SetPixels(pixelCanvas));
			pixelCanvas->setOnMouseDragged(new SetPixels(pixelCanvas));
			break;
		case Eraser:
			pixelCanvas->setOnPressed(new ErasePixels(pixelCanvas));
			pixelCanvas->setOnMouseDragged(new ErasePixels(pixelCanvas));
			break;
		case EyeDropper:
			pixelCanvas->setOnPressed(new SampleColor(pixelCanvas));
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

