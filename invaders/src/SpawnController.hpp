#pragma once
#include "ofMain.h"

class SpawnController 
{
public:
    void setup(float time, std::string difficultyLevel);
    bool spawn();
	void update(int score);

    float start_;
    float interval_;
	float spawnMultiplier_;
	
    int level_;
	int spawnSpeed_;
};