#pragma once

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>

#include "ofMain.h"

class Player 
{
public:
    void setup(ofImage * img);
    void update();
    void draw();
	void reset(std::string difficultyLevel);

    ofPoint position_;
    ofImage * img_;

    int lives_;
	int level_;

	double speed_, width_;
	float movement_;
    
    bool leftPressed_, rightPressed_;
	bool upPressed_, downPressed_;
};


#endif