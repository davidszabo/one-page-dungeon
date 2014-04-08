#include "StageFactory.h"


StageFactory::StageFactory(SpriteStore *spriteStore, sf::Vector2u renderSize)
{
	this->spriteStore = spriteStore;
	this->renderSize = new sf::Vector2u(renderSize);
}

Stage* StageFactory::createTownStage(int size)
{
	int xMid = renderSize->x / 2;
	int yMid = renderSize->y / 2;
	int sizeHalf = size / 2;
	int xOffset = spriteStore->getStoneBlock()->getGlobalBounds().width * sizeHalf;
	int yOffset = spriteStore->getStoneBlock()->getGlobalBounds().height * sizeHalf;
	sf::Vector2i origin(xMid - xOffset, yMid - yOffset);

	int **occupyMatrix = initialise2DMatrix(size, 0);
	sf::Vector2<Sprite ***> *materialVector = initialise2DMaterialMatrix(size, spriteStore->getStoneBlock(), spriteStore->getStoneBlockTall());
	int **adjacencyMatrix = initialiseAdjMatrix(size,materialVector);
	sf::Vector2<sf::IntRect ***> *boundingBoxVector = initialise2DBoundingBoxMatrix(size, origin, spriteStore->getStoneBlock()->getGlobalBounds(), spriteStore->getStoneBlock()->getScale());

	return new Stage(size, occupyMatrix, adjacencyMatrix, materialVector, boundingBoxVector);
}

sf::Vector2<sf::IntRect ***>* StageFactory::initialise2DBoundingBoxMatrix(int size, sf::Vector2i origin, sf::FloatRect rect, sf::Vector2f scale)
{
	sf::Vector2<sf::IntRect ***> *vector = new sf::Vector2<sf::IntRect ***>();
	sf::IntRect ***matrix = new sf::IntRect**[size];
	for(int i = 0; i < size; i++)
	{
		matrix[i] = new sf::IntRect*[size];
		for(int j = 0; j < size; j++)
		{
			rect.top = origin.y + (rect.height - (scale.y * 6)) * j;
			rect.left = origin.x + rect.width * i;
			matrix[i][j] = new sf::IntRect(rect);
		}
	}
	vector->x = matrix;

	sf::IntRect ***matrix2 = new sf::IntRect**[size];
	for(int i = 0; i < size; i++)
	{
		matrix2[i] = new sf::IntRect*[size];
		for(int j = 0; j < size; j++)
		{
			rect.top = origin.y + (rect.height - (scale.y * 6)) * j - (scale.y * 6);
			rect.left = origin.x + rect.width * i;
			matrix2[i][j] = new sf::IntRect(rect);
		}
	}
	vector->y = matrix2;

	return vector;
}

sf::Vector2<Sprite ***>* StageFactory::initialise2DMaterialMatrix(int size, Sprite *defaultGroundSprite, Sprite *defaultHighGroundSprite)
{
	sf::Vector2<Sprite ***> *vector = new sf::Vector2<Sprite ***>();
	Sprite ***matrix = new Sprite**[size];
	for(int i = 0; i < size; i++)
	{
		matrix[i] = new Sprite*[size];
		for(int j = 0; j < size; j++)
		{
			matrix[i][j] = new Sprite(*defaultGroundSprite);
		}
	}
	vector->x = matrix;
	Sprite ***matrix2 = new Sprite**[size];
	for(int i = 0; i < size; i++)
	{
		matrix2[i] = new Sprite*[size];
		for(int j = 0; j < size; j++)
		{
			matrix2[i][j] = 0;
		}
	}
	matrix2[1][1] = new Sprite(*defaultHighGroundSprite);
	matrix2[0][1] = new Sprite(*spriteStore->getStoneRampLeft());
	matrix2[2][1] = new Sprite(*defaultHighGroundSprite);
	matrix2[2][2] = new Sprite(*defaultHighGroundSprite);
	matrix2[3][1] = new Sprite(*spriteStore->getStoneRampRight());
	matrix2[1][0] = new Sprite(*spriteStore->getStoneRampTop());
	matrix2[1][2] = new Sprite(*spriteStore->getStoneRampBottom());
	vector->y = matrix2;
	return vector;
}

int** StageFactory::initialise2DMatrix(int size, int defaultValue)
{
	int **matrix = new int*[size];
	for(int i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
		for(int j = 0; j < size; j++)
		{
			matrix[i][j] = defaultValue;
		}
	}

	return matrix;
}

