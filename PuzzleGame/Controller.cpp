#include "Controller.h"

/*
The default constructor of Controller class. Will initialize a controller class with level 0
*/
Controller::Controller(): Controller(0) {}

/*
Construt the Controller class by passing in a level argument. Currently initialize a default map,
but in the future will initialize a map with specific level by loading corresponding map file.

Currently initialize the player at 0, 0. Will be developed in the future to initialize
the player at starting point which is defined in map.
*/
Controller::Controller(int _level): player(0, 0)
{
	level = _level;
}

/*
Perform update based on user input. Define the input code:
0: No input
1: Go up (positive y direction)
2: Go down (negative y direction)
3: Go left (negative x direction)
4: Go right (positive x direction)
5: Operation (open the door, switch the botton, etc)
*/
void Controller::update(int code)
{
	if (code != 0 && !isAvailable()) {
		return;
	}
	if (code == 1 && map.isValid(player.gridX, player.gridY + 1)) {
		player.setPosition(player.gridX, player.gridY + 1);
	}
	else if (code == 3 && map.isValid(player.gridX - 1, player.gridY)) {
		player.setPosition(player.gridX - 1, player.gridY);
	}
	else if (code == 4 && map.isValid(player.gridX + 1, player.gridY)) {
		player.setPosition(player.gridX + 1, player.gridY);
	}
	player.move();
}

/*
Get the center position of map. This function is designed to be used by Orbit class
since it need to rotate based on the center of the map.

Return format: pair<int , int> {xPosition, yPosition}
*/
std::pair<int, int> Controller::getCenter()
{
	int xPosition = map.grid.size() * Component::PIXEL_LENGTH / 2;
	int yPosition = map.grid[0].size() * Component::PIXEL_LENGTH / 2;

	return std::pair<int, int> {xPosition, yPosition};
}

/*
Draw all the things in current map
*/
void Controller::draw()
{
	map.draw();
	player.draw();
}

/*
Check whether current state is available for user operations.
Unavailable situation: player is moving, transition animations
*/
bool Controller::isAvailable()
{
	return !player.isMoving;
}
