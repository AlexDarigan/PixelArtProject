// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "Callback.h"
#include "ToolBox.h"

class SetTool : public Callback {

	ToolBox* toolBox;
	ToolBox::Tool tool;

protected:

	virtual void onCalled() { toolBox->setTool(tool); }

public:

	SetTool(ToolBox* toolBox, ToolBox::Tool tool) {
		this->toolBox = toolBox;
		this->tool = tool;
	}
};