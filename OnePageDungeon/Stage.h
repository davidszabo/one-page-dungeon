#pragma once

#include <SFML\Graphics.hpp>
#include "Sprite.h"
class Stage
{
public:
	~Stage(void);
	void DrawFirstLayer(sf::RenderWindow &Gamewindow);
	void DrawSecondLayer(sf::RenderWindow &Gamewindow);
	sf::Vector2i* CoordinateToIndex(sf::Vector2i* coordinate);
	sf::Vector2f GetObjectCoordinateOfBlock(sf::Vector2i index);
	int **adjacencyMatrix;
	sf::Vector2<Sprite ***> *materialVector;
private:
	Stage(void);
	Stage(int size, int **occupyMatrix, int **adjacencyMatrix, sf::Vector2<Sprite ***> *materialVector, sf::Vector2<sf::IntRect ***> *boundingBoxVector);
	bool checkIfOutOfBoundaryAndSetReturnVector(sf::Vector2i* coordinate, sf::Vector2i* returnVector);

	int size;
	int **occupyMatrix; 

	sf::Vector2<sf::IntRect ***> *boundingBoxVector;

	friend class StageFactory;
};

