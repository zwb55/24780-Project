/*
This is the copy of our project
For test
*/

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
#include "GraphicFont.h"
#include "starfield.h"

const int MAX_LEVEL = 9;

/* the 2 png using in start scene*/
YsRawPngDecoder png[2];
GLuint texId[2];
void init_pngs();
void drawStartScene(JokermanFont& jokerman, double& theta, double& delta);

/*
Define the main logic and display during one game, return an int code according
to different end state of the game:

Return:
0: exit the game, back to main window
1: reset the game, should directly restart the game
2: pass the game, should go to next level (maybe with some transition animations), 
	if it's the final level, back to main window
*/
int gamePlay(Camera3D& camera, OrbitingViewer& orbit, Controller* gameController) {
	bool terminate = false;
	bool clockwise = true;

	vector<star> Stars;
	for (int i = 0; i < 600; i++)
	{
		star aStar;
		aStar.initialize(1200, 800);
		Stars.push_back(aStar);
	}

	// set the camera focus center
	orbit.focusX = gameController->getCenter().first;
	orbit.focusY = gameController->getCenter().second;

	while (!terminate)
	{
		int key = FsInkey();
		switch (key)
		{
		case FSKEY_ESC:
			terminate = true;
			break;
		case FSKEY_W:
			gameController->update(1 + (orbit.face) % 4);
			if (gameController->getcurrLevel() == 1) gameController->setkeypressed(0);
			break;
		case FSKEY_D:
			gameController->update(1 + (orbit.face + 1) % 4);
			if (gameController->getcurrLevel() == 1) gameController->setkeypressed(3);
			break;
		case FSKEY_S:
			gameController->update(1 + (orbit.face + 2) % 4);
			if (gameController->getcurrLevel() == 1) gameController->setkeypressed(2);
			break;
		case FSKEY_A:
			gameController->update(1 + (orbit.face + 3) % 4);
			if (gameController->getcurrLevel() == 1) gameController->setkeypressed(1);
			break;
		case FSKEY_SPACE:
			gameController->update(5);
			break;
		case FSKEY_R:
			// reset current game
			return 1;
		default:
			gameController->update(0);
		}

		if (0 != FsGetKeyState(FSKEY_LEFT) && !orbit.isorbiting)
		{
			orbit.isorbiting = true;
			clockwise = true;
			if (gameController->getcurrLevel() == 1) gameController->setkeypressed(4);
		}

		if (0 != FsGetKeyState(FSKEY_RIGHT) && !orbit.isorbiting)
		{
			orbit.isorbiting = true;
			clockwise = false;
			if (gameController->getcurrLevel() == 1) gameController->setkeypressed(5);
		}

		if (0 != FsGetKeyState(FSKEY_UP) && orbit.r < 500)
			orbit.r += 10;

		if (0 != FsGetKeyState(FSKEY_DOWN) && orbit.r > 100.0)
			orbit.r -= 10;

		if (orbit.isorbiting)
		{
			orbit.changeview(clockwise);
		}

		// check whether passed the game
		if (gameController->pass()) {
			return 2;
		}

		FsPollDevice();

		int wid, hei;
		FsGetWindowSize(wid, hei);

		orbit.setUpCamera(camera);

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glViewport(0, 0, wid, hei);

		// Set up 3D drawing
		camera.setUpCameraProjection();
		camera.setUpCameraTransformation(orbit);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1, 1);

		// 3D drawing from here
		gameController->draw();

		// 2D drawing from here
		glMatrixMode(GL_PROJECTION); // Tell opengl that we are doing project matrix work
		glLoadIdentity(); // Clear the matrix
		glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);
		//glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0); // Setup an Ortho view
		glMatrixMode(GL_MODELVIEW); // Tell opengl that we are doing model matrix work. (drawing)
		glLoadIdentity(); // Clear the model matrix
		glDisable(GL_DEPTH_TEST);
		gameController->draw2D();

		for (auto& Star : Stars)
		{
			Star.move(wid, hei);
			if (Star.out(wid, hei))
				Star.initialize(wid, hei);
			Star.draw();
		}
		FsSwapBuffers();
		FsSleep(10);
	}

	return 0;
}


