#include <math.h>
#include "fssimplewindow.h"
#include "OrbitingViewer.h"

OrbitingViewer::OrbitingViewer()
{
	initialize();
}

void OrbitingViewer::initialize(void)
{
	h = 0;
	p = 0;
	b = 0;
	r = 300;
	theta = 0;
	height = 150;
	dist = 300.0;
	focusX = 0.0;
	focusY = 0.0;
	focusZ = 0.0;
	isorbiting = false;
	face = 0;
}

void OrbitingViewer::setUpCamera(Camera3D& camera)
{
	camera.h = h;
	camera.p = p;
	camera.b = b;
	/*
	double vx, vy, vz;
	camera.getForwardVector(vx, vy, vz);
	camera.x = focusX - vx * dist;
	camera.y = focusY - vy * dist;
	camera.z = focusZ - vz * dist;
	*/

	camera.x = focusX - r * sin(theta * (Camera3D::PI / 180.0));
	camera.y = focusY - r * cos(theta * (Camera3D::PI / 180.0));
	camera.z = height;
}
/*
face: 0, 1, 2, 3
face (X, Y)
  0  (0, 1)
  1  (1, 0)
  2  (0,-1)
  3  (-1,0)
*/
void OrbitingViewer::changeface(bool clockwise)
{
	if (clockwise)
	{
		if (face < 3) face++;
		else face = 0;
	}
	else
	{
		if (face > 0) face--;
		else face = 3;
	}
}

void OrbitingViewer::changeview(bool clockwise)
{
	if (clockwise)
		theta += 3;
	else
		theta -= 3;

	if ((int)(theta) % 90 == 0)
	{
		isorbiting = false;
		changeface(clockwise);
	}
}

