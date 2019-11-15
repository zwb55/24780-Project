/******************************************************
 * The controller of each level of the game, handles the operation from user (player movement)
 * and update corresponding position and result, and draw all the scene.
 *****************************************************/

#pragma once
#include "Map.h"
#include "Player.h"
#include "Rock.h"
#include <vector>

class Controller {
public:
	/* Functions */
	Controller();
	Controller(int _level);

	void update(int code);
	std::pair<int, int> getCenter();
	void updateObjectInds();
	void draw();

private:
	/* Member fields */
	Map map;
	Player player;
	std::vector<Rock> Rocks;

	// define the current level of the game, each level will have a separate controller
	int level;

	/* Functions */
	bool isAvailable();

};
