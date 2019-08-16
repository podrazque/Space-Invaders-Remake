#include "ofApp.h"

void ofApp::setup()
{
	ofSetWindowTitle("Space Invaders 2.0");

	/*----------------sound assets------------------------*/
	song_.load("sounds/song.mp3");
	invaderKilledSound_.load("sounds/invaderkilled.wav");
	shootSound_.load("sounds/shoot.wav");
	explosion_.load("sounds/explosion.wav");
	/*----------------------------------------------------*/
	/*
	derived font loading from here:
	https://www.youtube.com/watch?v=dzbJibA3vhc
	*/
	/*------------------logo & startscreen----------------------*/
	startScreen_.load("images/StartScreen.png");
	font_.load("04B_30__.TTF", 30);
	fontLower_.load("04B_30__.TTF", 15);
	fontTiny_.load("04B_30__.TTF", 10);
	heart_.load("images/heart.png");
	gameOverScreen_.load("images/EndScreen.png");
	background_.load("images/background.jpg");
	/*--------------------------------------------*/

	/*------------character models------------*/
	playerModel_.load("images/Spaceship.png");
	player_.setup(&playerModel_);
	alien1_.load("images/invader.png");
	alien2_.load("images/Alien2.png");
	alien3_.load("images/Alien3.png");

	/*----------------------------------------*/

	/*---------bullet assets------------*/
	pew1_.load("images/pew.png");
	/*-----------------------------------*/

	/*---------item assets------------*/
	mysteryPack_.load("images/mysterypack.png");
	healthPack_.load("images/healthPack.png");
	/*-----------------------------------*/
	

	BULLET_ARRAY.push_back(pew1_);

	ENEMY_ARRAY.push_back(alien1_);
	ENEMY_ARRAY.push_back(alien2_);
	ENEMY_ARRAY.push_back(alien3_);

	ITEM_ARRAY.push_back(mysteryPack_);
	ITEM_ARRAY.push_back(healthPack_);

	score_ = 0;

	bullets_.clear();
	enemies_.clear();
	items_.clear();
	song_.play();
}

void ofApp::update(){
	if(currentState_ == IN_PROGRESS)
	{
		player_.update();
		updateBullets();
		updateItems();
		enemyCollision();
		itemCollision();
		spawnController_.update(score_);
		for(int i = 0; i < enemies_.size(); i++)
		{
			enemies_[i].update();
		}
		if(spawnController_.spawn())
		{
			int max = MIN(spawnController_.spawnMultiplier_, 6);
			for(int i = 0; i < max; i++)
			{

				/*Random derived from here:
				http://www.cplusplus.com/forum/beginner/26611/*/
				Enemy enemy;
				int randomIndex = rand() % 3;
				enemy.setup(&ENEMY_ARRAY[randomIndex], difficultyLevel_);
				enemies_.push_back(enemy);
			}
		}
		
	}
}

