#include "AStar_BinaryHeap.h"
#include "BinaryHeap.h"

void AStar_BinaryHeap::run(HGE* hge,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length])
{
	int gScore[width][length];
	int fScore[width][length];
	int hScore[width][length];
	Binary_heap openHeap;
	list<pNode> closeList;
	bool isInCloseList[width][length];
	for (int i=0;i<width;i++)
		for (int j=0;j<length;j++)
			isInCloseList[i][j] = false;


	closeList.clear();
	history.clear();
	gScore[startX][startY] = 0;
	hScore[startX][startY] = getHScore(&map[startX][startY],&map[endX][endY]);
	fScore[startX][startY] = gScore[startX][startY] + hScore[startX][startY];
	openHeap.push(&map[startX][startY],fScore);
	history.push_back(startX*length+startY);

	while(!openHeap.empty())
	{
		pNode current = openHeap.front();
		openHeap.pop(fScore);

		if(current->postionX == endX && current->postionY == endY)
			return; //找到路径

		closeList.push_back(current);
		isInCloseList[current->postionX][current->postionY] = true;

		list<pNode> neighbor = getNeighbor(map,current);
		for (list<pNode>::iterator itn=neighbor.begin();itn!=neighbor.end();itn++)
		{
			if(isInCloseList[(*itn)->postionX][(*itn)->postionY])
				continue;
			int tempGScore = gScore[current->postionX][current->postionY] + distance(current,*itn,heightGraph);
			if(tempGScore >= MAX_DISTANCE)
				continue;

			if(!openHeap.find((*itn)))	//不在openHeap中
			{
				(*itn)->previous = current;
				hScore[(*itn)->postionX][(*itn)->postionY] = getHScore(*itn,&map[endX][endY]);
				gScore[(*itn)->postionX][(*itn)->postionY] = tempGScore;
				fScore[(*itn)->postionX][(*itn)->postionY] = tempGScore + hScore[(*itn)->postionX][(*itn)->postionY];
				openHeap.push((*itn),fScore);
				history.push_back((*itn)->postionX*length+(*itn)->postionY);

// 				if((*itn)->postionX == endX && (*itn)->postionY == endY)
// 					return; 
				hge->Gfx_BeginScene();
				block[(*itn)->postionX][(*itn)->postionY]->Render(_renderX+(*itn)->postionY*block_size,_renderY+(*itn)->postionX*block_size);
				hge->Gfx_EndScene();
			}
			else if(tempGScore < gScore[(*itn)->postionX][(*itn)->postionY])
			{
				(*itn)->previous = current;
				gScore[(*itn)->postionX][(*itn)->postionY] = tempGScore;
				fScore[(*itn)->postionX][(*itn)->postionY] = tempGScore + hScore[(*itn)->postionX][(*itn)->postionY];
				openHeap.update((*itn),fScore);
			}
		}
	}
}