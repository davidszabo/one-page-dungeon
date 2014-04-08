#include "Dijkstra.h"


Dijkstra::Dijkstra(sf::Vector2i sourcenode,sf::Vector2i destinationnode, int size,int **adjmat)
{
	adjMatrix = adjmat;
	numOfVertices = size*size;
	predecessor.resize(size*size);
	distance.resize(size*size);
	mark.resize(size*size);
	source = sourcenode.x * size + sourcenode.y;
	destination = destinationnode.x * size + destinationnode.y;
}


Dijkstra::~Dijkstra(void)
{ 
}

void Dijkstra::initialize()
{
    for(int i=0;i<numOfVertices;i++)
	{
        mark[i] = false;
        predecessor[i] = -1;
        distance[i] = 99;
    }
    distance[source]= 0;
}
int Dijkstra::getClosestUnmarkedNode()
{
    int minDistance = 99;
    int closestUnmarkedNode;
    for(int i=0;i<numOfVertices;i++)
	{
        if((!mark[i]) && ( minDistance >= distance[i])) 
		{
            minDistance = distance[i];
            closestUnmarkedNode = i;
        }
    }
    return closestUnmarkedNode;
}
std::vector<sf::Vector2i> Dijkstra::calculateDistance()
{

    initialize();
    int minDistance = 99;
    int closestUnmarkedNode;
    int count = 0;
    while(count < numOfVertices) {
        closestUnmarkedNode = getClosestUnmarkedNode();
        mark[closestUnmarkedNode] = true;
        for(int i=0;i<numOfVertices;i++)
		{
            if((!mark[i]) && (adjMatrix[closestUnmarkedNode][i]>0) )
			{
                if(distance[i] > distance[closestUnmarkedNode]+adjMatrix[closestUnmarkedNode][i])
				{
                    distance[i] = distance[closestUnmarkedNode]+adjMatrix[closestUnmarkedNode][i];
                    predecessor[i] = closestUnmarkedNode;
                }
            }
        }
        count++;
    }
	makePath(destination);
	return Route;
}

void Dijkstra::makePath(int node)
{
	if(predecessor[node] != -1)
	{
		makePath(predecessor[node]);
		sf::Vector2i routePart;
		routePart.x = (int)(node/(int)(sqrt((float)numOfVertices)));
		routePart.y = node % (int)(sqrt((float)numOfVertices)); 
		Route.push_back(routePart);
	}
}