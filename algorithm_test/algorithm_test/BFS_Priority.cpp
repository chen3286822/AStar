#include "BFS_Priority.h"

bool BFS_Priority::findNodeInPriorityQueue(pNode node,bool _queue[width][length])
{
	return _queue[node->postionX][node->postionY];
}

priority_queue<priorityNode> BFS_Priority::updateQueue(int newPriority,priorityNode pronode,priority_queue<priorityNode>& origQueue)
{
	//不能直接更改priority_queue中的成员的priority
	//因为直接更改后会导致queue中排列出错，会导致invaild heap

	//如果被更改优先级的元素只是queue的头元素，则不会引发位置的调换
	if(pronode.node->postionX==origQueue.top().node->postionX && pronode.node->postionY==origQueue.top().node->postionY)
	{
		pronode.node->priority = newPriority;
		return origQueue;
	}
	priority_queue<priorityNode> newQueue;
	while (!origQueue.empty())
	{
		priorityNode temp = origQueue.top();
		origQueue.pop();
		if(temp.node->postionX!= pronode.node->postionX || temp.node->postionY!=pronode.node->postionY)
		{
			newQueue.push(temp);
		}
		else
		{
			temp.node->priority = newPriority;
			newQueue.push(temp);
		}
	}
	return newQueue; 
}

void BFS_Priority::run(HGE* hge,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length])
{
	priority_queue<priorityNode> Q;
	priorityNode priNodes[width][length];
	bool explored[width][length];
	bool inQueue[width][length];
	for (int i=0;i<width;i++)
	{
		for (int j=0;j<length;j++)
		{
/*			map[i][j].priority = 0;*/
			priNodes[i][j].node = &map[i][j];
			explored[i][j] = false;
			inQueue[i][j] = false;
		}
	}
	history.clear();
	priNodes[startX][startY].node->priority = 0;

	Q.push(priNodes[startX][startY]);
	inQueue[startX][startY] = true;
	history.push_back(startX*length+startY);

	while (!Q.empty())
	{
		priorityNode head = Q.top();

		if (head.node->postionX==endX && head.node->postionY==endY)
			return;

		Q.pop();
		inQueue[head.node->postionX][head.node->postionY] = false;

		explored[head.node->postionX][head.node->postionY] = true;
		list<pNode> neighbor = getNeighbor(map,head.node);
		for (list<pNode>::iterator itn=neighbor.begin();itn!=neighbor.end();itn++)
		{
			if(!explored[(*itn)->postionX][(*itn)->postionY] && map[(*itn)->postionX][(*itn)->postionY].achiveble)
			{
				int w = distance(head.node,*itn,heightGraph)*-1;
				if(!findNodeInPriorityQueue(*itn,inQueue))
				{
					(*itn)->priority = w + head.node->priority;
					(*itn)->previous = head.node;
					Q.push(priNodes[(*itn)->postionX][(*itn)->postionY]);
					inQueue[(*itn)->postionX][(*itn)->postionY] = true;
					history.push_back((*itn)->postionX*length+(*itn)->postionY);

					hge->Gfx_BeginScene();
					block[(*itn)->postionX][(*itn)->postionY]->Render(_renderX+(*itn)->postionY*block_size,_renderY+(*itn)->postionX*block_size);
					hge->Gfx_EndScene();
				}
				else
				{
					if((*itn)->priority < w + head.node->priority)
					{
						Q = updateQueue(w + head.node->priority,priNodes[(*itn)->postionX][(*itn)->postionY],Q);
						(*itn)->previous = head.node;
					}
				}
			}		
		}
	}
	return;
}