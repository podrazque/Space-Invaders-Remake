#pragma once
#include "ofMain.h"

class Enemy 
{
public:
    void setup(ofImage * enemyImage, std::string difficultyLevel);
    void update();
    void draw();
	
    ofPoint position_;
    ofImage * enemyImage_;

    float speed_;
    float amplitude_;
    float width_;
};