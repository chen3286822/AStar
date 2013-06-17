#include "AStar_InsertSort_BinarySearch.h"


int findNode_BinarySearch(pNode node,vector<pNode> nodeList,int score[width][length])
{
	//二分查找，nodeList中元素是按fScore从大到小的顺序排列的
	if(nodeList.empty())
		return -1;
	if(score[node->postionX][node->postionY] == MAX_DISTANCE)
		return -1;
	int max = nodeList.size() - 1;
	int min = 0;
	while(min <= max)
	{
		int mid = (min + max)>>1;
		if(score[nodeList[mid]->postionX][nodeList[mid]->postionY] == score[node->postionX][node->postionY])
		{
			//找到fScore相同的某个节点，现在向前向后查找这个fScore都相同的区间
			//比较这个区间内节点的坐标，看是否与目标相同
			int temp = mid;
			//向前查找
			while(score[nodeList[temp]->postionX][nodeList[temp]->postionY] == score[node->postionX][node->postionY])
			{
				if(nodeList[temp]->postionX==node->postionX && nodeList[temp]->postionY==node->postionY)
					return temp;
				if(temp > 0)
					temp--;
				else
					break;
			}
			//向后查找
			if(temp < nodeList.size()-1)
				temp = mid+1;
			else
				return -1;
			while(score[nodeList[temp]->postionX][nodeList[temp]->postionY] == score[node->postionX][node->postionY])
			{
				if(nodeList[temp]->postionX==node->postionX && nodeList[temp]->postionY==node->postionY)
					return temp;
				if(temp < nodeList.size()-1)
					temp++;
				else
					break;
			}
			return -1;
		}
		else if(score[nodeList[mid]->postionX][nodeList[mid]->postionY] < score[node->postionX][node->postionY])
			max = mid - 1;
		else 
			min = mid + 1;
	}
	return -1; //没有找到
}

void insert_sort(vector<pNode>& nodeList,pNode node,int score[width][length],int begin)
{
	//观察得知，随着查找范围变大，新加入的fScore会不断变小
	//所以为了效率，新待插入的值优先从后往前比较并插入
	//vector前向插入效率不高
	//进一步优化：使用二分查找得到待插入位置
	vector<pNode>::iterator temp = nodeList.end();
	for (vector<pNode>::reverse_iterator rit=nodeList.rbegin();rit!=nodeList.rend();rit++)
	{
		if(score[(*rit)->postionX][(*rit)->postionY] < score[node->postionX][node->postionY])
			temp--;
		else
			break;
	}
	nodeList.insert(temp,node);
}

void insert_sort_BinarySearch(vector<pNode>& nodeList,pNode node,int score[width][length],int begin)
{
	int min = begin,max = nodeList.size()-1;
	int mid = -1;
	while (min <= max)
	{ 
		mid = (min+max)>>1;
		if(score[nodeList[mid]->postionX][nodeList[mid]->postionY] == score[node->postionX][node->postionY])
		{
			int temp = mid;
			while(score[nodeList[temp]->postionX][nodeList[temp]->postionY] == score[node->postionX][node->postionY])
			{
				if(temp < nodeList.size()-1)
					temp++;
				else
					break;
			}
			nodeList.insert(nodeList.begin()+temp,node);
			return;
		}
		if(score[nodeList[mid]->postionX][nodeList[mid]->postionY] > score[node->postionX][node->postionY])
			min = mid+1;
		else 
			max = mid - 1;
	}
	//nodeList为空
	if(mid==-1)
	{
		nodeList.push_back(node);
		return;
	}
	//没有相等的节点
	if(score[nodeList[mid]->postionX][nodeList[mid]->postionY] > score[node->postionX][node->postionY])
		nodeList.insert(nodeList.begin()+mid+1,node);
	else
		nodeList.insert(nodeList.begin()+mid,node);
}

pNode removeLeastNode(vector<pNode>& nodeList)
{
	//由于nodeList按照从大到小的顺序排列
	//所以最后一个元素就是具有最小fScore的节点
	if (nodeList.empty())
		return NULL;
	pNode leastNode = nodeList.back();
	nodeList.pop_back();
	return leastNode;
}

void updateNode(vector<pNode>& nodeList,pNode node,int score[width][length],int index)
{
	//根据前面insert_sort返回的位置index就是node在nodeList中的位置
	//以及node的新fScore肯定变小
	//故直接移除index位置的node，然后从index位置往后判断并插入node
	//进一步优化：使用二分查找得到待插入位置
	//进一步优化：由于要移除节点并插入到新的位置，其实只要移动从移除到插入
	//这一段nodeList中间的元素，其余元素尤其是插入位置以后的元素保持不变
	//所以使用erase和insert将会导致插入位置之后的元素整体向前移动又向后移动
	//影响效率，故手动执行移除到插入这一段之间的元素更改将更有效率
	/*
	*	e.p. 7, 6, 4, 1 若6更新成3，则数组应该变成 7, 4, 3, 1
	*	仅仅只有第二个和第三个元素交换
	*	先erase再insert将是 7,4,1  -> 7,4,3,1 : 4,1先向前移动，1又向后移动
	*	新插入位置后面元素越多，降低效率越明显
	*/
	if(index < nodeList.size()-1 && 
		score[nodeList[index+1]->postionX][nodeList[index+1]->postionY] <= score[node->postionX][node->postionY])
		return;	//更新的node的fScore依然比后面一个node的fScore要大，则不需要更新位置
	nodeList.erase(nodeList.begin()+index);
	vector<pNode>::iterator it = nodeList.begin()+index;
	for (;it!=nodeList.end();it++)
	{
		if(score[(*it)->postionX][(*it)->postionY] < score[node->postionX][node->postionY])
			break;
	}
	nodeList.insert(it,node);
}

