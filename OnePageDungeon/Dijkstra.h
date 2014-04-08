#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
class Dijkstra
{
public:
	Dijkstra(sf::Vector2i sourcenode, sf::Vector2i destinationnode, int size,int **adjmat);
	~Dijkstra(void);
	int getClosestUnmarkedNode();
	std::vector<sf::Vector2i> calculateDistance();
	void makePath(int node);
	void initialize();
private:
	int **adjMatrix;
    std::vector<int> predecessor;
	std::vector<int> distance;
    std::vector<bool> mark; 
    int source;
	int destination;
    int numOfVertices;
	std::vector<sf::Vector2i> Route;
};

