#pragma once
#include "Component.h"
#include <vector>

const double PI = 3.1415927;
class Switch : public Component
{
public:
	/* Functions */
	Switch(int _px, int _py, int _doorx, int _doory);
	void draw();
	void update();
	bool open = false;
private:
	double theta;
	double length;  // length of the handle
	double r;
	std::vector<int> color{ 0, 0, 0 };
};

