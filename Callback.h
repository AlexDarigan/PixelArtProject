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

class ChangeColor : public Callback {
	static ChangeColor changeColors[100];
	static int count;
	Color* swatchColor;
	sf::Color color;

protected:

	virtual void onCalled() {
		swatchColor->setColor(color);
	}

public:
	static ChangeColor* create(Color* swatchColor, sf::Color color);
};


int ChangeColor::count = 0;
ChangeColor ChangeColor::changeColors[100] = {};
ChangeColor* ChangeColor::create(Color* swatchColor, sf::Color color) {
	ChangeColor changeColorCallback;
	changeColorCallback.swatchColor = swatchColor;
	changeColorCallback.color = color;
	changeColors[count] = changeColorCallback;
	count++;
	return (ChangeColor*)&changeColors[count - 1];
}

class PaintTarget : public Callback {
	static PaintTarget paintTargets[100];
	static int count;
	Color* swatchColor;
	Color* target;

protected:

	virtual void onCalled() {
		target->setColor(swatchColor->getColor());
	}

public:
	static PaintTarget* create(Color* swatchColor, Color* target);
};


int PaintTarget::count = 0;
PaintTarget PaintTarget::paintTargets[100] = {};
PaintTarget* PaintTarget::create(Color* swatchColor, Color* target) {
	PaintTarget paintTarget;
	paintTarget.swatchColor = swatchColor;
	paintTarget.target = target;
	paintTargets[count] = paintTarget;
	count++;
	return (PaintTarget*)&paintTargets[count - 1];
}

