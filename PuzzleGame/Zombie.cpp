#include "Zombie.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"
#include "Component.h"
#include <chrono>
#include <iostream>

// ...


Zombie::Zombie(int _gridX, int _gridY, int direction): Player(_gridX, _gridY) {
	spaceX = gridX * Component::PIXEL_LENGTH;
	spaceY = gridY * Component::PIXEL_LENGTH;
	setDireciton(direction);
}

std::pair<int, int>Zombie::getPosition(){
	return std::pair<int,int>{gridX,gridY};
}

void Zombie::setDireciton(int code) {
	dirCode = code;
	switch (code) {
		case 1:
			face = 1;
			dirX = 0; dirY = 1;
			break;
		case 3:
			face = 3;
			dirX = 0; dirY = -1;
			break;
		case 2:
			face = 2;
			dirX = 1; dirY = 0;
			break;
		case 4:
			face = 4;
			dirX = -1; dirY = 0;
			break;
	}
}

void Zombie::flipDirection() {
	switch (dirCode) {
		case 1:
			if (temp % 80 < 20)
				setDireciton(4);
			break;
		case 3:
			if ((temp % 80 >= 40) && (temp % 80 < 60))
				setDireciton(2);
			break;
		case 2:
			if (temp % 80 > 60)
				setDireciton(1);
			break;
		case 4:
			if ((temp % 80 >= 20) && (temp % 80 < 40))
				setDireciton(3);
			break;
	}
}


void Zombie::move(bool valid) {

	
	
	// do something
	float dur = 10 * float( clock () - begin_time ) /  CLOCKS_PER_SEC;
	if (dur < 3) {
		return;
	}
	
	
	
	if (gridX * Component::PIXEL_LENGTH < (int)spaceX) {
		spaceX -= MOVE_SPEED;
		isMoving = true;
	}
	else if (gridX * Component::PIXEL_LENGTH > (int)spaceX) {
		spaceX += MOVE_SPEED;
		isMoving = true;
	}
	else if (gridY * Component::PIXEL_LENGTH < (int)spaceY) {
		spaceY -= MOVE_SPEED;
		isMoving = true;
	}
	else if (gridY * Component::PIXEL_LENGTH > (int)spaceY) {
		spaceY += MOVE_SPEED;
		isMoving = true;
	}
	else {
		isMoving = false;
	}
	
	if (!valid && !isMoving) {
		flipDirection();
		return;
	}
	
	if (!isMoving) {
		setPosition(gridX + dirX, gridY + dirY);
		begin_time = clock();
	}
	
}

