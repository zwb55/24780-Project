#include "Plain.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"

Plain::Plain(int _px, int _py): Component(_px, _py, true, 'p'){
	//// assign a random color to the plain (should be improved)
	//color[0] = DrawingUtilNG::getRandom(0, 255);
	//color[1] = DrawingUtilNG::getRandom(0, 255);
	//color[2] = DrawingUtilNG::getRandom(0, 255);

	color[0] = 0;
	color[1] = 153;
	color[2] = 0;
}

void Plain::update() {
	return;
}

void Plain::draw() {
	// draw dark green part
	glColor3ub(color[0], color[1], color[2]);
	DrawingUtilNG::drawCube(px* Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, 0, px * Component::PIXEL_LENGTH + 0.95*Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.95*Component::PIXEL_LENGTH, -5, false);

	// draw brown ground
	glColor3ub(153, 76, 0);
	DrawingUtilNG::drawCube(px * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, -5, px * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, -15, false);

	// draw light green surface
	glColor3ub(153, 255, 51);
	DrawingUtilNG::drawRectangle(px * Component::PIXEL_LENGTH + 0.1 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.1 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, true);
}
