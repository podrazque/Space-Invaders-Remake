#include "Item.hpp"

void Item::setup(ofPoint position, ofImage * image, string itemType) 
{
    position_ = position;
    speed_ = 7;
    this->itemImage_ = image;
    width_ = 30;
	amplitude_ = 3;
	itemType_ = itemType;
}

void Item::update() 
{
        position_.y += speed_;
		position_.x += amplitude_ * cos(ofGetElapsedTimef());
}
void Item::draw() 
{
    itemImage_->draw(position_.x - width_/2, position_.y - width_/2, width_, width_);
}