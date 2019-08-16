#include "ofMain.h"
class Bullet 
{
public:
    void setup(ofPoint position, float speed, ofImage * bulletImage);
    void update();
    void draw();

    ofPoint position_;
    ofImage * bulletImage_;

    float speed_;
    float width_, height_;
    float speedX_;
};