#include "Rock.h"
#include "DrawingUtilNG.h"
#include "fssimplewindow.h"
#include "Component.h"
#include <assert.h>

Rock::Rock(int _gridX, int _gridY)
{
	gridX = _gridX;
	gridY = _gridY;
	spaceX = gridX * Component::PIXEL_LENGTH;
	spaceY = gridY * Component::PIXEL_LENGTH;

}

void Rock::setPosition(int _gridX, int _gridY)
{
	// enforce that the new position should be the neighbor of current position
	assert(abs(_gridX - gridX) + abs(_gridY - gridY) == 1);

	gridX = _gridX;
	gridY = _gridY;
}

int* Rock::getPosition()
{
	int* loc = new int[2];
	loc[0] = gridX; loc[1] = gridY;
	return loc;
}

void Rock::move()
{
	if (gridX * Component::PIXEL_LENGTH < spaceX) {
		spaceX -= MOVE_SPEED;
	}
	else if (gridX * Component::PIXEL_LENGTH > spaceX) {
		spaceX += MOVE_SPEED;
	}
	else if (gridY * Component::PIXEL_LENGTH < spaceY) {
		spaceY -= MOVE_SPEED;
	}
	else if (gridY * Component::PIXEL_LENGTH > spaceY) {
		spaceY += MOVE_SPEED;
	}
	else {
		return;
	}
}

void Rock::draw()
{
	// Need to be improved.
	glColor3ub(128, 128, 128);
	DrawingUtilNG::drawCube(gridX * Component::PIXEL_LENGTH, gridY * Component::PIXEL_LENGTH, 0, (gridX + 1) * Component::PIXEL_LENGTH, (gridY + 1) * Component::PIXEL_LENGTH, 10, false);

}