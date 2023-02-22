// Student Name	: David Darigan
// Student ID	: C00263218

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