/*
At main window:
Press s to start the game
Press ESC to exit

At the game:
Press R to reset
Press ESC to go back to main window
*/
int main(void) {
	srand(time(NULL));
	bool terminate = false;
	int currLevel = 7;

	int leftButton, middleButton, rightButton, locX, locY;
	int mouseEvent;

	double theta = 0.;  // for the startscene
	double delta = 0.5;

	Camera3D camera;
	OrbitingViewer orbit;
	Controller* gameController;
	int returnCode = 0;

	FsOpenWindow(16, 16, 1200, 800, 1);

	JokermanFont jokerman;
	init_pngs();

	while (!terminate) {
		int key = FsInkey();
		mouseEvent = FsGetMouseEvent(leftButton, middleButton, rightButton, locX, locY);

		if (key == FSKEY_ESC) {
			terminate = true;
		}
		else if ((mouseEvent == FSMOUSEEVENT_LBUTTONDOWN &&
			locX > 430 && locX < 710 &&
			locY > 620 && locY < 700)
			|| returnCode != 0) {
			// start a new game
			gameController = new Controller(currLevel);
			returnCode = gamePlay(camera, orbit, gameController);
			delete gameController;
		}
		
		// update level according to returnCode
		if (returnCode == 2 && currLevel == MAX_LEVEL) {
			// can show some congrats, currently directly return to main window
			returnCode = 0;
			currLevel = 1;
		}
		else if (returnCode == 2) {
			currLevel++;
		}
		else if (returnCode == 0) {
			// reset to the first level of the game
			currLevel = 1;
			// start scene from here
			drawStartScene(jokerman, theta, delta);
			FsSwapBuffers();
			FsSleep(10);
		}

		// show main window
		FsPollDevice();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		/*glColor3ub(255, 0, 0);
		DrawingUtilNG::drawRectangle(0, 0, 800, 600, true);

		FsSwapBuffers();
		FsSleep(10);*/
	}
}

void init_pngs()
{
	png[0].Decode("startscene.png");
	png[1].Decode("scrshot.png");
	for (int i = 0; i < 2; i++)
	{
		glGenTextures(1, &texId[i]);  // Reserve one texture identifier
		glBindTexture(GL_TEXTURE_2D, texId[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D
		(GL_TEXTURE_2D,
			0,    // Level of detail
			GL_RGBA,
			png[i].wid,
			png[i].hei,
			0,    // Border width, but not supported and needs to be 0.
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			png[i].rgba);
	}
}

void drawStartScene(JokermanFont& jokerman, double& theta, double& delta)
{
	int wid, hei;
	FsGetWindowSize(wid, hei);

	glViewport(0, 0, wid, hei);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glColor4d(1.0, 1.0, 1.0, 1.0);   // this color will "tint" the image

	// enable texture mapping
	glEnable(GL_TEXTURE_2D);

	// bind a texture to OpenGL primitives
	glBindTexture(GL_TEXTURE_2D, texId[0]);

	glBegin(GL_QUADS);

	glTexCoord2d(0.0, 0.0);
	glVertex2i(0, 0);
	glTexCoord2d(1.0, 0.0);
	glVertex2i(1200, 0);
	glTexCoord2d(1.0, 1.0);
	glVertex2i(1200, 800);
	glTexCoord2d(0.0, 1.0);
	glVertex2i(0, 800);

	glEnd();

	// turn off texture 
	glDisable(GL_TEXTURE_2D);

	// draw text start button
	theta += delta;
	if (theta > 10. || theta < -10.) delta *= -1;

	jokerman.setColorHSV(210, 1, 1);
	jokerman.drawText("MINI  MAZE", 230, 264, 1.2, 0);
	jokerman.setColorHSV(0, 0, 100);
	jokerman.drawText("START!", 430, 720, 0.8, theta);
}
