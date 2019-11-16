#include "Controller.h"
#include <iostream>

using namespace std;

/*
The default constructor of Controller class. Will initialize a controller class with level 0
*/
Controller::Controller(): Controller(0) {

}

/*
Construt the Controller class by passing in a level argument. Currently initialize a default map,
but in the future will initialize a map with specific level by loading corresponding map file.

Currently initialize the player at 0, 0. Will be developed in the future to initialize
the player at starting point which is defined in map.
*/
Controller::Controller(int _level): player(0, 0)
{
	level = _level;
	Rock rock1(4, 4);
	Rock rock2(6, 6);
	Rocks.push_back(rock1);
	Rocks.push_back(rock2);
	pos.push_back(make_pair(rock1.gridX,rock1.gridY));
	pos.push_back(make_pair(rock2.gridX, rock2.gridY));

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


bool Controller::isObstacle(vector<pair<int, int>> pos, int intend_x, int intend_y)
{
	for (int i = 0; i < pos.size(); i++)
	{
		if (intend_x == pos[i].first && intend_y == pos[i].second)
			return true;
	}
	return false;
}

void Controller::update(int code)
{
	
	if (code != 0 && !isAvailable()) {
		return;
	}
	if (code == 1)
	{
		int intend_x = player.gridX, intend_y = player.gridY + 1;
		if(map.isValid(intend_x,intend_y)&&!isObstacle(pos,intend_x,intend_y))
			player.setPosition(player.gridX, player.gridY + 1);
		else if (map.isValid(intend_x, intend_y) && isObstacle(pos, intend_x, intend_y))
		{
			int rock_next_x = intend_x, rock_next_y = intend_y + 1;
			if (map.isValid(rock_next_x, rock_next_y) && !isObstacle(pos, rock_next_x, rock_next_y))
			{
				int j = 0;
				for (;j<Rocks.size();j++)
				{
					if (Rocks[j].gridX == intend_x && Rocks[j].gridY == intend_y)
						break;
				}
				Rocks[j].setPosition(rock_next_x, rock_next_y);
				player.setPosition(intend_x, intend_y);
			}
		}
	}
	else if (code == 2)
	{
		int intend_x = player.gridX, intend_y = player.gridY - 1;
		if (map.isValid(intend_x, intend_y) && !isObstacle(pos, intend_x, intend_y))
			player.setPosition(player.gridX, player.gridY - 1);
		else if (map.isValid(intend_x, intend_y) && isObstacle(pos, intend_x, intend_y))
		{
			int rock_next_x = intend_x, rock_next_y = intend_y - 1;
			if (map.isValid(rock_next_x, rock_next_y) && !isObstacle(pos, rock_next_x, rock_next_y))
			{
				int j = 0;
				for (; j < Rocks.size(); j++)
				{
					if (Rocks[j].gridX == intend_x && Rocks[j].gridY == intend_y)
						break;
				}
				Rocks[j].setPosition(rock_next_x, rock_next_y);
				player.setPosition(intend_x, intend_y);
			}
		}
	}
	else if (code == 3)
	{
		int intend_x = player.gridX-1, intend_y = player.gridY;
		if (map.isValid(intend_x, intend_y) && !isObstacle(pos, intend_x, intend_y))
			player.setPosition(player.gridX-1, player.gridY);
		else if (map.isValid(intend_x, intend_y) && isObstacle(pos, intend_x, intend_y))
		{
			int rock_next_x = intend_x-1, rock_next_y = intend_y;
			if (map.isValid(rock_next_x, rock_next_y) && !isObstacle(pos, rock_next_x, rock_next_y))
			{
				int j = 0;
				for (; j < Rocks.size(); j++)
				{
					if (Rocks[j].gridX == intend_x && Rocks[j].gridY == intend_y)
						break;
				}
				Rocks[j].setPosition(rock_next_x, rock_next_y);
				player.setPosition(intend_x, intend_y);
			}
		}
	}
	else if (code == 4)
	{
		int intend_x = player.gridX+1, intend_y = player.gridY;
		if (map.isValid(intend_x, intend_y) && !isObstacle(pos, intend_x, intend_y))
			player.setPosition(player.gridX+1, player.gridY);
		else if (map.isValid(intend_x, intend_y) && isObstacle(pos, intend_x, intend_y))
		{
			int rock_next_x = intend_x+1, rock_next_y = intend_y;
			if (map.isValid(rock_next_x, rock_next_y) && !isObstacle(pos, rock_next_x, rock_next_y))
			{
				int j = 0;
				for (; j < Rocks.size(); j++)
				{
					if (Rocks[j].gridX == intend_x && Rocks[j].gridY == intend_y)
						break;
				}
				Rocks[j].setPosition(rock_next_x, rock_next_y);
				player.setPosition(intend_x, intend_y);
			}
		}
	}

	player.move();
	pos.clear();
	for (auto rock : Rocks)
	{
		rock.move();
		pos.push_back(make_pair(rock.gridX,rock.gridY));
	}
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
	updateObjectInds();
	map.draw();
	player.draw();
	for (int i = 0; i < Rocks.size(); i++)
	{
		Rocks[i].draw();
	}
}

/*
Updates the objectInds field of map with all the updated positions of objects
*/
void Controller::updateObjectInds() {
	for (int i = 0; i < map.grid.size(); i++) {
		for (int j = 0; j < map.grid[0].size(); j++) {
			char componentID = map.grid[i][j]->ID;
			std::pair<int, int> loc = player.getPosition();
			switch (componentID) {
				case 'p':
					break;
				case 'b':
					int* doorLoc = map.grid[i][j]->corrCompLoc;
					bool hasObstacle = isObstacle(pos, i, j);
					cout << doorLoc[0] << doorLoc[1] << endl;
					if ((loc.first == i && loc.second == j) || hasObstacle) {
						map.grid[i][j]->state = false;
						map.grid[doorLoc[0]][doorLoc[1]]->state = false;
					} else {
						map.grid[i][j]->state = true;
						map.grid[doorLoc[0]][doorLoc[1]]->state = true;
					}
					break;
			}
		}

	}

}

/*
Check whether current state is available for user operations.
Unavailable situation: player is moving, transition animations
*/
bool Controller::isAvailable()
{
	return !player.isMoving;
}
