#pragma once
#include "Button.h"

// Using Factories as a way to give objects an 'Owner'
class ButtonFactory {

	Button buttons[100];
	int count = 0;

public:
	
	Button* getButton(sf::Color color, float x = 0, float y = 0, float width = 50, float height = 50) {
		Button button(color, x, y, width, height);
		buttons[count] = button;
		count++;
		return &buttons[count - 1];
	}
};