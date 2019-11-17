#include "Player.h"
#include "Component.h"
#include <assert.h>
#include <cmath>
#include "DrawingUtilNG.h"
#include "fssimplewindow.h"


/*
Constructor of Player class, set the initial position of player on the grid and in the space.
The space position will be the top left point of player.

If necessary, also set the face direction of player.
Direction definition:
1: up (positive y direction)
2: down (negative y direction)
3: left (negative x direction)
4: right (positive x direction)
*/
Player::Player(int _gridX, int _gridY)
{
	gridX = _gridX;
	gridY = _gridY;
	int loc[2] = { gridX, gridY };
	spaceX = gridX * Component::PIXEL_LENGTH;
	spaceY = gridY * Component::PIXEL_LENGTH;

	isMoving = false;
	face = 1;
}

/*
Set new the position of player.
*/
void Player::setPosition(int _gridX, int _gridY)
{	
	// enforce that the new position should be the neighbor of current position
	assert(abs(_gridX - gridX) + abs(_gridY - gridY) == 1);

	gridX = _gridX;
	gridY = _gridY;
}



std::pair<int, int> Player::getPosition() {
	return std::pair<int, int> {gridX, gridY};
}

/*
Move the player to new position
*/
void Player::move() {
	if (gridX * Component::PIXEL_LENGTH < spaceX) {
		spaceX -= MOVE_SPEED;
		isMoving = true;
	}
	else if (gridX * Component::PIXEL_LENGTH > spaceX) {
		spaceX += MOVE_SPEED;
		isMoving = true;
	}
	else if (gridY * Component::PIXEL_LENGTH < spaceY) {
		spaceY -= MOVE_SPEED;
		isMoving = true;
	}
	else if (gridY * Component::PIXEL_LENGTH > spaceY) {
		spaceY += MOVE_SPEED;
		isMoving = true;
	}
	else {
		isMoving = false;
	}
}

