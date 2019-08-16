#include "Enemy.hpp"

void Enemy::setup(ofImage * enemyImage, std::string difficultyLevel) 
{
    position_.x = ofRandom(ofGetWidth());
    position_.y = 0;
    enemyImage_ = enemyImage;
    width_ = 40;
	if(difficultyLevel == "EASY")
	{
		this->speed_ = ofRandom(1, 7);
		amplitude_ = ofRandom(1, 3);
	}
	else if(difficultyLevel == "MEDIUM")
	{
		this->speed_ = ofRandom(4, 10);
		amplitude_ = ofRandom(2, 5);
	}
	else if(difficultyLevel == "HARD")
	{
		this->speed_ = ofRandom(6, 13);
		amplitude_ = ofRandom(4, 7);
	}
}

void Enemy::update() 
{
    position_.y += speed_;
    position_.x += amplitude_ * cos(ofGetElapsedTimef());
}
void Enemy::draw() 
{
    enemyImage_->draw(position_.x - width_/2, position_.y - width_/2, width_, width_);
}