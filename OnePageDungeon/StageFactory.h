#pragma once

#include <SFML\Graphics.hpp>
#include "SpriteStore.h"
#include "Stage.h"

class StageFactory
{
public:
	StageFactory(SpriteStore *spriteStore, sf::Vector2u renderSize);
	~StageFactory(void);
	Stage* createTownStage(int size);

private:
	SpriteStore *spriteStore;
	sf::Vector2u *renderSize;

	int** initialise2DMatrix(int size, int defaultValue);
	int** initialiseAdjMatrix(int size,sf::Vector2<Sprite ***>* materialVector);
	(sf::Vector2<Sprite ***>*) StageFactory::initialise2DMaterialMatrix(int size, Sprite *defaultGroundSprite, Sprite *defaultHighGroundSprite);
	sf::Vector2<sf::IntRect ***>* StageFactory::initialise2DBoundingBoxMatrix(int size, sf::Vector2i origin, sf::FloatRect rect, sf::Vector2f scale);
};

