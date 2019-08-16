#include "Player.hpp"
#include "ofApp.h"

void Player::setup(ofImage * image)
{
	img_ = image;
	position_.x = 100;
	position_.y = ofGetHeight() - 100;
	width_ = 50;
}

void Player::reset(string difficultyLevel)
{
	speed_ = 5;
	if(difficultyLevel == "EASY") lives_ = 5;
	else if(difficultyLevel == "MEDIUM") lives_ = 4;
	else if(difficultyLevel == "HARD") lives_ = 3;
	level_ = 0;
	leftPressed_ = false;
	rightPressed_ = false;
	upPressed_ = false;
	downPressed_ = false;
}

void Player::update()
{
	if(leftPressed_) position_.x -= speed_;
	if(rightPressed_) position_.x += speed_;
	if(upPressed_) position_.y -= speed_;
	if(downPressed_) position_.y += speed_;
}

void Player::draw()
{
	img_->draw(position_.x - width_/2, position_.y - width_/2, width_, width_);
}

