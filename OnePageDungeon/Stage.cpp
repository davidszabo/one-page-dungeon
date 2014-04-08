#include "Stage.h"


Stage::Stage(int size, int **occupyMatrix, int **adjacencyMatrix, sf::Vector2<Sprite ***> *materialVector, sf::Vector2<sf::IntRect ***> *boundingBoxVector)
{
	this->size = size;
	this->occupyMatrix = occupyMatrix;
	this->adjacencyMatrix = adjacencyMatrix;
	this->materialVector = materialVector;
	this->boundingBoxVector = boundingBoxVector;
}

sf::Vector2i* Stage::CoordinateToIndex(sf::Vector2i* coordinate)
{
	sf::Vector2i *offSetcoordinate = new sf::Vector2i(0 + coordinate->x, coordinate->y +16);
	sf::Vector2i* indexVector = new sf::Vector2i();
	if (checkIfOutOfBoundaryAndSetReturnVector(offSetcoordinate, indexVector))
	{
		return indexVector;
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			
			if (boundingBoxVector->x[i][j]->contains(*offSetcoordinate))
			{
				indexVector->x = i;
				indexVector->y = j;
				return indexVector;
			}
		}
	}
}

bool Stage::checkIfOutOfBoundaryAndSetReturnVector(sf::Vector2i* coordinate, sf::Vector2i* indexVector)
{
	sf::Vector2i* topLeftCorner = new sf::Vector2i(boundingBoxVector->x[0][0]->left, boundingBoxVector->x[0][0]->top);
	sf::Vector2i* bottomLeftCorner = new sf::Vector2i(boundingBoxVector->x[0][size - 1]->left, boundingBoxVector->x[0][size - 1]->top + boundingBoxVector->x[0][size - 1]->height);
	sf::Vector2i* bottomRightCorner = new sf::Vector2i(boundingBoxVector->x[size - 1][size - 1]->left + boundingBoxVector->x[0][size - 1]->width, boundingBoxVector->x[size - 1][size - 1]->top + boundingBoxVector->x[0][size - 1]->height);

	if(coordinate->x < bottomLeftCorner->x || coordinate->x > bottomRightCorner->x || coordinate->y > bottomLeftCorner->y || coordinate->y < topLeftCorner->y)
	{
		delete topLeftCorner;
		delete bottomLeftCorner;
		delete bottomRightCorner;

		indexVector->x = -1;
		indexVector->y = -1;
		return true;
	}

	return false;
}

sf::Vector2f Stage::GetObjectCoordinateOfBlock(sf::Vector2i index)
{
	sf::Vector2f objectCoordinate = sf::Vector2f();
	objectCoordinate.x = boundingBoxVector->x[index.x][index.y]->left;
	objectCoordinate.y = boundingBoxVector->x[index.x][index.y]->top;
	return objectCoordinate;
}

void Stage::DrawFirstLayer(sf::RenderWindow &gameWindow)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
				sf::Vector2i drawCoords = sf::Vector2i(boundingBoxVector->x[i][j]->left, boundingBoxVector->x[i][j]->top);
				materialVector->x[i][j]->setPosition(drawCoords.x, drawCoords.y);
				gameWindow.draw(*materialVector->x[i][j]);
		}
	}
}
void Stage::DrawSecondLayer(sf::RenderWindow &gameWindow)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
				sf::Vector2i drawCoords = sf::Vector2i(boundingBoxVector->y[i][j]->left, boundingBoxVector->y[i][j]->top);
				if(materialVector->y[i][j] != 0)
				{
					materialVector->y[i][j]->setPosition(drawCoords.x, drawCoords.y);
					gameWindow.draw(*materialVector->y[i][j]);
				}
		}
	}
}

Stage::~Stage(void)
{
	for(int i = 0; i < size; ++i)
	{
		delete [] occupyMatrix[i];
	}
	delete [] occupyMatrix;

	for(int i = 0; i < size; ++i)
	{
		delete [] adjacencyMatrix[i];
	}
	delete [] adjacencyMatrix;


	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			delete materialVector->x[i][j];
			if(materialVector->y[i][j] != 0)
			{
				delete materialVector->y[i][j];
			}
		}
		delete[] materialVector->x[i];
		delete[] materialVector->y[i];
	}
	delete[] materialVector->x;
	delete[] materialVector->y;
	delete materialVector;
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			delete boundingBoxVector->x[i][j];
			if(boundingBoxVector->y[i][j] != 0)
			{
				delete boundingBoxVector->y[i][j];
			}
		}
		delete[] boundingBoxVector->x[i];
		delete[] boundingBoxVector->y[i];
	}
	delete[] boundingBoxVector->x;
	delete[] boundingBoxVector->y;
	delete boundingBoxVector;
}
