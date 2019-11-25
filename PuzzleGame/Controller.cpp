#include "Controller.h"
#include "starfield.h"
#include <iostream>
#include "fssimplewindow.h"
#include <string>
#include <fstream>

using namespace std;

const int KEY_NUM = 8;

/*
The default constructor of Controller class. Will initialize a controller class with level 0
*/
Controller::Controller(): player(0, 0), zombie(1, 1, 1) {
	level = 0;
	Rock rock1(4, 4);
	Rock rock2(6, 6);
	Rocks.push_back(rock1);
	Rocks.push_back(rock2);
	pos.push_back(make_pair(rock1.gridX,rock1.gridY));
	pos.push_back(make_pair(rock2.gridX, rock2.gridY));
}

/*
Construt the Controller class by passing in a level argument. Currently initialize a default map,
but in the future will initialize a map with specific level by loading corresponding map file.

Currently initialize the player at 0, 0. Will be developed in the future to initialize
the player at starting point which is defined in map.
*/
Controller::Controller(int _level): map(_level), player(map.startPosition.first, map.startPosition.second), zombie(2, 6, 1)
{
	//ComicSansFont comicsans;
	level = _level;
	
	// add rocks from map
	for (std::pair<int, int>& rockPos : map.rockPositions) {
		Rock rock(rockPos.first, rockPos.second);
		Rocks.push_back(rock);
	}
	if (level == 1) {
		ifstream inFile1;
		string filename1 = "initkey.txt";
		inFile1.open(filename1);

		if (inFile1.is_open()) {
			for (int line = 0; line < KEY_NUM; line++)
			{
				double locX, locY;
				double gapX, gapY;  // the gap between text and frame
				int width;
				int height;
				double scale; // size of string
				string text;
				inFile1 >> locX >> locY >> gapX >> gapY >> width >> height >> scale >> text;
				TeachingKey akey(locX, locY, gapX, gapY, width, height, scale, text);
				Keys.push_back(akey);
			}
		}
		else {
			exit(1);
		}
		inFile1.close();
	}
	
}

bool Controller::isObstacle(vector<pair<int, int>> pos, int intend_x, int intend_y)
{
	for (int i = 0; i < pos.size(); i++)
	{
		if (intend_x == pos[i].first && intend_y == pos[i].second)
			return true;
	}
	return false;
}

/*
Check whether pass the game
*/
bool Controller::pass()
{
	if (level == 1)
	{
		for (int i = 0; i < Keys.size(); i++)
		{
			if (Keys[i].isPressed == false) return false;
		}
	}
	return isAvailable() && player.getPosition() == map.endPosition;
}

void Controller::setkeypressed(int i)
{
	Keys[i].isPressed = true;
}

/*
Perform update based on user input. Define the input code:
0: No input
1: Go up (positive y direction)
2: Go right (positive x direction)
3: Go down (negative y direction)
4: Go left (negative x direction)
5: Operation (open the door, switch the botton, etc)
*/
void Controller::update(int code)
{
	
	if (code != 0 && !isAvailable()) {
		return;
	}
	
	if (code == 1)
	{
		player.face=1;
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
					if (Rocks[j].gridX == intend_x && Rocks[j].gridY == intend_y) // decide which rock is going to be moved
						break;
				}
				Rocks[j].setPosition(rock_next_x, rock_next_y);
				player.setPosition(intend_x, intend_y);
			}
		}
	}
	else if (code == 3)
	{
		player.face=3;
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
	else if (code == 4)
	{
		player.face=4;
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
	else if (code == 2)
	{
		player.face=2;
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
	else if (code == 5)
	{
		std::pair<int, int> loc = player.getPosition();
		int direction1[4] = { 0,1,0,-1 };
		int direction2[4] = { 1,0,-1,0 };
		int nextX = loc.first + direction1[player.face-1];
		int nextY = loc.second + direction2[player.face-1];
		if (nextX >= 0 && nextX < map.grid.size() && nextY >= 0 && nextY < map.grid[0].size())
		{
			if (map.grid[nextX][nextY]) {
				// if player is facing a switch
				char componentID = map.grid[nextX][nextY]->ID;

				if (componentID == 'S')
				{
					if (level == 1) setkeypressed(7);
					int* doorLoc = map.grid[nextX][nextY]->corrCompLoc;
					map.grid[nextX][nextY]->state = !map.grid[nextX][nextY]->state;
					map.grid[doorLoc[0]][doorLoc[1]]->state = !map.grid[doorLoc[0]][doorLoc[1]]->state;
				}
			}
		}
	}
	
	
	bool valid;
	int zombie_intendX = zombie.gridX + zombie.dirX, zombie_intendY = zombie.gridY + zombie.dirY;
	if (map.isValid(zombie_intendX, zombie_intendY) && !isObstacle(pos, zombie_intendX, zombie_intendY))
		valid = true;
	else
		valid = false;
	
	zombie.move(valid);
	
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
	zombie.draw();
	for (int i = 0; i < Rocks.size(); i++)
	{
		Rocks[i].draw();
	}
}

void Controller::draw2D()
{
	if (level == 1)
	{
		for (int i = 0; i < Keys.size(); i++)
		{
			Keys[i].draw(comicsans);
		}
	}
}

/*
Updates the objectInds field of map with all the updated positions of objects
*/
void Controller::updateObjectInds() {
	for (int i = 0; i < map.grid.size(); i++) {
		for (int j = 0; j < map.grid[0].size(); j++) {
			if (!map.grid[i][j]) {
				continue;
			}
			char componentID = map.grid[i][j]->ID;
			std::pair<int, int> loc = player.getPosition();
			switch (componentID) {
				case 'p':
					break;
				case 'b':
				{
					int* doorLoc = map.grid[i][j]->corrCompLoc;

					bool hasObstacle = isObstacle(pos, i, j);
					if ((loc.first == i && loc.second == j) || hasObstacle) {
						map.grid[i][j]->state = false;
						map.grid[doorLoc[0]][doorLoc[1]]->state = false;
						if (level == 1) setkeypressed(6);
					}
					else {
						map.grid[i][j]->state = true;
						map.grid[doorLoc[0]][doorLoc[1]]->state = true;
					}
				}
					break;
				case 'd':
					break;
				case 's':
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
