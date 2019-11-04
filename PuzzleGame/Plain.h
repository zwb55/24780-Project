/******************************************************
 * The class that represent a plain with nothing on it and can be landed by player.
 *****************************************************/

#pragma once
#include "Component.h"

class Plain : public Component {
public:

	/*
	 * Functions
	 */
	Plain(int _px, int _py);
	void draw();
};
