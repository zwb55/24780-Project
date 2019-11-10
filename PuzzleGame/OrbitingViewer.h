#pragma once
#include "Camera3D.h"

class Camera3D;

class OrbitingViewer
{
public:
	double h, p, b, theta;
	double dist, r, height;
	double focusX, focusY, focusZ;
	bool isorbiting;
	int face;
	OrbitingViewer();
	void initialize(void);
	void setUpCamera(Camera3D& camera);
	void changeface(bool clockwise);
	void changeview(bool clockwise);
};


