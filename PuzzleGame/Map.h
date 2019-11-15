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
    std::vector<int*> objectInds;
	std::vector<int*> lastObjectInds;
	std::vector<int*> buttonDoorPairs;

	/* Functions */
	Map();
	~Map();
    void update();
	void draw();
	bool isValid(int gridX, int gridY);

private:
};
