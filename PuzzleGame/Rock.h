#pragma once
/*
Define the Rock in the game.
*/

class Rock {
public:
	/* Constants */
	static const int MOVE_SPEED = 2;

	/* Member fields */
	// define the current position on the grid
	int gridX;
	int gridY;

	// define the current position on in the space
	int spaceX;
	int spaceY;

	/* Functions */
	Rock(int _gridX, int _gridY);

	void setPosition(int _gridX, int _gridY);
	int* getPosition();
	void move();
	void draw();
};
