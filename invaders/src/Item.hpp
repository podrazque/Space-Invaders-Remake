#pragma once
#include "ofMain.h"

class Item 
{
public:
    void setup(ofPoint position, ofImage * image, string itemType);
    void update();
    void draw();
    
    ofPoint position_;
    ofImage * itemImage_;

	float health_;
    float powerUp_;
    float width_;

    int speed_;
	int amplitude_;

    bool fromPlayer_;
	
	string itemType_;
};