void ofApp::draw(){
	if(currentState_ == START)
	{
		startScreen_.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
	else if(currentState_ == IN_PROGRESS)
	{	
		/*
		changing screen derived from
		https://books.google.com/books?id=WRr2AAAAQBAJ&pg=PT81&lpg=PT81&dq=openframeworks+how+to+make+background+pulsate&source=bl&ots=9ol9ts72n7&sig=c1u5u_6bfaRQ3KzdA3fMITp56Lk&hl=pl&sa=X&ved=2ahUKEwiZgZGf4Z3fAhVK_IMKHRPWBy8Q6AEwAHoECAcQAQ#v=onepage&q=openframeworks%20how%20to%20make%20background%20pulsate&f=false
		*/
		if(difficultyLevel_ == "HARD")
		{
			float time = ofGetElapsedTimef();
			float value = sin(time * M_TWO_PI);
			float v = ofMap(value, -1, 1, 0, 255);
			ofBackground(v,v,v);
		}
		else ofBackground(0, 0, 100);
		player_.draw();
		drawScore();
		drawLives();
		drawMe();
		for(int i = 0; i < bullets_.size(); i++) 
		{
            bullets_[i].draw();
        }

		for(int i = 0; i < enemies_.size(); i++) 
		{
            enemies_[i].draw();
        }
		for(int i = 0; i < items_.size(); i++)
		{
			items_[i].draw();
		}
	}
	else if(currentState_ == FINISHED)
	{
		gameOverScreen_.draw(0, 0, ofGetWidth(), ofGetHeight());
		drawScore();
	}
}

void ofApp::keyPressed(int key)
{
	if(currentState_ == IN_PROGRESS)
	{
		if (key == OF_KEY_F12) 
		{
			ofToggleFullscreen();
			return;
		}

		if(key == OF_KEY_LEFT) player_.leftPressed_ = true;
		if(key == OF_KEY_RIGHT) player_.rightPressed_ = true;
		if(key == OF_KEY_UP) player_.upPressed_ = true;
		if(key == OF_KEY_DOWN) player_.downPressed_ = true;

		if (key == ' ') 
		{
			shootSound_.play();
            int max = MIN(player_.level_ / 3 + 1, 5);
            for(int i = 0; i < max; ++i) 
			{

                Bullet bullet;
                ofPoint positionOfBullet;


                positionOfBullet.x = player_.position_.x + (i - max/2) * 20;
                positionOfBullet.y = player_.position_.y;
            

                bullet.setup(positionOfBullet, player_.speed_, &BULLET_ARRAY[0]);
                bullet.speedX_ = (i-max/2) / 2;
                bullets_.push_back(bullet);
            }
        }
	}
}

void ofApp::updateBullets() 
{
    for(int i=0;i<bullets_.size();i++) // for each
	{
        bullets_[i].update();
        if (bullets_[i].position_.x - bullets_[i].width_ / 2 < 0 || bullets_[i].position_.y + bullets_[i].width_/2 > ofGetHeight()) 
		{
            bullets_.erase(bullets_.begin()+i);
        }
    }
	bulletCollision();
}

void ofApp::updateItems() 
{
    for(int i=0;i<items_.size();i++) 
	{
        items_[i].update();
        if (items_[i].position_.x - items_[i].width_/2 < 0 || items_[i].position_.y + items_[i].width_/2 > ofGetHeight())
		{
            items_.erase(items_.begin()+i);
        }
    }
}

void ofApp::keyReleased(int key)
{	
	if(currentState_ == START)
	{
		if(key == 'e' || key == 'E')
		{
			currentState_ = IN_PROGRESS;
			difficultyLevel_ = "EASY";
		}
		else if(key == 'm' || key == 'M')
		{
			currentState_ = IN_PROGRESS;
			difficultyLevel_ = "MEDIUM";
		}
		else if(key == 'h' || key == 'H')
		{
			currentState_ = IN_PROGRESS;
			difficultyLevel_ = "HARD";
		}
		score_ = 0;
		bullets_.clear();
		enemies_.clear();
		player_.reset(difficultyLevel_);
		items_.clear();
		spawnController_.setup(ofGetElapsedTimeMillis(), difficultyLevel_);
	}
	else if(currentState_ == IN_PROGRESS)
	{
		if(key == OF_KEY_LEFT) player_.leftPressed_ = false;
		if(key == OF_KEY_RIGHT) player_.rightPressed_ = false;
		if(key == OF_KEY_UP) player_.upPressed_ = false;
		if(key == OF_KEY_DOWN) player_.downPressed_ = false;
		if(key == 'q' || key == 'Q') currentState_ = FINISHED;
	}
	else if(currentState_ == FINISHED)
	{
		if(key == ' ')
		{
			currentState_ = START;
		}
	}
}

void ofApp::bulletCollision()
{
	for (int i = 0; i < bullets_.size(); i++) 
	{
		for (int e = enemies_.size() - 1; e >= 0; e--) 
		{
			//checks for collision
			if (ofDist(bullets_[i].position_.x, bullets_[i].position_.y,
			enemies_[e].position_.x, enemies_[e].position_.y) < 
			(enemies_[e].width_ + bullets_[i].width_)/2) 
			{
				invaderKilledSound_.play();
				enemies_.erase(enemies_.begin()+e);
				bullets_.erase(bullets_.begin()+i);
				--i;
				score_ += 5;
				// my friend helped me with figuring out how to make enemies drop items
				if(ofRandom(0, 50 + player_.level_) > 40 + player_.level_)
				{
					Item i;
					if(player_.lives_ >= 3) //only spawns bullet upgrades if lives >= 3
					{
						i.setup(enemies_[e].position_, &ITEM_ARRAY[0], "mystery");
							items_.push_back(i);
					}
					else if(player_.lives_ < 3)//only spawns healthpacks or "insta deaths" if lives < 3
					{
						int index = rand() % 2;
						if(index == 1) 
						{
							i.setup(enemies_[e].position_, &ITEM_ARRAY[1], "health");
							items_.push_back(i);
						}
						else if(index == 0)
						{
							i.setup(enemies_[e].position_, &ITEM_ARRAY[0], "death");
							items_.push_back(i);
						}
					}
				}
			}
		}
        
    }
}

void ofApp::enemyCollision()
{
	for(int i = 0; i < enemies_.size(); i++)
	{
		//checks for collision
		if(ofDist(enemies_[i].position_.x, enemies_[i].position_.y, 
		player_.position_.x, player_.position_.y) <
		(enemies_[i].width_ + player_.width_/2))
		{	
			enemies_.erase(enemies_.begin() + i);
			player_.lives_--;

			//checks for death
			if(player_.lives_ <= 0)
			{
				explosion_.play();
				currentState_ = FINISHED;
			}
		}
	}
}

void ofApp::itemCollision()
{
	int maxBullets = 7;
	for(int i = 0; i < items_.size(); i++)
	{
		//checks for collision
		if(ofDist(items_[i].position_.x, items_[i].position_.y, 
		player_.position_.x, player_.position_.y) <
		(items_[i].width_ + player_.width_/2))
		{
			items_.erase(items_.begin() + i);

			if(items_[i].itemType_ == "health")
			{
				player_.lives_++;
			}
			else if(items_[i].itemType_ == "mystery")
			{
				for(int j = 0; j < maxBullets; j++)
				{
					int j = 100;
					Bullet bullet;
					ofPoint position;
					position.x = player_.position_.x + (j - maxBullets / 2) * 15;
					position.y = player_.position_.y;
					bullet.setup(position, player_.speed_ * 2, &BULLET_ARRAY[0]);
					bullet.speedX_ -= (j - maxBullets / 2) / 2;
					bullets_.push_back(bullet);
				}
			}
			else if(items_[i].itemType_ == "death")
			{
				for(int k = 0; k < enemies_.size(); k++)
				{
					enemies_.erase(enemies_.begin() + k);
				}
			}
		}
	}
}

/*
displaying text derived from
https://www.youtube.com/watch?v=lYlTKN2G6G8
*/
void ofApp::drawScore()
{	
	if(currentState_ == IN_PROGRESS)
	{
		fontLower_.drawString(ofToString("Score: "), 30, 50);
		font_.drawString(ofToString(score_), 125, 50);
		fontLower_.drawString(ofToString("Level: "), 30, 80);
		fontLower_.drawString(ofToString(spawnController_.level_), 125, 80);
	}
	if(currentState_ == FINISHED)
	{
		font_.drawString(ofToString(score_), ofGetWidth()/2, 450);
	}
}

void ofApp::drawMe()
{
	fontTiny_.drawString(ofToString("Made by: podrazque"), ofGetWidth() - 210, ofGetHeight()- 15);
}

void ofApp::drawLives()
{
	for(int i = 0; i < player_.lives_; i++)
	{
		heart_.draw(ofGetWidth() - (i*50) - 60, 20, 20, 20);
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
