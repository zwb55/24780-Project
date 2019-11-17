#include "Map.h"
#include "Plain.h"
#include "StartPoint.h"
#include "EndPoint.h"
#include "Button.h"
#include "Door.h"
#include "Rock.h"
#include "Switch.h"
#include <string>
#include <fstream>
#include <iostream>

std::ifstream inFile;
std::ofstream outFile;

/*
The default constructor initialize a map with default length and all plain on it
*/
Map::Map(): grid(DEFAULT_X, std::vector<Component*> (DEFAULT_Y, nullptr)){
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			grid[i][j] = new Plain(i, j);
		}
	}
	// test start and end point
	grid[0][0] = new StartPoint(0, 0);
	grid[2][2] = new EndPoint(2, 2);
	grid[3][3] = new Button(3, 3, 8, 8);
	grid[8][8] = new Door(8, 8);
	grid[7][7] = new Door(7, 7);
	grid[1][6] = new Switch(1, 6, 7, 7);
	
	// initialize start and end position
	startPosition.first = 0;
	startPosition.second = 0;
	endPosition.first = 2;
	endPosition.second = 2;
}

/*
Map from charater to components:
'0': NULL
'p': Plain
's': StartPoint
'e': EndPoint
'b': Button (if see button, read two more digits representing the position of corresponding door)
'd': Door 
'r': Rock (store its position and send back to Controller)
'S': Switch
*/
Map::Map(int level)
{
	std::string filename = "./map_file/level" + std::to_string(level) + ".txt";
	inFile.open(filename);

	if (inFile.is_open()) {
		int num_row = 0;
		int num_col = 0;
		while (!inFile.eof()) {
			inFile >> num_row;
			inFile >> num_col;

			std::vector<std::vector<Component*>> temp(num_col, std::vector<Component*>(num_row, nullptr));

			for (int i = 0; i < num_row; i++) {
				for (int j = 0; j < num_col; j++) {
					char curr;
					int tempx;
					int tempy;
					inFile >> curr;
					Component* currComp = nullptr;

					switch (curr) {
					case 'p':
						currComp = new Plain(j, num_row - 1 - i);
						break;
					case 's':
						currComp = new StartPoint(j, num_row - 1 - i);
						startPosition.first = j;
						startPosition.second = num_row - 1 - i;
						break;
					case 'e':
						currComp = new EndPoint(j, num_row - 1 - i);
						endPosition.first = j;
						endPosition.second = num_row - 1 - i;
						break;
					case 'd':
						currComp = new Door(j, num_row - 1 - i);
						break;
					case 'b':
						inFile >> tempx;
						inFile >> tempy;
						currComp = new Button(j, num_row - 1 - i, tempx, tempy);
						break;
					case 'r':
						currComp = new Plain(j, num_row - 1 - i);
						rockPositions.push_back(std::pair<int, int>{i, num_row - 1 - i});
						break;
					}

					temp[j][num_row - 1 - i] = currComp;
				}
			}
			grid = temp;
			break;
		}
	}
	else {
		exit(1);
	}
}

Map::~Map() {
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			delete grid[i][j];
		}
	}
}

void Map::update() {
	
}

/*
Draw each component on the map
*/
void Map::draw() {
	update();
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (!grid[i][j]) {
				continue;
			}
			grid[i][j]->draw();
		}
	}
}

/*
Check whether the position is valid
Non valid case:
out of bound, empty (null in map), canLand = false
*/
bool Map::isValid(int gridX, int gridY)
{
	return gridX >= 0 && gridX < grid.size() && gridY >= 0 && gridY < grid[0].size()
		&& grid[gridX][gridY] && grid[gridX][gridY]->canLand;
}
