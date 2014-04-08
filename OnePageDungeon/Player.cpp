#include "Player.h"
Player::Player(Sprite *sprite, float positionX,float positionY,Stage *stage)
{	
	logger = new Logger("Player");

	thestage = stage;
	playerSprite = sprite;
	playerSprite->setPosition(positionX, positionY);
	
	firstLayer = true;

	x = positionX;
	y = positionY;

	playerIndex = sf::Vector2i(0, 0);

	isMoving = false;
}

Player::~Player(void)
{
	delete logger;
}

float* Player::getX()
{
	return &x;
}

float* Player::getY()
{
	return &y;
}

void Player::setPositions()
{
	playerSprite->setPosition(x, y);
}

void Player::MoveTo(std::vector<sf::Vector2f> fDestination,float Time,std::vector<bool> isHigh)
{
	if(isMoving == false)
	{
		CDBTweener::CTween *pTween = new CDBTweener::CTween();
		pTween->setEquation(&CDBTweener::TWEQ_LINEAR, CDBTweener::TWEA_OUT, Time);
		pTween->addValue(&x, fDestination[0].x);
		pTween->addValue(&y, fDestination[0].y);
		if(isHigh[0])
		{
			firstLayer = !isHigh[0];
		}
		oTweener.addTween(pTween);
		isMoving = true;
		Destination = fDestination;
		this->isHigh = isHigh;
		MoveTime = Time;
		logger->log("The Player started moving");
	}
	else
	{
		logger->log("The Player is already moving");
	}
}

void Player::Move()
{
	if(isMoving)
	{
		oTweener.step(20.0f * 0.001f);
		setPositions();
		if(Destination[0] == playerSprite->getPosition())
		{
			if(Destination.size() == 1)
			{
				std::cout << "Destination.x: " << Destination[0].x << " Destination.y: " << Destination[0].y << std::endl;
				std::cout << "playerIndex.x: " << playerIndex.x << " playerIndex.y: " << playerIndex.y << std::endl;
				Destination.clear();
				firstLayer = !isHigh[0];
				isHigh.clear();
				isMoving = false;
			    logger->logWARN("The Player reached the destination.");
			}
			else
			{
				Destination.erase(Destination.begin());
				firstLayer = !isHigh[0];
				isHigh.erase(isHigh.begin());
				CDBTweener::CTween *pTween = new CDBTweener::CTween();
				pTween->setEquation(&CDBTweener::TWEQ_LINEAR, CDBTweener::TWEA_OUT, MoveTime);
				pTween->addValue(&x, Destination[0].x);
				pTween->addValue(&y, Destination[0].y);
				if(isHigh[0])
				{
					firstLayer = !isHigh[0];
				}
				oTweener.addTween(pTween);			
			}

		}
	}
}

void Player::Update()
{
	Move();
}

void Player::Draw(sf::RenderWindow &gameWindow)
{
	gameWindow.draw(*playerSprite);
}