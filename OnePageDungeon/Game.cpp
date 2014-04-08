#include "Game.h"


Game::Game(void)
{
	logger = new Logger("Game");

	window = new sf::RenderWindow(sf::VideoMode(640, 480), "One Page Dungeon");
	window->setFramerateLimit(60);

	sf::Image Icon;
	if (!Icon.loadFromFile("assets/gfx/ico.png"))
	{
		logger->logWARN("Failed to load the icon.");
	}
	window->setIcon(32, 32, Icon.getPixelsPtr());

	mainTexture = new sf::Texture();

	if (!mainTexture->loadFromFile("assets/gfx/prototype-tilesheet.png"))
	{
		logger->logWARN("Failed to load the main texture.");
	}

	sf::Font* fontPixel = new sf::Font();
	if (!fontPixel->loadFromFile("assets/fonts/pixelfont.ttf"))
	{
		logger->logWARN("Failed to load font.");
	}
	cFrames = new char[2];
	txtFPS = new sf::Text();
	txtFPS->setStyle(sf::Text::Regular);
	txtFPS->setColor(sf::Color::White);
	txtFPS->setPosition(0.0f, 0.0f);
	txtFPS->setCharacterSize(12);
	txtFPS->setFont(*fontPixel);
	txtFPS->setString("60");

	spriteStore = new SpriteStore(mainTexture);
	stageFactory = new StageFactory(spriteStore, window->getSize());
	townStage = stageFactory->createTownStage(5);

	sf::Vector2f initPosition = townStage->GetObjectCoordinateOfBlock(sf::Vector2i(0, 0));
	player = new Player(spriteStore->getPlayer(), initPosition.x, initPosition.y,townStage);

	indicator = new Indicator(mainTexture,player);

	frameCount = 0;
	clock.restart();
	
	logger->log("Game constructor ended.");
}

Game::~Game(void)
{
	delete player;
	delete logger;
	delete indicator;
	delete window;
	delete spriteStore;
	delete stageFactory;
	delete townStage;
	delete txtFPS;
}

void Game::Update()
{
	indicator->Update(*window,townStage);
	player->Update();
}

void Game::Draw()
{
	townStage->DrawFirstLayer(*window);
	
	if(player->firstLayer)
	{
		indicator->Draw(*window);
		player->Draw(*window);
		
		townStage->DrawSecondLayer(*window);
	}
	else
	{
		townStage->DrawSecondLayer(*window);
		indicator->Draw(*window);
		player->Draw(*window);
	}
	computeAndDrawFps(*window);
}

void Game::computeAndDrawFps(sf::RenderWindow &gameWindow)
{
	sf::Time elapsedTime = clock.getElapsedTime();
	frameCount++;

	if (elapsedTime.asSeconds() >= 1)
	{
		sprintf(cFrames, "%d", frameCount);
		txtFPS->setString(cFrames);

		frameCount = 0;
		clock.restart();
	}

	gameWindow.draw(*txtFPS);
}

void Game::Run()
{
	logger->log("Entering game loop.");
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		Update();
		Draw();

		window->display();
	}
}