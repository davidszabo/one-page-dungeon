#include "SpriteStore.h"


SpriteStore::SpriteStore(sf::Texture *tilesheetTexture)
{
	stoneBlock = new Sprite(*tilesheetTexture, sf::IntRect(0, 0, 16, 16));
	stoneBlock->setPosition(0.f, 0.f);
	stoneBlock->SetSpriteNumber(STONE_BLOCK);
	stoneBlock->setScale(3.f, 3.f);

	stoneRampLeft = new Sprite(*tilesheetTexture, sf::IntRect(64, 0, 16, 16));
	stoneRampLeft->setPosition(0.f, 0.f);
	stoneRampLeft->SetSpriteNumber(STONE_RAMP_LEFT);
	stoneRampLeft->setScale(3.f, 3.f);

	stoneRampRight = new Sprite(*tilesheetTexture, sf::IntRect(80, 0, -16, 16));
	stoneRampRight->setPosition(0.f, 0.f);
	stoneRampRight->SetSpriteNumber(STONE_RAMP_RIGHT);
	stoneRampRight->setScale(3.f, 3.f);

	stoneRampTop = new Sprite(*tilesheetTexture, sf::IntRect(96, 0, 16, 16));
	stoneRampTop->setPosition(0.f, 0.f);
	stoneRampTop->SetSpriteNumber(STONE_RAMP_TOP);
	stoneRampTop->setScale(3.f, 3.f);

	stoneRampBottom = new Sprite(*tilesheetTexture, sf::IntRect(80, 0, 16, 16));
	stoneRampBottom->setPosition(0.f, 0.f);
	stoneRampBottom->SetSpriteNumber(STONE_RAMP_BOTTOM);
	stoneRampBottom->setScale(3.f, 3.f);

	player = new Sprite(*tilesheetTexture, sf::IntRect(32, 0, 16, 16));
	player->setPosition(0.f, 0.f);
	player->SetSpriteNumber(PLAYER);
	player->setScale(3.f, 3.f);

	stoneBlockTall = new Sprite(*tilesheetTexture, sf::IntRect(16, 0, 16, 16));
	stoneBlockTall->setPosition(0.f, 0.f);
	stoneBlockTall->SetSpriteNumber(STONE_BLOCK_TALL);
	stoneBlockTall->setScale(3.f, 3.f);
}

SpriteStore::~SpriteStore(void)
{
	delete stoneBlock;
	delete stoneRampLeft;
	delete stoneRampRight;
	delete stoneRampTop;
	delete stoneRampBottom;
	delete player;
}

Sprite* SpriteStore::getStoneBlock()
{
	return stoneBlock;
}

Sprite* SpriteStore::getStoneRampLeft()
{
	return stoneRampLeft;
}

Sprite* SpriteStore::getStoneRampRight()
{
	return stoneRampRight;
}

Sprite* SpriteStore::getStoneRampTop()
{
	return stoneRampTop;
}

Sprite* SpriteStore::getStoneRampBottom()
{
	return stoneRampBottom;
}

Sprite* SpriteStore::getPlayer()
{
	return player;
}

Sprite* SpriteStore::getStoneBlockTall()
{
	return stoneBlockTall;
}
