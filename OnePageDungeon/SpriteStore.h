#pragma once

#include <SFML\Graphics.hpp>
#include "Sprite.h"

class SpriteStore
{
public:
	SpriteStore(sf::Texture *tilesheetTexture);
	~SpriteStore(void);

	Sprite *getStoneBlock();
	Sprite *getStoneRampLeft();
	Sprite *getStoneRampRight();
	Sprite *getStoneRampTop();
	Sprite *getStoneRampBottom();
	Sprite *getPlayer();
	Sprite *getStoneBlockTall();

private:
	Sprite *stoneBlock;
	Sprite *stoneRampLeft;
	Sprite *stoneRampRight;
	Sprite *stoneRampTop;
	Sprite *stoneRampBottom;
	Sprite *player;
	Sprite *stoneBlockTall;
};

