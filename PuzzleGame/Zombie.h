#pragma once
#include "Player.h"
#include <vector>
#include <chrono>

class Zombie : public Player {
public:
	
	double MOVE_SPEED = 0.4;
	
	int startX;
	int startY;
	
	// define the current position on in the space
	double spaceX;
	double spaceY;
	
	int endX;
	int endY;
	
	// direciton of movement
	int dirCode;
	int dirX;
	int dirY;
	
	clock_t begin_time = clock();
	
	/* Functions */
	Zombie(int _gridX, int _gridY, int direction);
	void setDireciton(int code);
	std::pair<int,int>getPosition();
	void flipDirection();
	void move(bool valid);
	void draw();
	
};
