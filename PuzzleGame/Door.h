/*****************************************************
 * The class defines a door which opens when a button
 * is pressed
 *****************************************************/

#pragma once
#include "Component.h"
#include <vector>

class Door : public Component {
public:
	
	/* Functions */
	Door(int _px, int _py);
	void setPosition(int _px, int _py);
	void draw();
	void update();
	int height = Component::PIXEL_LENGTH*2.;
	
private:
	friend class Button;
	/* Member fields */
	std::vector<int> color{0, 0, 0};
};
