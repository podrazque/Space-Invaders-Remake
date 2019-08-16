#include "SpawnController.hpp"

void SpawnController::setup(float startTime, std::string difficultyLevel) 
{
	if(difficultyLevel == "EASY")
	{
		interval_ = 500;
	}
	else if(difficultyLevel == "MEDIUM")
	{
		interval_ = 300;
	}
	else if(difficultyLevel == "HARD")
	{
		interval_ = 100;
	}
    start_ = startTime;
}

void SpawnController::update(int score)
{
	level_ = score / 50;
	spawnSpeed_ = 3 * (level_ * 0.5f);
	spawnMultiplier_ = 1 + level_ * 0.3f;
}

//from openFrameworks tutorial on spawning
bool SpawnController::spawn() 
{
    if (ofGetElapsedTimeMillis() - start_ > interval_) 
	{
        start_ = ofGetElapsedTimeMillis();
        return true;
    }
    return false;
}