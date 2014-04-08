#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.h"
#include "Player.h"
#include "Dijkstra.h"
class Indicator
{
public:
	Indicator(sf::Texture *texture,Player *playerchar);
	~Indicator(void);
	void Update(sf::RenderWindow &Gamewindow,Stage *s);
	void Draw(sf::RenderWindow &Gamewindow);

	sf::Sprite *indicatorSprite;
private:
	sf::Mouse mouse;
	Player *player;
};

