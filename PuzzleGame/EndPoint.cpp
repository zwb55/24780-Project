#include "EndPoint.h"
#include "DrawingUtilNG.h"
#include "fssimplewindow.h"

EndPoint::EndPoint(int _px, int _py): Component(_px, _py, true) {

}

void EndPoint::draw() {
	// draw dark green part
	glColor3ub(153, 153, 0);
	DrawingUtilNG::drawCube(px * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, 0, px * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, -5, false);

	// draw brown ground
	glColor3ub(153, 76, 0);
	DrawingUtilNG::drawCube(px * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, -5, px * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, -15, false);

	// draw light green surface
	glColor3ub(255, 255, 0);
	DrawingUtilNG::drawRectangle(px * Component::PIXEL_LENGTH + 0.1 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.1 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, true);

	// draw circles

	int pos = posZ;
	glColor3ub(102, 0, 102);
	DrawingUtilNG::drawCircle((px + 0.5) * Component::PIXEL_LENGTH, (px + 0.5) * Component::PIXEL_LENGTH, 0.01 * pos * Component::PIXEL_LENGTH - 10, Component::PIXEL_LENGTH / 3., true);
	glColor3ub(153, 0, 153);
	DrawingUtilNG::drawCircle((px + 0.5) * Component::PIXEL_LENGTH, (px + 0.5) * Component::PIXEL_LENGTH, 0.01 * pos * Component::PIXEL_LENGTH - 5, Component::PIXEL_LENGTH / 3.5, true);
	glColor3ub(204, 0, 204);
	DrawingUtilNG::drawCircle((px + 0.5) * Component::PIXEL_LENGTH, (px + 0.5) * Component::PIXEL_LENGTH, 0.01 * pos * Component::PIXEL_LENGTH, Component::PIXEL_LENGTH / 4., true);
	posZ--;
	if (posZ == 0)
		posZ = 100;
}