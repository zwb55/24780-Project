#include "Door.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"

Door::Door(int _px, int _py): Component(_px, _py, false, 'd'){
	// assign a random color to the plain (should be improved)
	color[0] = 200;
	color[1] = 200;
	color[2] = 200;
	state = false;
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
	// draw a surface on XY plane
	color[0] = 0;
	color[1] = 153;
	color[2] = 0;
	glColor3ub(color[0], color[1], color[2]);
	DrawingUtilNG::drawCube(px* Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, 0, px * Component::PIXEL_LENGTH + 0.95*Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.95*Component::PIXEL_LENGTH, -5, false);
	
	// draw brown ground
	glColor3ub(153, 76, 0);
	DrawingUtilNG::drawCube(px * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, -5, px * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, -15, false);
	
	// draw light green surface
	glColor3ub(153, 255, 51);
	DrawingUtilNG::drawRectangle(px * Component::PIXEL_LENGTH + 0.1 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.1 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, true);
	
	glColor3ub(200, 200, 200);
	//
	//    glEnable(GL_POLYGON_OFFSET_FILL);
	//    glPolygonOffset(1, 1);
	//
	//    glBegin(GL_QUADS);
	//
	int x1 = px * Component::PIXEL_LENGTH + 5;
	int x2 = (px + 1) * Component::PIXEL_LENGTH - 5;
	int y1 = py * Component::PIXEL_LENGTH;
	int y2 = (py + 1) * Component::PIXEL_LENGTH;
	int z1 = 0, z2 = 0;
	
	if (!state) {
		z2 = Component::PIXEL_LENGTH * 1.5;
	} else {
		z2 = 0;
	}
	
	//    glVertex3i(x1, y1, 0);
	//    glVertex3i(x2, y1, 0);
	//    glVertex3i(x2, y2, 0);
	//    glVertex3i(x1, y2, 0);
	
	DrawingUtilNG::drawCube(x1, y1, z1, x2, y2, z2, false);
	
	//    glEnd();
	//
	//    glDisable(GL_POLYGON_OFFSET_FILL);
}
