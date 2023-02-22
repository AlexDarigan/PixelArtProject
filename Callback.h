#pragma once
#include "SFML/Graphics.hpp"
#include "Color.h"

class Callback {

protected:

	virtual void onCalled() { std::cout << "Calling Base Callback" << std::endl; }

public:

	void call() { 
		if (this == nullptr) { return; }
		onCalled(); 
	}
};



class PaintTarget : public Callback {
	Color* swatchColor;
	Color* target;

protected:

	virtual void onCalled() {
		target->setColor(swatchColor->getColor());
	}

public:
	PaintTarget(Color* swatchColor, Color* target) {
		this->swatchColor = swatchColor;
		this->target = target;
	}

};