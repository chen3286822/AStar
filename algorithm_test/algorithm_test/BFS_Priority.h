#ifndef BFS_PRIORITY_H
#define BFS_PRIORITY_H

#include "utily.h"

class BFS_Priority : public Algorithm
{
public:
	BFS_Priority()
	{
		strcpy_s(name,"BFS_Priority");
	}
	char* getName(){return name;}
	void run(HGE*,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length]);

private:
	bool findNodeInPriorityQueue(pNode node,bool _queue[width][length]);
	priority_queue<priorityNode> updateQueue(int newPriority,priorityNode pronode,priority_queue<priorityNode>& origQueue);
};

#endif