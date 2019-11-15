#include "Component.h"

Component::Component(int _px, int _py, int _canLand, char _ID) {
	px = _px;
	py = _py;
	ID = _ID;
	canLand = _canLand;
}

int* Component::getPosition() {
	int* loc = new int[2];
	loc[0] = px; loc[1] = py;
	return loc;
}
