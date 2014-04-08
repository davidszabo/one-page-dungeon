#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Logger.h"
#include "dbtweener.h"
#include "Stage.h"
#include "StageFactory.h"

class Player
{

public:

	Player(Sprite *sprite, float positionX,float positionY,Stage *stage);
	~Player(void);
	void setPositions();
	float* getX();
	float* getY();
	void Update();
	void Draw(sf::RenderWindow &Gamewindow);
	void MoveTo(std::vector<sf::Vector2f> fDestination,float Time,std::vector<bool> isHigh);

	sf::Vector2i playerIndex;
	Sprite *playerSprite;
	bool isMoving;
	bool firstLayer;
	

private: 
	void Move();
	float MoveTime;
	float x;
	float y;
	Stage *thestage;
	Logger *logger;
	CDBTweener oTweener;
	std::vector<sf::Vector2f> Destination;
	std::vector<bool> isHigh;
};

