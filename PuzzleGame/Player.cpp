#include "Player.h"
#include "Component.h"
#include <assert.h>
#include <cmath>
#include "DrawingUtilNG.h"


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
	DrawingUtilNG::drawCube(spaceX, spaceY, 0, spaceX + Component::PIXEL_LENGTH, spaceY + Component::PIXEL_LENGTH, 20, true);

}
