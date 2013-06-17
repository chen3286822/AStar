#include "AStar_InsertSort_BinarySearch.h"


int findNode_BinarySearch(pNode node,vector<pNode> nodeList,int score[width][length])
{
	//���ֲ��ң�nodeList��Ԫ���ǰ�fScore�Ӵ�С��˳�����е�
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
			//�ҵ�fScore��ͬ��ĳ���ڵ㣬������ǰ���������fScore����ͬ������
			//�Ƚ���������ڽڵ�����꣬���Ƿ���Ŀ����ͬ
			int temp = mid;
			//��ǰ����
			while(score[nodeList[temp]->postionX][nodeList[temp]->postionY] == score[node->postionX][node->postionY])
			{
				if(nodeList[temp]->postionX==node->postionX && nodeList[temp]->postionY==node->postionY)
					return temp;
				if(temp > 0)
					temp--;
				else
					break;
			}
			//������
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
	return -1; //û���ҵ�
}

void insert_sort(vector<pNode>& nodeList,pNode node,int score[width][length],int begin)
{
	//�۲��֪�����Ų��ҷ�Χ����¼����fScore�᲻�ϱ�С
	//����Ϊ��Ч�ʣ��´������ֵ���ȴӺ���ǰ�Ƚϲ�����
	//vectorǰ�����Ч�ʲ���
	//��һ���Ż���ʹ�ö��ֲ��ҵõ�������λ��
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
	//nodeListΪ��
	if(mid==-1)
	{
		nodeList.push_back(node);
		return;
	}
	//û����ȵĽڵ�
	if(score[nodeList[mid]->postionX][nodeList[mid]->postionY] > score[node->postionX][node->postionY])
		nodeList.insert(nodeList.begin()+mid+1,node);
	else
		nodeList.insert(nodeList.begin()+mid,node);
}

pNode removeLeastNode(vector<pNode>& nodeList)
{
	//����nodeList���մӴ�С��˳������
	//�������һ��Ԫ�ؾ��Ǿ�����СfScore�Ľڵ�
	if (nodeList.empty())
		return NULL;
	pNode leastNode = nodeList.back();
	nodeList.pop_back();
	return leastNode;
}

void updateNode(vector<pNode>& nodeList,pNode node,int score[width][length],int index)
{
	//����ǰ��insert_sort���ص�λ��index����node��nodeList�е�λ��
	//�Լ�node����fScore�϶���С
	//��ֱ���Ƴ�indexλ�õ�node��Ȼ���indexλ�������жϲ�����node
	//��һ���Ż���ʹ�ö��ֲ��ҵõ�������λ��
	//��һ���Ż�������Ҫ�Ƴ��ڵ㲢���뵽�µ�λ�ã���ʵֻҪ�ƶ����Ƴ�������
	//��һ��nodeList�м��Ԫ�أ�����Ԫ�������ǲ���λ���Ժ��Ԫ�ر��ֲ���
	//����ʹ��erase��insert���ᵼ�²���λ��֮���Ԫ��������ǰ�ƶ�������ƶ�
	//Ӱ��Ч�ʣ����ֶ�ִ���Ƴ���������һ��֮���Ԫ�ظ��Ľ�����Ч��
	/*
	*	e.p. 7, 6, 4, 1 ��6���³�3��������Ӧ�ñ�� 7, 4, 3, 1
	*	����ֻ�еڶ����͵�����Ԫ�ؽ���
	*	��erase��insert���� 7,4,1  -> 7,4,3,1 : 4,1����ǰ�ƶ���1������ƶ�
	*	�²���λ�ú���Ԫ��Խ�࣬����Ч��Խ����
	*/
	if(index < nodeList.size()-1 && 
		score[nodeList[index+1]->postionX][nodeList[index+1]->postionY] <= score[node->postionX][node->postionY])
		return;	//���µ�node��fScore��Ȼ�Ⱥ���һ��node��fScoreҪ������Ҫ����λ��
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
		return;	//���µ�node��fScore��Ȼ�Ⱥ���һ��node��fScoreҪ������Ҫ����λ��
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
			return; //�ҵ�·��

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
			if(result == -1)	//����openList��
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

