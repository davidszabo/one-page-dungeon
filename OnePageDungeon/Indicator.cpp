#include "Indicator.h"


Indicator::Indicator(sf::Texture *texture, Player *playerchar)
{
	indicatorSprite = new sf::Sprite(*texture,sf::IntRect(48, 0, 16, 16));
	indicatorSprite->setPosition(0.0f, 0.0f);
	indicatorSprite->setScale(3.0f, 3.0f);
	player = playerchar;
}


Indicator::~Indicator(void)
{
}

void Indicator::Update(sf::RenderWindow &Gamewindow,Stage *s)
{
	if(mouse.isButtonPressed(sf::Mouse::Left) && !player->isMoving)
	{
		sf::Vector2i position = mouse.getPosition(Gamewindow);
		if(position.x > 0 && position.x < (int)Gamewindow.getSize().x && position.y > 0 && position.y < (int)Gamewindow.getSize().y)
		{
			sf::Vector2i *mouseClickIndex = new sf::Vector2i(position.x, position.y);
			mouseClickIndex = s->CoordinateToIndex(mouseClickIndex);
			std::cout << "mouseClickIndex->x: " << mouseClickIndex->x << " mouseClickIndex->y: " << mouseClickIndex->y << std::endl;
			if(mouseClickIndex->x != -1 && mouseClickIndex->y != -1 && *mouseClickIndex != player->playerIndex)
			{
				Dijkstra Graph(player->playerIndex, *mouseClickIndex, 5, s->adjacencyMatrix);
				std::vector<sf::Vector2i> routeIndex = Graph.calculateDistance();
				player->playerIndex = *mouseClickIndex;
				std::vector<sf::Vector2f> route;
				std::vector<bool> high;
				sf::Vector2f coord = s->GetObjectCoordinateOfBlock(*mouseClickIndex);
				if(s->materialVector->y[mouseClickIndex->x][mouseClickIndex->y] != 0 && s->materialVector->y[mouseClickIndex->x][mouseClickIndex->y]->GetSpriteNumber() == STONE_BLOCK_TALL)
				{
					indicatorSprite->setPosition(coord.x, coord.y);
				}
				else
				{
					indicatorSprite->setPosition(coord.x,coord.y);
				}
				for(int i = 0; i < (int)routeIndex.size();++i)
				{
					sf::Vector2f objectCoordinate = s->GetObjectCoordinateOfBlock(routeIndex[i]);
					if(s->materialVector->y[routeIndex[i].x][routeIndex[i].y] != 0)
					{
						if( s->materialVector->y[routeIndex[i].x][routeIndex[i].y]->GetSpriteNumber() == STONE_BLOCK_TALL)
						{
							objectCoordinate = objectCoordinate - sf::Vector2f(0, 30);
						}
						else
						{
							objectCoordinate = objectCoordinate - sf::Vector2f(0, 20);
						}
						route.push_back(objectCoordinate);
						high.push_back(true);
					}
					else
					{
						objectCoordinate = objectCoordinate - sf::Vector2f(0, 20);
						route.push_back(objectCoordinate);
						high.push_back(false);
					}					
				}
				player->MoveTo(route, 1.0f, high);
			}
		}
	}
	
}

void Indicator::Draw(sf::RenderWindow &Gamewindow)
{
	if(player->isMoving)
	{
		Gamewindow.draw(*indicatorSprite);
	}
}
