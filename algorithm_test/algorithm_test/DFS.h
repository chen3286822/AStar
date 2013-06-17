#ifndef DFS_H
#define DFS_H

#include "utily.h"

class DFS : public Algorithm
{
public:
	DFS()
	{
		strcpy_s(name,"DFS");
	}
	char* getName(){return name;}
	void run(HGE*,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length]);

private:
	int getDirection(pNode current,pNode target);
	list<pNode> getNewNeighbor(Node map[width][length],pNode current,int direct);
	bool testNode(HGE* hge,pNode current,int endX,int endY,int _renderX,int _renderY);
	bool visited[width][length];

	enum
	{
		EAST = 0x00000001,
		WEST = 0x00000010,
		NORTH = 0x00000100,
		SOUTH = 0x00001000,
		EASTNORTH = 0x00010000,
		EASTSOUTH = 0x00100000,
		WESTNORTH = 0x01000000,
		WESTSOUTH = 0x10000000,
	};
};

#endif