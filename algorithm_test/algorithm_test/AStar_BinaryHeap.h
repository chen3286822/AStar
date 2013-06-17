#ifndef ASTAR_BINARYHEAP_H
#define ASTAR_BINARYHEAP_H

#include "utily.h"


class AStar_BinaryHeap : public Algorithm
{
public:
	AStar_BinaryHeap()
	{
		strcpy_s(name,"AStar_BinaryHeap");
	}
	char* getName(){return name;}
	void run(HGE*,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length]);

};


#endif