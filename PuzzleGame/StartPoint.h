/******************************************************
 * The class that represent the start point of a game.
 *****************************************************/

#pragma once
#include "Component.h"

class StartPoint: public Component {
public:

	/* Functions */
	StartPoint(int _px, int _py);
	int posZ = 0;
	void draw();
	void update();
};
