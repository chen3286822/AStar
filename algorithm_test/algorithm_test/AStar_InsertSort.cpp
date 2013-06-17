#include "AStar_InsertSort.h"


void insert_sort(list<pNode>& nodeSet, pNode node,int fScore[width][length])
{
	list<pNode>::iterator temp = nodeSet.end();
	for (list<pNode>::reverse_iterator rit=nodeSet.rbegin();rit!=nodeSet.rend();rit++)
	{
		if(fScore[(*rit)->postionX][(*rit)->postionY] > fScore[node->postionX][node->postionY])
			temp--;
		else
			break;
	}
	nodeSet.insert(temp,node);
}

pNode removeLeastNode(list<pNode>& nodeSet)
{
	if(nodeSet.empty())
		return NULL;
	pNode leastNode = nodeSet.front();
	nodeSet.pop_front();
	return leastNode;
}

void updateNode(list<pNode>& nodeSet, pNode node,int fScore[width][length])
{
	list<pNode>::iterator  it,temp;
	
	for (it=nodeSet.end(),--it;it!=nodeSet.begin();--it)		//由于肯定node是nodeSet其中一个，所以只比较到begin后面一个，如果找不到，则begin肯定是node
	{
		if((*it)->postionX==node->postionX && (*it)->postionY==node->postionY)
			break;
	}
	temp = it;
	for (;it!=nodeSet.begin();--it)
	{
		list<pNode>::iterator itTemp = it;
		itTemp--;
		if(fScore[(*itTemp)->postionX][(*itTemp)->postionY] <= fScore[node->postionX][node->postionY])
			break;
	}
	nodeSet.insert(it,node);
	nodeSet.erase(temp);
}

void AStar_InsertSort::run(HGE* hge,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length])
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
		pNode current = removeLeastNode(openList);

		if(current->postionX == endX && current->postionY == endY)
			return; //找到路径

		closeList.push_back(current);

		list<pNode> neighbor = getNeighbor(map,current);
		for (list<pNode>::iterator itn=neighbor.begin();itn!=neighbor.end();itn++)
		{
			if(findNode(*itn,closeList))
				continue;
			int tempGScore = gScore[current->postionX][current->postionY] + distance(current,*itn,heightGraph);
			if(tempGScore >= MAX_DISTANCE)
				continue;

			if(!findNode(*itn,openList))
			{
				(*itn)->previous = current;
				hScore[(*itn)->postionX][(*itn)->postionY] = getHScore(*itn,&map[endX][endY]);
				gScore[(*itn)->postionX][(*itn)->postionY] = tempGScore;
				fScore[(*itn)->postionX][(*itn)->postionY] = tempGScore + hScore[(*itn)->postionX][(*itn)->postionY];
				insert_sort(openList,*itn,fScore);
				history.push_back((*itn)->postionX*length+(*itn)->postionY);

				hge->Gfx_BeginScene();
				block[(*itn)->postionX][(*itn)->postionY]->Render(_renderX+(*itn)->postionY*block_size,_renderY+(*itn)->postionX*block_size);
				hge->Gfx_EndScene();

				
			}
			else if(tempGScore < gScore[(*itn)->postionX][(*itn)->postionY])
			{
				(*itn)->previous = current;
				gScore[(*itn)->postionX][(*itn)->postionY] = tempGScore;
				fScore[(*itn)->postionX][(*itn)->postionY] = tempGScore + hScore[(*itn)->postionX][(*itn)->postionY];
				updateNode(openList,*itn,fScore);
			}

		}
	}

	return;
}

void test()
{
	list<pNode>  mylist;
	Node a1,a2,a3,a4;
	a1.postionX = 0;
	a1.postionY = 0;
	a2.postionX = 0;
	a2.postionY = 1;
	a3.postionX = 0;
	a3.postionY = 2;
	a4.postionX = 0;
	a4.postionY = 3;
	int score[width][length];
	score[0][0] = 4;
	score[0][1] = 7;
	score[0][2] = 3;
	score[0][3] = 8;

	insert_sort(mylist,&a1,score);
	insert_sort(mylist,&a2,score);
	insert_sort(mylist,&a3,score);
	insert_sort(mylist,&a4,score);

	score[0][1] = 1;
	updateNode(mylist,&a2,score);

	pNode temp = removeLeastNode(mylist);
	temp = removeLeastNode(mylist);
	temp = removeLeastNode(mylist);
	temp = removeLeastNode(mylist);
}