#pragma once

class ToolBox {

	enum Tool;
	Tool selected = Tool::Cursor;
	const std::string ToolNames[6] = { "Cursor", "PaintBrush", "Eraser", "EyeDropper", "Picker", "Max" };

public:

	const enum Tool { Cursor, PaintBrush, Eraser, EyeDropper, Picker, MAX, };

	Tool getTool() { return selected; }

	void setTool(Tool tool) {
		std::cout << "Selecting tool: " << tool << std::endl;
		selected = tool;
	}

	const std::string& getToolName(Tool tool) {
		return ToolNames[tool];
	}
};

