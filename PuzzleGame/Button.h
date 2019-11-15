/*****************************************************
 * The class defines a button which can be pressed on
 * the map if stepped on.
 *****************************************************/

#pragma once
#include "Component.h"
#include "Door.h"
#include <vector>

class Button : public Component {
public:
    
    /* Functions */
    Button(int _px, int _py, int _doorx, int _doory);
    void draw();
	void update();
	int* corrDoor
    
private:
    /* Member fields */
    std::vector<int> color{0, 0, 0};
};
