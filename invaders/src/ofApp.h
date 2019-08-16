#pragma once

#include "ofMain.h"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "SpawnController.hpp"
#include "Item.hpp"
#include <stdlib.h>
#include <time.h>

enum GameState 
{
	IN_PROGRESS = 0,
	FINISHED,
	START
};

class ofApp : public ofBaseApp
{

	private: 

		/*---------------------Sounds------------------*/
		ofSoundPlayer song_, invaderKilledSound_, shootSound_, explosion_;
		/*--------------------------------------------*/

		/*--------------------Screens------------------------*/
		ofImage startScreen_;
		ofImage gameOverScreen_;
		ofImage heart_;
		ofImage background_;
		/*--------------------------------------------------*/

		/*--------------------Game Resources--------------------*/
		int score_;
		ofTrueTypeFont font_, fontLower_, fontTiny_;
		GameState currentState_ = START;
		string difficultyLevel_;
		/*-----------------------------------------------------*/

		/*----------------Player-------------------*/
		ofImage playerModel_; 
		Player player_;
		ofPoint playerStart_;
		/*----------------------------------------*/

		/*----------------Bullets-------------------*/
		vector<Bullet> bullets_;
		vector<ofImage> BULLET_ARRAY;
    	ofImage pew1_;
		/*------------------------------------------*/

		/*-----------------Enemies-----------------*/
		vector<Enemy> enemies_;
		vector<ofImage> ENEMY_ARRAY;
		ofImage alien1_, alien2_, alien3_;
		/*------------------------------------------*/

		/*--------------------SpawnController----------------------*/
		SpawnController spawnController_;
		/*---------------------------------------------------------*/

		/*-------------------Items---------------------*/
		vector<Item> items_;
		vector<ofImage> ITEM_ARRAY;
		ofImage healthPack_, mysteryPack_;		
		/*--------------------------------------------*/


	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void updateBullets();
		void updateItems();

		void loadSounds();
		void loadModels();
		void loadBulletModels();
		void createBulletVector();

		void bulletCollision();
		void enemyCollision();
		void itemCollision();
		
		void drawScore();
		void drawLives();

		void drawMe();

		/*-----------------Not currrently used------------------*/	
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		/*----------------------------------------------------*/
		

};
