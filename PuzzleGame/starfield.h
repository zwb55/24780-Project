#pragma once
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"

using namespace std;

class star {
private:
	float CX, CY, z;

public:
	void initialize(int width, int height);
	void draw();
	void move(int width, int height);
	bool out(int width, int height);

};