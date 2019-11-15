#include "Button.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"
#include "Plain.h"

Button::Button(int _px, int _py): Component(_px, _py, true) {
    // assign a random color to the plain (should be improved)
	color[0] = DrawingUtilNG::getRandom(0, 255);
    color[1] = DrawingUtilNG::getRandom(0, 255);
    color[2] = DrawingUtilNG::getRandom(0, 255);
}

void Button::update() {
	open = !open;
}

void Button::draw() {
    // draw a surface on XY plane
//    glColor3ub(color[0], color[1], color[2]);
//
//    glEnable(GL_POLYGON_OFFSET_FILL);
//    glPolygonOffset(1, 1);
//
//    glBegin(GL_QUADS);
//
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
	
    int x1 = px * Component::PIXEL_LENGTH + 5;
    int x2 = (px + 1) * Component::PIXEL_LENGTH - 5;
    int y1 = py * Component::PIXEL_LENGTH + 5;
    int y2 = (py + 1) * Component::PIXEL_LENGTH - 5;
    int z1 = 1, z2 = 1;
    
//    if (open) {
//        z2 = Component::PIXEL_LENGTH * 2;
//    } else {
//        z2 = 0;
//    }
//
//    glVertex3i(x1, y1, 0);
//    glVertex3i(x2, y1, 0);
//    glVertex3i(x2, y2, 0);
//    glVertex3i(x1, y2, 0);
    glColor3ub(255, 255, 255);
    DrawingUtilNG::drawCube(x1, y1, z1, x2, y2, z2, false);
    
//    glEnd();
//    
//    glDisable(GL_POLYGON_OFFSET_FILL);
}