void Player::draw()
{
	//DrawingUtilNG::drawCube(spaceX, spaceY, 0, spaceX + Component::PIXEL_LENGTH, spaceY + Component::PIXEL_LENGTH, 20, true);
	temp += 1;
	glPushMatrix();
	if (temp % 60 < 30) {
		glTranslated(spaceX + 0.5 * Component::PIXEL_LENGTH, spaceY + 0.5 * Component::PIXEL_LENGTH, 0);
	}
	else {
		glTranslated(spaceX + 0.5 * Component::PIXEL_LENGTH, spaceY + 0.5 * Component::PIXEL_LENGTH, -0.03 * Component::PIXEL_LENGTH);
	}
	if (face == 1)
		theta = 0;
	if (face == 3)
		theta = 180;
	if (face == 4)
		theta = 90;
	if (face == 2)
		theta = 270;
	glRotated(theta, 0, 0, 1);
	//head
	glColor3ub(255, 0, 0);
	DrawingUtilNG::drawCube(-0.2 * Component::PIXEL_LENGTH, -0.2 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 1.05 * Component::PIXEL_LENGTH, false);
	//body
	glColor3ub(200, 0, 0);
	DrawingUtilNG::drawCube(-0.2 * Component::PIXEL_LENGTH, -0.2 * Component::PIXEL_LENGTH, 0.35 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 0.75 * Component::PIXEL_LENGTH, false);
	//face
	glColor3ub(255, 255, 255);
	DrawingUtilNG::drawCube(-0.15 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 0.85 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0.25 * Component::PIXEL_LENGTH, 0.95 * Component::PIXEL_LENGTH, false);
	DrawingUtilNG::drawCube(0.05 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 0.85 * Component::PIXEL_LENGTH, 0.15 * Component::PIXEL_LENGTH, 0.25 * Component::PIXEL_LENGTH, 0.95 * Component::PIXEL_LENGTH, false);
	glColor3ub(255, 50, 50);
	//arms and legs
	if (!isMoving) {
		DrawingUtilNG::drawCube(-0.3 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0.45 * Component::PIXEL_LENGTH, -0.2 * Component::PIXEL_LENGTH, 0.05 * Component::PIXEL_LENGTH, 0.7 * Component::PIXEL_LENGTH, false);
		DrawingUtilNG::drawCube(0.2 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0.45 * Component::PIXEL_LENGTH, 0.3 * Component::PIXEL_LENGTH, 0.05 * Component::PIXEL_LENGTH, 0.7 * Component::PIXEL_LENGTH, false);

		DrawingUtilNG::drawCube(-0.15 * Component::PIXEL_LENGTH, -0.07 * Component::PIXEL_LENGTH, 0, -0.05 * Component::PIXEL_LENGTH, 0.07 * Component::PIXEL_LENGTH, 0.35 * Component::PIXEL_LENGTH, false);
		DrawingUtilNG::drawCube(0.05 * Component::PIXEL_LENGTH, -0.07 * Component::PIXEL_LENGTH, 0, 0.15 * Component::PIXEL_LENGTH, 0.07 * Component::PIXEL_LENGTH, 0.35 * Component::PIXEL_LENGTH, false);
		glPopMatrix();
	}
	else {
		glTranslated(0, 0, 0.72 * Component::PIXEL_LENGTH);
		if (temp % 50 < 25) {
			DrawingUtilNG::drawCube(0.05 * Component::PIXEL_LENGTH, 0.03 * Component::PIXEL_LENGTH, -0.65 * Component::PIXEL_LENGTH, 0.15 * Component::PIXEL_LENGTH, 0.17 * Component::PIXEL_LENGTH, -0.3 * Component::PIXEL_LENGTH, false);
			DrawingUtilNG::drawCube(-0.15 * Component::PIXEL_LENGTH, -0.17 * Component::PIXEL_LENGTH, -0.65 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, -0.03 * Component::PIXEL_LENGTH, -0.3 * Component::PIXEL_LENGTH, false);
			glRotated(30, 1, 0, 0);
			DrawingUtilNG::drawCube(-0.3 * Component::PIXEL_LENGTH, 0.05 * Component::PIXEL_LENGTH, -0.25 * Component::PIXEL_LENGTH, -0.2 * Component::PIXEL_LENGTH, 0.15 * Component::PIXEL_LENGTH, 0, false);
			glRotated(-60, 1, 0, 0);
			DrawingUtilNG::drawCube(0.2 * Component::PIXEL_LENGTH, -0.15 * Component::PIXEL_LENGTH, -0.25 * Component::PIXEL_LENGTH, 0.3 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0, false);
			glPopMatrix();
		}
		else if (temp % 50 >= 25) {
			DrawingUtilNG::drawCube(-0.15 * Component::PIXEL_LENGTH, 0.03 * Component::PIXEL_LENGTH, -0.65 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0.17 * Component::PIXEL_LENGTH, -0.3 * Component::PIXEL_LENGTH, false);
			DrawingUtilNG::drawCube(0.05 * Component::PIXEL_LENGTH, -0.17 * Component::PIXEL_LENGTH, -0.65 * Component::PIXEL_LENGTH, 0.15 * Component::PIXEL_LENGTH, -0.03 * Component::PIXEL_LENGTH, -0.3 * Component::PIXEL_LENGTH, false);
			glRotated(-30, 1, 0, 0);
			DrawingUtilNG::drawCube(-0.3 * Component::PIXEL_LENGTH, -0.15 * Component::PIXEL_LENGTH, -0.25 * Component::PIXEL_LENGTH, -0.2 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0, false);
			glRotated(60, 1, 0, 0);
			DrawingUtilNG::drawCube(0.2 * Component::PIXEL_LENGTH, 0.05 * Component::PIXEL_LENGTH, -0.25 * Component::PIXEL_LENGTH, 0.3 * Component::PIXEL_LENGTH, 0.15 * Component::PIXEL_LENGTH, 0, false);
			glPopMatrix();
		}
	}
}
