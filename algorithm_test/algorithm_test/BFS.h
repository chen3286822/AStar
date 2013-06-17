#ifndef BFS_H
#define BFS_H

#include "utily.h"

class BFS : public Algorithm
{
public:
	BFS()
	{
		strcpy_s(name,"BFS");
	}
	char* getName(){return name;}
	void run(HGE*,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length]);
};

#endif