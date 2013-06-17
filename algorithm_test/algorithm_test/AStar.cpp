#include "AStar.h"





void AStar::run(HGE* hge,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length])
{
	int gScore[width][length];
	int fScore[width][length];
	int hScore[width][length];
	list<pNode> openList;
	list<pNode> closeList;

	openList.push_back(&map[startX][startY]);
	closeList.clear();
	history.clear();
	gScore[startX][startY] = 0;
	hScore[startX][startY] = getHScore(&map[startX][startY],&map[endX][endY]);
	fScore[startX][startY] = gScore[startX][startY] + hScore[startX][startY];

	history.push_back(startX*length+startY);

	while(!openList.empty())
	{
		//取openlist中f(x)最少的那个节点
		list<pNode>::iterator current = openList.begin();
		for (list<pNode>::iterator it=openList.begin();it!=openList.end();it++)
		{
			if(fScore[(*current)->postionX][(*current)->postionY]>fScore[(*it)->postionX][(*it)->postionY])
			{
				current = it;
			}
		}

		if((*current)->postionX == endX && (*current)->postionY == endY)
			return; //找到路径

		closeList.push_back(*current);

		list<pNode>::iterator tempCurrent = (--closeList.end());
		openList.erase(current);
		current = tempCurrent;

		list<pNode> neighbor = getNeighbor(map,*current);
		for (list<pNode>::iterator itn=neighbor.begin();itn!=neighbor.end();itn++)
		{
			if(findNode(*itn,closeList))
				continue;
			int tempGScore = gScore[(*current)->postionX][(*current)->postionY] + distance(*current,*itn,heightGraph);
			if(tempGScore >= MAX_DISTANCE)
				continue;
			bool tempGood = false;
			if(!findNode(*itn,openList))
			{
				openList.push_back(*itn);
				history.push_back((*itn)->postionX*length+(*itn)->postionY);

				hge->Gfx_BeginScene();
				block[(*itn)->postionX][(*itn)->postionY]->Render(_renderX+(*itn)->postionY*block_size,_renderY+(*itn)->postionX*block_size);
				hge->Gfx_EndScene();

				hScore[(*itn)->postionX][(*itn)->postionY] = getHScore(*itn,&map[endX][endY]);
				tempGood = true;
			}
			else if(tempGScore < gScore[(*itn)->postionX][(*itn)->postionY])
				tempGood = true;
			else
				tempGood = false;
			if(tempGood)
			{
				(*itn)->previous = *current;
				gScore[(*itn)->postionX][(*itn)->postionY] = tempGScore;
				fScore[(*itn)->postionX][(*itn)->postionY] = tempGScore + hScore[(*itn)->postionX][(*itn)->postionY];
			}
		}
	}

	return;
}