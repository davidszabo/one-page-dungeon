#pragma once
#include <SFML/Graphics.hpp>
#include "Logger.h"
#include "Player.h"
#include "SpriteStore.h"
#include "StageFactory.h"
#include "Stage.h"
#include "Indicator.h"

class Game
{
public:
	Game(void);
	~Game(void);
	void Run();
	
private: 
	void Game::computeAndDrawFps(sf::RenderWindow &gameWindow);

	sf::RenderWindow *window;
	sf::Texture *mainTexture;
	Logger *logger;
	
	Player *player;
	
	Indicator *indicator;

	SpriteStore *spriteStore;
	StageFactory *stageFactory;
	Stage *townStage;
	
	sf::Clock clock;
	sf::Text* txtFPS;
	char* cFrames;
	int frameCount;

	void Update();
	void Draw();
};

