#ifndef ASTAR_INSERTSORT_H
#define ASTAR_INSERTSORT_H

#include "utily.h"


class AStar_InsertSort : public Algorithm
{
public:
	AStar_InsertSort()
	{
		strcpy_s(name,"AStar_InsertSort");
	}
	char* getName(){return name;}
	void run(HGE*,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length]);
};
//list<int> AStar_InsertSort(HGE* hge,Node map[width][length],pNode start,pNode end,int heightGraph[width][length],hgeSprite* _block[width][length]);
void test();
#endif