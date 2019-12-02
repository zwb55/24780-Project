#include "Teaching.h"
#include <iostream>
TeachingKey::TeachingKey()
{
	return;
}
TeachingKey::TeachingKey(double _locX, double _locY, double _gapX, double _gapY, int _width, int _height, double _scale, const string _text)
{
	locX = _locX;
	locY = _locY;
	width = _width;
	height = _height;
	gapX = _gapX;
	gapY = _gapY;
	scale = _scale;
	text = _text;
	isPressed = false;
}

void TeachingKey::draw(ComicSansFont& comicsans)
{
	comicsans.setColorHSV(200, 1, 1);

	if (!isPressed)
	{
		glColor3ub(238, 44, 44);
	}
	else
	{
		glColor3ub(50, 205, 50);
	}
	glLineWidth(2);
	DrawingUtilNG::drawRectangle(locX, locY, width, height, false);
	comicsans.setColorRGB(255, 255, 255);
	comicsans.drawText(text, locX + gapX, locY + gapY, scale, 0);
}

string TeachingKey::gettext()
{
	return text;
}