int** StageFactory::initialiseAdjMatrix(int size,sf::Vector2<Sprite ***>* materialVector)
{
	int **matrix = new int*[size*size];
	for(int i = 0; i < size*size;++i)
	{
		matrix[i] = new int[size*size];
		for(int j = 0; j < size*size; ++j)
		{
			matrix[i][j] = 0;
		}
	}
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			if(i + 1 < size)
			{
				if(materialVector->y[i+1][j] != 0 && materialVector->y[i+1][j]->GetSpriteNumber() == STONE_BLOCK_TALL)
				{
					if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_RAMP_LEFT)
					{
						matrix[i*size+j][(i+1)*size+j] = 2;
					}
					else if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_BLOCK_TALL)
					{
						matrix[i*size+j][(i+1)*size+j] = 1;
					}
					else
					{
						matrix[i*size+j][(i+1)*size+j] = 0;
					}
				}
				else if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_BLOCK_TALL)
				{
					if(materialVector->y[i+1][j] != 0 && materialVector->y[i+1][j]->GetSpriteNumber() == STONE_RAMP_RIGHT)
					{
						matrix[i*size+j][(i+1)*size+j] = 2;
					}
					else
					{
						matrix[i*size+j][(i+1)*size+j] = 0;
					}
				}
				else
				{
					matrix[i*size+j][(i+1)*size+j] = 1;
				}
			}
			if(i - 1 >= 0)
			{
				if(materialVector->y[i-1][j] != 0 && materialVector->y[i-1][j]->GetSpriteNumber() == STONE_BLOCK_TALL)
				{
					if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_RAMP_RIGHT)
					{
						matrix[i*size+j][(i-1)*size+j] = 2;
					}
					else if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_BLOCK_TALL)
					{
						matrix[i*size+j][(i-1)*size+j] = 1;
					}
					else
					{
						matrix[i*size+j][(i-1)*size+j] = 0;
					}
				}
				else if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_BLOCK_TALL)
				{
					if(materialVector->y[i-1][j] != 0 && materialVector->y[i-1][j]->GetSpriteNumber() == STONE_RAMP_LEFT)
					{
						matrix[i*size+j][(i-1)*size+j] = 2;
					}
					else
					{
						matrix[i*size+j][(i-1)*size+j] = 0;
					}
				}
				else
				{
					matrix[i*size+j][(i-1)*size+j] = 1;
				}
			}
			if(j + 1 < size)
			{
				if(materialVector->y[i][j+1] != 0 && materialVector->y[i][j+1]->GetSpriteNumber() == STONE_BLOCK_TALL)
				{
					if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_RAMP_TOP)
					{
						matrix[i*size+j][i*size+j+1] = 2;
					}
					else if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_BLOCK_TALL)
					{
						matrix[i*size+j][i*size+j+1] = 1;
					}
					else
					{
						matrix[i*size+j][i*size+j+1] = 0;
					}
				}
				else if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_BLOCK_TALL)
				{
					if(materialVector->y[i][j+1] != 0 && materialVector->y[i][j+1]->GetSpriteNumber() == STONE_RAMP_BOTTOM)
					{
						matrix[i*size+j][i*size+j+1] = 2;
					}
					else
					{
						matrix[i*size+j][i*size+j+1] = 0;
					}
				}
				else
				{
					matrix[i*size+j][i*size+j+1] = 1;
				}
			}
			if(j - 1 >= 0)
			{
				if(materialVector->y[i][j-1] != 0 && materialVector->y[i][j-1]->GetSpriteNumber() == STONE_BLOCK_TALL)
				{
					if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_RAMP_BOTTOM)
					{
						matrix[i*size+j][i*size+j-1] = 2;
					}
					else if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_BLOCK_TALL)
					{
						matrix[i*size+j][i*size+j-1] = 1;
					}
					else
					{
						matrix[i*size+j][i*size+j-1] = 0;
					}
				}
				else if(materialVector->y[i][j]!=0 && materialVector->y[i][j]->GetSpriteNumber() == STONE_BLOCK_TALL)
				{
					if(materialVector->y[i][j-1] != 0 && materialVector->y[i][j-1]->GetSpriteNumber() == STONE_RAMP_TOP)
					{
						matrix[i*size+j][i*size+j-1] = 2;
					}
					else
					{
						matrix[i*size+j][i*size+j-1] = 0;
					}
				}
				else
				{
					matrix[i*size+j][i*size+j-1] = 1;
				}
			}
		}
	}

	return matrix;
}

StageFactory::~StageFactory(void)
{
	delete renderSize;
}
