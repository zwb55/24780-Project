/******************************************************
 * The class that represent the end point of a game.
 *****************************************************/

#pragma once
#include "Component.h"

class EndPoint: public Component {
public:

	/* Functions */
	EndPoint(int _px, int _py);
	int posZ = 100;
	void draw();
};