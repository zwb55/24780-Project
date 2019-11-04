#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "Camera3D.h"
#include "OrbitingViewer.h"
#include "DrawingUtilNG.h"
#include "Map.h"

int main(void) {
	bool terminate = false;
	Camera3D camera;
	OrbitingViewer orbit;
	Map gameMap;

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

		glViewport(0, 0, wid, hei);

		// Set up 3D drawing
		camera.setUpCameraProjection();
		camera.setUpCameraTransformation();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1, 1);

		// 3D drawing from here
		gameMap.draw();
		//glColor3ub(93, 290, 112);
		////DrawingUtilNG::drawCube(-10.0, -10.0, -10.0, 10.0, 10.0, 10.0);
		//DrawingUtilNG::drawCube(0, 0, 0, 20.0, 20.0, 20.0, true, &impact);

		//// Set up 2D drawing
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		//glDisable(GL_DEPTH_TEST);

		FsSwapBuffers();
		FsSleep(10);
	}

	return 0;
}