void Zombie::draw() {
	if(gridX>=0){
	//DrawingUtilNG::drawCube(spaceX, spaceY, 0, spaceX + Component::PIXEL_LENGTH, spaceY + Component::PIXEL_LENGTH, 20, true);
	temp += 1;
	glPushMatrix();
	if (temp % 60 < 30) {
		glTranslated(spaceX + 0.5 * Component::PIXEL_LENGTH, spaceY + 0.5 * Component::PIXEL_LENGTH, 0);
	}
	else {
		glTranslated(spaceX + 0.5 * Component::PIXEL_LENGTH, spaceY + 0.5 * Component::PIXEL_LENGTH, -0.03 * Component::PIXEL_LENGTH);
	}
	if (face == 1)
		theta = 0;
	if (face == 3)
		theta = 180;
	if (face == 4)
		theta = 90;
	if (face == 2)
		theta = 270;
	glRotated(theta, 0, 0, 1);
	//head
	glColor3ub(0, 0, 150);
	DrawingUtilNG::drawCube(-0.2 * Component::PIXEL_LENGTH, -0.2 * Component::PIXEL_LENGTH, 0.8 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 1.05 * Component::PIXEL_LENGTH, false);
	//body
	glColor3ub(0, 0, 95);
	DrawingUtilNG::drawCube(-0.2 * Component::PIXEL_LENGTH, -0.2 * Component::PIXEL_LENGTH, 0.35 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 0.75 * Component::PIXEL_LENGTH, false);
	//face
	glColor3ub(0, 0, 0);
	DrawingUtilNG::drawCube(-0.15 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 0.85 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0.25 * Component::PIXEL_LENGTH, 0.95 * Component::PIXEL_LENGTH, false);
	DrawingUtilNG::drawCube(0.05 * Component::PIXEL_LENGTH, 0.2 * Component::PIXEL_LENGTH, 0.85 * Component::PIXEL_LENGTH, 0.15 * Component::PIXEL_LENGTH, 0.25 * Component::PIXEL_LENGTH, 0.95 * Component::PIXEL_LENGTH, false);
	glColor3ub(50, 50, 150);
	//arms and legs
	if (!isMoving) {
		DrawingUtilNG::drawCube(-0.3 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0.45 * Component::PIXEL_LENGTH, -0.2 * Component::PIXEL_LENGTH, 0.05 * Component::PIXEL_LENGTH, 0.7 * Component::PIXEL_LENGTH, false);
		DrawingUtilNG::drawCube(0.2 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0.45 * Component::PIXEL_LENGTH, 0.3 * Component::PIXEL_LENGTH, 0.05 * Component::PIXEL_LENGTH, 0.7 * Component::PIXEL_LENGTH, false);
		
		DrawingUtilNG::drawCube(-0.15 * Component::PIXEL_LENGTH, -0.07 * Component::PIXEL_LENGTH, 0, -0.05 * Component::PIXEL_LENGTH, 0.07 * Component::PIXEL_LENGTH, 0.35 * Component::PIXEL_LENGTH, false);
		DrawingUtilNG::drawCube(0.05 * Component::PIXEL_LENGTH, -0.07 * Component::PIXEL_LENGTH, 0, 0.15 * Component::PIXEL_LENGTH, 0.07 * Component::PIXEL_LENGTH, 0.35 * Component::PIXEL_LENGTH, false);
		glPopMatrix();
	}
	else {
		glTranslated(0, 0, 0.72 * Component::PIXEL_LENGTH);
		if (temp % 50 < 25) {
			DrawingUtilNG::drawCube(0.05 * Component::PIXEL_LENGTH, 0.03 * Component::PIXEL_LENGTH, -0.65 * Component::PIXEL_LENGTH, 0.15 * Component::PIXEL_LENGTH, 0.17 * Component::PIXEL_LENGTH, -0.3 * Component::PIXEL_LENGTH, false);
			DrawingUtilNG::drawCube(-0.15 * Component::PIXEL_LENGTH, -0.17 * Component::PIXEL_LENGTH, -0.65 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, -0.03 * Component::PIXEL_LENGTH, -0.3 * Component::PIXEL_LENGTH, false);
			glRotated(30, 1, 0, 0);
			DrawingUtilNG::drawCube(-0.3 * Component::PIXEL_LENGTH, 0.05 * Component::PIXEL_LENGTH, -0.25 * Component::PIXEL_LENGTH, -0.2 * Component::PIXEL_LENGTH, 0.15 * Component::PIXEL_LENGTH, 0, false);
			glRotated(-60, 1, 0, 0);
			DrawingUtilNG::drawCube(0.2 * Component::PIXEL_LENGTH, -0.15 * Component::PIXEL_LENGTH, -0.25 * Component::PIXEL_LENGTH, 0.3 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0, false);
			glPopMatrix();
		}
		else if (temp % 50 >= 25) {
			DrawingUtilNG::drawCube(-0.15 * Component::PIXEL_LENGTH, 0.03 * Component::PIXEL_LENGTH, -0.65 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0.17 * Component::PIXEL_LENGTH, -0.3 * Component::PIXEL_LENGTH, false);
			DrawingUtilNG::drawCube(0.05 * Component::PIXEL_LENGTH, -0.17 * Component::PIXEL_LENGTH, -0.65 * Component::PIXEL_LENGTH, 0.15 * Component::PIXEL_LENGTH, -0.03 * Component::PIXEL_LENGTH, -0.3 * Component::PIXEL_LENGTH, false);
			glRotated(-30, 1, 0, 0);
			DrawingUtilNG::drawCube(-0.3 * Component::PIXEL_LENGTH, -0.15 * Component::PIXEL_LENGTH, -0.25 * Component::PIXEL_LENGTH, -0.2 * Component::PIXEL_LENGTH, -0.05 * Component::PIXEL_LENGTH, 0, false);
			glRotated(60, 1, 0, 0);
			DrawingUtilNG::drawCube(0.2 * Component::PIXEL_LENGTH, 0.05 * Component::PIXEL_LENGTH, -0.25 * Component::PIXEL_LENGTH, 0.3 * Component::PIXEL_LENGTH, 0.15 * Component::PIXEL_LENGTH, 0, false);
			glPopMatrix();
		}
	}
	}
}
