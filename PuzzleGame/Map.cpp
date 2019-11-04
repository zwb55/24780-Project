#include "Map.h"
#include "Plain.h"

/*
The default constructor initialize a map with default length and all plain on it
*/
Map::Map(): map(DEFAULT_X, std::vector<Component*> (DEFAULT_Y, nullptr)){
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			map[i][j] = new Plain(i, j);
		}
	}
}

Map::~Map() {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			delete map[i][j];
		}
	}
}

/*
Draw each component on the map
*/
void Map::draw() {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			map[i][j]->draw();
		}
	}
}
