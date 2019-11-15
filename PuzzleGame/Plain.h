/******************************************************
 * The class that represent a plain with nothing on it and can be landed by player.
 *****************************************************/

#pragma once
#include "Component.h"
#include <vector>

class Plain : public Component {
public:

	/* Functions */
	Plain(int _px, int _py);
	void draw();
	void update();

private:
	/* Member fields */
	std::vector<int> color{0, 0, 0};
};
