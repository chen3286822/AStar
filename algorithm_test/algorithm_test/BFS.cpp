#include "BFS.h"

void BFS::run(HGE* hge,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length])
{
	bool visited[width][length];
	queue<pNode> Q;

	for (int i=0;i<width;i++)
	{
		for (int j=0;j<length;j++)
		{
			visited[i][j] = false;
		}
	}
	history.clear();
	Q.push(&map[startX][startY]);
	history.push_back(startX*length+startY);
	visited[startX][startY] = true;

	while (!Q.empty())
	{
		pNode head = Q.front();
		Q.pop();

		if(head->postionX==endX && head->postionY==endY)
			return;

		list<pNode> neighbor = getNeighbor(map,head);
		for (list<pNode>::iterator it=neighbor.begin();it!=neighbor.end();it++)
		{
			if(!visited[(*it)->postionX][(*it)->postionY] && map[(*it)->postionX][(*it)->postionY].achiveble)
			{
				visited[(*it)->postionX][(*it)->postionY] = true;
				Q.push((*it));
				(*it)->previous = head;
				history.push_back((*it)->postionX*length+(*it)->postionY);

				hge->Gfx_BeginScene();
				block[(*it)->postionX][(*it)->postionY]->Render(_renderX+(*it)->postionY*block_size,_renderY+(*it)->postionX*block_size);
				hge->Gfx_EndScene();
			}
		}
	}
}