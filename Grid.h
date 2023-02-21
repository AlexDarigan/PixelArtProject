#pragma once
#include "GameObject.h"

class Grid : public GameObject {

	int rows = 0;
	int cols = 0;
	int h_gap = 0;
	int v_gap = 0;
	int row = 0;
	int col = 0;
	sf::Vector2f position;
	sf::Vector2f cellSize;

	sf::Vector2f getNextCell() { return sf::Vector2f(getX(), getY()); }
	float getX() { return getPosition().x + (cellSize.x + h_gap) * col; }
	float getY() { return getPosition().y + (cellSize.y + v_gap) * row; }
	void updateRowsAndColumns() {
		col++;
		if (col >= cols) {
			row++;
			col = 0;
		}
	}

protected:

	void onChildAdded(GameObject* child) {
		child->setSize(cellSize);
		child->setPosition(getNextCell());
		updateRowsAndColumns();
	}

public:

	Grid() {}

	Grid(sf::Vector2f position, sf::Vector2f cellSize, int rows, int cols, int h_gap = 0, int v_gap = 0) {
		this->position = position;
		this->cellSize = cellSize;
		this->rows = rows;
		this->cols = cols;
		this->h_gap = h_gap;
		this->v_gap = v_gap;
	}

	virtual void setPosition(sf::Vector2f position) { this->position = position; }
	virtual sf::Vector2f getPosition() { return position; }

};