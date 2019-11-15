/******************************************************
 * The class that represent each componenet on the map. Should be an "abstract" class
 * that must be implemented by a specific component subclass
 *****************************************************/


#pragma once

class Component {
public:
	/* Constants */
	static const int PIXEL_LENGTH = 20;  // the side length used for drawing

	/* Member fields */
	// define the x, y, position of the component in the map (not the pixel position)
	int px;
	int py;
	bool canLand;  // whether player can land on this component
	bool state; // for button, switch, etc. subclasses
	int ID;

	/* Functinons */
	Component(int _px, int _py, int _canLand, int _ID);
	int* getPosition();

	// define as pure virtual function because only a specific componenet can be drawed
	virtual void draw() = 0;
	virtual void update() = 0;
};
