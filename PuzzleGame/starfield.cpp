#include <fstream>
#include <iostream>
#include <string>
#include "Starfield.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"

using namespace std;


void star::initialize(int width, int height) {
	CX = 1.0f * (rand() % width);
	CY = 1.0f * (rand() % height);
	z = 0.0001;
}
void star::draw() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	float radius = 0.05 + z;
	glColor3ub(255, 255, 255);
	DrawingUtilNG::drawCircle(CX, CY, radius, true);
}
void star::move(int width, int height) {
	z += 0.005;
	CX = (CX - (1.0f * width) / 2) * 1.009 + (1.0f * width) / 2;
	CY = (CY - (1.0f * height) / 2) * 1.009 + (1.0f * height) / 2;
}

bool star::out(int width, int height) {
	return CX<0 || CX>width || CY<0 || CY>height || z > 600;
}


