#include "Bullet.hpp"

void Bullet::setup(ofPoint position, float speed, ofImage * bulletImage) 
{
    position_ = position;
    speed_ = speed + 4;
    speedX_ = 0;
    bulletImage_ = bulletImage;
    width_ = 10;
	height_ = 20;
}

void Bullet::update() 
{
    position_.y -= speed_;
    position_.x -= speedX_;
}
void Bullet::draw() 
{
    bulletImage_->draw(position_.x - width_/2, position_.y - height_/2, width_, height_);
}