#include "Sprite.h"

Sprite::Sprite(void)
	: sf::Sprite()
{
}

Sprite::Sprite(sf::Texture &texture) 
	: sf::Sprite(texture)
{
}

Sprite::Sprite(sf::Texture &texture, sf::IntRect &rect) 
	: sf::Sprite(texture, rect)
{
}

Sprite::~Sprite(void)
{
}

int Sprite::GetSpriteNumber()
{
	return this->spriteNumber;
}

void Sprite::SetSpriteNumber(int spriteNumber)
{
	this->spriteNumber = spriteNumber;
}
