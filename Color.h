// Student Name	: David Darigan
// Student ID	: C00263218

#pragma once
#include "SFML/Graphics.hpp"

class Color {

	sf::Color color = sf::Color::White;

public:

	virtual void setColor(sf::Color color) { this->color = color; }
	virtual sf::Color getColor() { return color; }
};
