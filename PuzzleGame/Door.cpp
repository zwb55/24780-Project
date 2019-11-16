#include "Door.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"

Door::Door(int _px, int _py): Component(_px, _py, false, 'd'){
	// assign a random color to the plain (should be improved)
	color[0] = 200;
	color[1] = 200;
	color[2] = 200;
	state = true;
}

void Door::setPosition(int _px, int _py) {
	px = _px;
	py = _py;
}

void Door::update() {
	state = !state;
	canLand = !canLand;
}

void Door::draw() {
	glColor3b(100, 100, 100);
	if (state)
	{
		height += 1;
		if (height >= Component::PIXEL_LENGTH * 2.)
			height = Component::PIXEL_LENGTH * 2.;
		DrawingUtilNG::drawCube(px * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH, 0, (px + 1) * Component::PIXEL_LENGTH, (py + 1) * Component::PIXEL_LENGTH, height, false);

	}
	else
	{
		height -= 1;
		if (height <= 0)
			height = 0;
		DrawingUtilNG::drawCube(px * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH, 0, (px + 1) * Component::PIXEL_LENGTH, (py + 1) * Component::PIXEL_LENGTH, height, false);

	}
	// draw dark green part
	glColor3ub(color[0], color[1], color[2]);
	DrawingUtilNG::drawCube(px * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, 0, px * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, -5, false);

	// draw brown ground
	glColor3ub(153, 76, 0);
	DrawingUtilNG::drawCube(px * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, -5, px * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, -15, false);

	// draw light green surface
	glColor3ub(153, 255, 51);
	DrawingUtilNG::drawRectangle(px * Component::PIXEL_LENGTH + 0.1 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.1 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, true);

}
