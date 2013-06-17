#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "utily.h"

class Dijkstra : public Algorithm
{
public:
	Dijkstra()
	{
		strcpy_s(name,"Dijkstra");
	}
	char* getName(){return name;}
	void run(HGE*,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length]);
};
#endif