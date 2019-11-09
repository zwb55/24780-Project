#include <stdio.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "Camera3D.h"
#include "OrbitingViewer.h"
#include "DrawingUtilNG.h"
#include "Controller.h"
#include <iostream>

int main(void) {
	srand(time(NULL));
	bool terminate = false;
	Camera3D camera;
	OrbitingViewer orbit;
	Controller gameController;

	camera.z = 10.0;

	FsOpenWindow(16, 16, 1200, 800, 1);

	while (!terminate)
	{
		FsPollDevice();

		int wid, hei;
		FsGetWindowSize(wid, hei);

		int key = FsInkey();
		switch (key)
		{
		case FSKEY_ESC:
			terminate = true;
			break;
		case FSKEY_W:
			gameController.update(1);
			break;
		case FSKEY_S:
			gameController.update(2);
			break;
		case FSKEY_A:
			gameController.update(3);
			break;
		case FSKEY_D:
			gameController.update(4);
			break;
		default:
			gameController.update(0);
		}

		if (0 != FsGetKeyState(FSKEY_LEFT))
			orbit.h += Camera3D::PI / 180.0;

		if (0 != FsGetKeyState(FSKEY_RIGHT))
			orbit.h -= Camera3D::PI / 180.0;

		if (0 != FsGetKeyState(FSKEY_UP))
			orbit.p += Camera3D::PI / 180.0;

		if (0 != FsGetKeyState(FSKEY_DOWN))
			orbit.p -= Camera3D::PI / 180.0;

		if (0 != FsGetKeyState(FSKEY_F) && orbit.dist > 1.0)
			orbit.dist /= 1.05;

		if (0 != FsGetKeyState(FSKEY_B) && orbit.dist < 500.0)
			orbit.dist *= 1.05;

		orbit.setUpCamera(camera);

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		//glDisable(GL_DEPTH_TEST);
		//glDisable(GL_POLYGON_OFFSET_FILL);
		//DrawingUtilNG::drawRectangle(0., 0., -60, -60, true);

		glViewport(0, 0, wid, hei);

		// Set up 3D drawing
		camera.setUpCameraProjection();
		camera.setUpCameraTransformation();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1, 1);

		// 3D drawing from here
		gameController.draw();

		glMatrixMode(GL_PROJECTION); // Tell opengl that we are doing project matrix work
		glLoadIdentity(); // Clear the matrix
		glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0); // Setup an Ortho view
		glMatrixMode(GL_MODELVIEW); // Tell opengl that we are doing model matrix work. (drawing)
		glLoadIdentity(); // Clear the model matrix


		//DrawingUtilNG::drawRectangle(0., 0., -60, -60, true);
		

		FsSwapBuffers();
		FsSleep(10);


	}

	return 0;
}