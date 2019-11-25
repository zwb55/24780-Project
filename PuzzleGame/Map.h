/******************************************************
 * Define the map of the game. Can load a text file and convert it to 3D map.
 *****************************************************/

#pragma once
#include <vector>
#include "Component.h"

class Map {
public:
	/* Constants */
	static const int DEFAULT_X = 10;
	static const int DEFAULT_Y = 10;

	/* Member fields */
	std::vector<std::vector<Component*>> grid;
	std::pair<int, int> startPosition;
	std::pair<int, int> endPosition;
	std::pair<int, int> zombiePosition;
	std::vector<std::pair<int, int>> rockPositions;


	/* Functions */
	Map();
	Map(int level);
	~Map();
    void update();
	void draw();
	bool isValid(int gridX, int gridY);

private:
};
