#include "Button.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"

Button::Button(int _px, int _py): Component(_px, _py, true){
    // assign a random color to the plain (should be improved)
    color[0] = DrawingUtilNG::getRandom(0, 255);
    color[1] = DrawingUtilNG::getRandom(0, 255);
    color[2] = DrawingUtilNG::getRandom(0, 255);
}

void Button::update(std::vector<int*> objectInds) {
    
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
    int x1 = px * Component::PIXEL_LENGTH;
    int x2 = (px + 1) * Component::PIXEL_LENGTH;
    int y1 = py * Component::PIXEL_LENGTH;
    int y2 = (py + 1) * Component::PIXEL_LENGTH;
    int z1 = 0, z2 = 0;
    
    if (open) {
        z2 = Component::PIXEL_LENGTH;
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
