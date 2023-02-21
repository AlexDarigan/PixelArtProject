#pragma once
#include "SFML/Graphics.hpp"


class SwatchColor {

	sf::Color color = sf::Color::White;

public:

	void setColor(sf::Color color) { this->color = color; }
	sf::Color getColor() { return color; }
};