void updateNode_BinarySearch(vector<pNode>& nodeList,pNode node,int score[width][length],int index)
{
	if(index < nodeList.size()-1 && 
		score[nodeList[index+1]->postionX][nodeList[index+1]->postionY] <= score[node->postionX][node->postionY])
		return;	//更新的node的fScore依然比后面一个node的fScore要大，则不需要更新位置
	int min = index+1;
	int max = nodeList.size()-1;
	int mid = nodeList.size()-1;
	while (min < max)
	{
		mid = (min + max)>>1;
		if(score[nodeList[mid]->postionX][nodeList[mid]->postionY] == score[node->postionX][node->postionY])
		{
			int temp = mid;
			while(score[nodeList[temp]->postionX][nodeList[temp]->postionY] == score[node->postionX][node->postionY])
			{
				if(temp < nodeList.size()-1)
					temp++;
				else
					break;
			}
			mid = temp;
			break;
		}
		if(score[nodeList[mid]->postionX][nodeList[mid]->postionY] > score[node->postionX][node->postionY])
			min = mid+1;
		else 
			max = mid - 1;
	}
	if(score[nodeList[mid]->postionX][nodeList[mid]->postionY] > 	score[node->postionX][node->postionY])
		mid = mid + 1;
	pNode tempNode = nodeList[index];
	for (vector<pNode>::iterator itIndex=nodeList.begin()+index+1;itIndex!=nodeList.begin()+mid+1;itIndex++)
	{
		nodeList[index] = *itIndex;
		index++;
	}
	nodeList[index] = tempNode;

// 	vector<pNode>::iterator it = nodeList.begin()+index+1;
// 	for (;it!=nodeList.end();it++)
// 	{
// 		if(score[(*it)->postionX][(*it)->postionY] < score[node->postionX][node->postionY])
// 			break;
// 	}
// 	pNode tempNode = nodeList[index];
// 	for (vector<pNode>::iterator itIndex=nodeList.begin()+index+1;itIndex!=it;itIndex++)
// 	{
// 		nodeList[index] = *itIndex;
// 		index++;
// 	}
// 	nodeList[index] = tempNode;
}

void AStar_InsertSort_BinarySearch::run(HGE* hge,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length],insertFunc func,updateFunc upfunc)
{
	int gScore[width][length];
	int fScore[width][length];
	int hScore[width][length];
	for (int i=0;i<width;i++)
	{
		for (int j=0;j<length;j++)
		{
			fScore[i][j] = MAX_DISTANCE;
		}
	}
	vector<pNode> openList;
	vector<pNode> closeList;

	openList.push_back(&map[startX][startY]);
	closeList.clear();
	history.clear();

	gScore[startX][startY] = 0;
	hScore[startX][startY] = getHScore(&map[startX][startY],&map[endX][endY]);
	fScore[startX][startY] = gScore[startX][startY] + hScore[startX][startY];

	history.push_back(startX*length+startY);

	while(!openList.empty())
	{
		pNode current = removeLeastNode(openList);

		if(current->postionX == endX && current->postionY == endY)
			return; //找到路径

		func(closeList,current,fScore,0);

		list<pNode> neighbor = getNeighbor(map,current);
		for (list<pNode>::iterator itn=neighbor.begin();itn!=neighbor.end();itn++)
		{
			if(findNode_BinarySearch(*itn,closeList,fScore) != -1)
				continue;
			int tempGScore = gScore[current->postionX][current->postionY] + distance(current,*itn,heightGraph);
			if(tempGScore >= MAX_DISTANCE)
				continue;

			int result = findNode_BinarySearch(*itn,openList,fScore);
			if(result == -1)	//不在openList中
			{
				(*itn)->previous = current;
				hScore[(*itn)->postionX][(*itn)->postionY] = getHScore(*itn,&map[endX][endY]);
				gScore[(*itn)->postionX][(*itn)->postionY] = tempGScore;
				fScore[(*itn)->postionX][(*itn)->postionY] = tempGScore + hScore[(*itn)->postionX][(*itn)->postionY];
				func(openList,*itn,fScore,0);
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
				upfunc(openList,*itn,fScore,result);
			}

		}
	}

	return;
}

