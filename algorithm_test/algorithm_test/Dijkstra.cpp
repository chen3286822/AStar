#include "Dijkstra.h"


void Dijkstra::run(HGE* hge,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length])
{
	list<pNode> S;
	list<pNode> Q;
	int dist[width][length];
	for (int i=0;i<width;i++)
	{
		for (int j=0;j<length;j++)
		{
			dist[i][j] = MAX_DISTANCE;
			Q.push_back(&map[i][j]);
		}
	}
	dist[map[startX][startY].postionX][map[startX][startY].postionY] = 0;
	S.clear();

	while (!Q.empty())
	{
		list<pNode>::iterator temp = Q.begin();
		for (list<pNode>::iterator it=Q.begin();it!=Q.end();it++)
		{
			if(dist[(*temp)->postionX][(*temp)->postionY] > dist[(*it)->postionX][(*it)->postionY])
				temp = it;
		}
		if(dist[(*temp)->postionX][(*temp)->postionY] >= MAX_DISTANCE)
			break;	//已经无法找到路径，可能由于所有路径都被封死
		pNode u = *temp;
		Q.erase(temp);
		S.push_back(u);
		history.push_back(u->postionX*length+u->postionY);

		hge->Gfx_BeginScene();
		block[u->postionX][u->postionY]->Render(_renderX+u->postionY*block_size,_renderY+u->postionX*block_size);
		hge->Gfx_EndScene();

		if(map[endX][endY].postionX==u->postionX &&map[endX][endY].postionY==u->postionY)
			return;

		list<pNode> neighbor = getNeighbor(map,u);
		for (list<pNode>::iterator itn=neighbor.begin();itn!=neighbor.end();itn++)
		{
			int w = distance(u,*itn,heightGraph);
			if(dist[(*itn)->postionX][(*itn)->postionY] > dist[u->postionX][u->postionY] + w)
			{
				dist[(*itn)->postionX][(*itn)->postionY] = dist[u->postionX][u->postionY] + w;
				map[(*itn)->postionX][(*itn)->postionY].previous = u;
			}
		}
	}
	return;
}
