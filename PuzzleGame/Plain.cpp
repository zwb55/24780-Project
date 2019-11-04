#include "Plain.h"
#include "fssimplewindow.h"

Plain::Plain(int _px, int _py): Component(_px, _py, true){}

void Plain::draw() {
	// draw a surface on XY plane
	glColor3ub(93, 290, 112);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);

	glBegin(GL_QUADS);
	
	int x1 = px * Component::PIXEL_LENGTH;
	int x2 = (px + 1) * Component::PIXEL_LENGTH;
	int y1 = py * Component::PIXEL_LENGTH;
	int y2 = (py + 1) * Component::PIXEL_LENGTH;

	glVertex3i(x1, y1, 0);
	glVertex3i(x2, y1, 0);
	glVertex3i(x2, y2, 0);
	glVertex3i(x1, y2, 0);

	glEnd();

	glDisable(GL_POLYGON_OFFSET_FILL);
}
