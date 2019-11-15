#include "Switch.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"
#include "Plain.h"

Switch::Switch(int _px, int _py) : Component(_px, _py, false, 'b') {
	
	color[0] = DrawingUtilNG::getRandom(0, 255);
	color[1] = DrawingUtilNG::getRandom(0, 255);
	color[2] = DrawingUtilNG::getRandom(0, 255);
	
	state = false;
	r = 6;
	theta = 45 / 180 * PI;
	length = 10;
}
void Switch::draw()
{
	//gluSphere
	glPushMatrix();
	GLUquadric* quad;
	quad = gluNewQuadric();
	GLUquadric* cylinder;
	cylinder = gluNewQuadric();

	glTranslated((px + 0.5) * Component::PIXEL_LENGTH, (py + 0.5) * Component::PIXEL_LENGTH, 0);
	// draw sphere
	glColor3ub(160, 82, 45);
	gluSphere(quad, r, 36, 36);

	// draw cylinder use theta
	if (state)
	{
		if (theta < 45)
			theta += 2;
	}
	else
	{
		if (theta > -45)
			theta -= 2;
	}
	glColor3ub(0, 0, 0);
	glRotated(theta, 1, 0, 0);
	gluCylinder(cylinder, 1.5, 1.5, 20, 20, 20);

	glPopMatrix();

	color[0] = 0;
	color[1] = 153;
	color[2] = 0;
	glColor3ub(color[0], color[1], color[2]);
	DrawingUtilNG::drawCube(px * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, 0, px * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, -5, false);

	// draw brown ground
	glColor3ub(153, 76, 0);
	DrawingUtilNG::drawCube(px * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.05 * Component::PIXEL_LENGTH, -5, px * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.95 * Component::PIXEL_LENGTH, -15, false);

	// draw light green surface
	glColor3ub(153, 255, 51);
	DrawingUtilNG::drawRectangle(px * Component::PIXEL_LENGTH + 0.1 * Component::PIXEL_LENGTH, py * Component::PIXEL_LENGTH + 0.1 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, true);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}

void Switch::update()
{
	open = !open;
}
