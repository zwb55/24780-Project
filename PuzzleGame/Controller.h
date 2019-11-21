/******************************************************
 * The controller of each level of the game, handles the operation from user (player movement)
 * and update corresponding position and result, and draw all the scene.
 *****************************************************/

#pragma once
#include "Map.h"
#include "Player.h"
#include "Rock.h"
#include "Teaching.h"
#include <vector>

using namespace std;

class Controller {
public:
	/* Functions */
	Controller();
	Controller(int _level);

	void update(int code);
	std::pair<int, int> getCenter();
	void updateObjectInds();
	void draw();
	void draw2D();
	bool isObstacle(vector<pair<int, int>> pos, int intend_x, int intend_y);
	bool pass();
	void setkeypressed(int i);
	int getcurrLevel() { return level; }
private:
	/* Member fields */
	Map map;
	Player player;

	/*
	used in the first level
	0: W    turn red to green when W is pressed
	1: A    ...
	2: S    ...
	3: D    ...
	4: <-   ...
	5: ->   ...
	6: Button   turn red to green when Button is stepped on
	7: SPACE    turn red to green when SPACE is pressed
	*/
	vector<TeachingKey> Keys;
	ComicSansFont comicsans;  // the text of the keys



	std::vector<Rock> Rocks;
	// pos records all the positions of rocks. May contains zombies later...
	vector<pair<int, int>> pos;

	// define the current level of the game, each level will have a separate controller
	int level;

	/* Functions */
	bool isAvailable();

};
