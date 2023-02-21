#pragma once
#include "Grid.h"

class GridFactory {

	Grid grids[100];
	int count = 0;

public:

	Grid* getGrid(sf::Vector2f position, sf::Vector2f cellSize, int rows, int cols, int h_gap = 0, int v_gap = 0) {
		Grid grid(position, cellSize, rows, cols, h_gap, v_gap);
		grids[count] = grid;
		count++;
		return &grids[count - 1];
	}
};