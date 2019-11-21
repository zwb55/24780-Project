#pragma once
#include <string>
#include "DrawingUtilNG.h"
#include "ysglfontdata.h"
#include "GraphicFont.h"
#include "fssimplewindow.h"
using namespace std;

class TeachingKey
{
private:
	double locX, locY;
	int width;
	int height;
	double gapX, gapY;  // the gap between text and frame
	double scale; // size of string
	string text;
	//ComicSansFont comicsans;
public:
	TeachingKey();
	TeachingKey(double _locX, double _locY, double _gapX, double _gapY,int _width, int _height, double _scale,const string _text);
	void draw(ComicSansFont& comicsans);
	string gettext();
	bool isPressed;
	
};

//TeachingKey::TeachingKey()
//{
//
//}
