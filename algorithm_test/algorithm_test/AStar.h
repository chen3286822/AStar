#ifndef ASTAR_H
#define ASTAR_H

#include "utily.h"




class AStar : public Algorithm
{
public:
	AStar()
	{
		strcpy_s(name,"AStar");
	}
	char* getName(){return name;}
	void run(HGE*,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length]);
};
#endif
