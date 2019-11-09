#include "EndPoint.h"
#include "DrawingUtilNG.h"
#include "fssimplewindow.h"

EndPoint::EndPoint(int _px, int _py): Component(_px, _py, true) {

}

void EndPoint::draw() {
	glColor3ub(229, 229, 237);
	DrawingUtilNG::drawCube(px * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH, 0, 
		(px + 1) * Component::PIXEL_LENGTH, (py + 1) * Component::PIXEL_LENGTH, -Component::PIXEL_LENGTH);

	glColor3ub(170, 174, 190);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);
	glBegin(GL_QUADS);
	int bound = Component::PIXEL_LENGTH * 0.1;

	int x1 = px * Component::PIXEL_LENGTH + bound;
	int x2 = (px + 1) * Component::PIXEL_LENGTH - bound;
	int y1 = py * Component::PIXEL_LENGTH + bound;
	int y2 = (py + 1) * Component::PIXEL_LENGTH - bound;

	glVertex3i(x1, y1, 0);
	glVertex3i(x2, y1, 0);
	glVertex3i(x2, y2, 0);
	glVertex3i(x1, y2, 0);

	glColor3ub(229, 229, 237);
	x1 += bound;
	x2 -= bound;
	y1 += bound;
	y2 -= bound;

	glVertex3i(x1, y1, 0);
	glVertex3i(x2, y1, 0);
	glVertex3i(x2, y2, 0);
	glVertex3i(x1, y2, 0);

	glEnd();
	
	glDisable(GL_POLYGON_OFFSET_FILL);
}