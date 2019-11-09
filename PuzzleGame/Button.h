/*****************************************************
 * The class defines a button which can be pressed on
 * the map if stepped on.
 *****************************************************/

#pragma once
#include "Component.h"
#include <vector>

class Button : public Component {
public:
    
    /* Functions */
    Button(int _px, int _py);
    void update(std::vector<int*> objectInds);
    void draw();
    
private:
    /* Member fields */
    std::vector<int> color{0, 0, 0};
    bool open;
};
