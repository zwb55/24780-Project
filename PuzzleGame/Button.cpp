#include "Button.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"
#include "Plain.h"

Button::Button(int _px, int _py, int _doorx, int _doory): Component(_px, _py, true, 'b') {
    // assign a random color to the plain (should be improved)
	color[0] = DrawingUtilNG::getRandom(0, 255);
    color[1] = DrawingUtilNG::getRandom(0, 255);
    color[2] = DrawingUtilNG::getRandom(0, 255);
	corrCompLoc[0] = _doorx;
	corrCompLoc[1] = _doory;
	state = true;
}

void Button::update() {
	state = !state;
}

void Button::draw() {
	glColor3ub(153, 0, 0);
	if (state)
	{
		height += 1;
		if (height >= Component::PIXEL_LENGTH * 0.3)
			height = Component::PIXEL_LENGTH * 0.3;
		DrawingUtilNG::drawCube((px+0.2) * Component::PIXEL_LENGTH, (py+0.2) * Component::PIXEL_LENGTH, 0, (px + 0.8) * Component::PIXEL_LENGTH, (py + 0.8) * Component::PIXEL_LENGTH, height, false);

	}
	else
	{
		height -= 1;
		if (height <= 0)
			height = 0;
		DrawingUtilNG::drawCube((px + 0.2) * Component::PIXEL_LENGTH, (py + 0.2) * Component::PIXEL_LENGTH, 0, (px + 0.8) * Component::PIXEL_LENGTH, (py + 0.8) * Component::PIXEL_LENGTH, height, false);

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
