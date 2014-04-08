#pragma once
#include <SFML\Graphics.hpp>
#include "SpriteNames.h"

class Sprite :
	public sf::Sprite
{
public:
	Sprite(void);
	Sprite(sf::Texture &texture);
	Sprite(sf::Texture &texture, sf::IntRect &rect);
	~Sprite(void);
	int GetSpriteNumber();
	void SetSpriteNumber(int a);

private:
	int spriteNumber;
};

