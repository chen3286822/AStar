#ifndef ASTAR_INSERTSORT_BINARYSEARCH_H
#define ASTAR_INSERTSORT_BINARYSEARCH_H

#include "utily.h"


class AStar_InsertSort_BinarySearch : public Algorithm
{
public:
	AStar_InsertSort_BinarySearch()
	{
		strcpy_s(name,"AStar_InsertSort_BinarySearch");
	}
	char* getName(){return name;}
	void run(HGE*,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length],insertFunc func,updateFunc upfunc);
};

void insert_sort(vector<pNode>& nodeList,pNode node,int score[width][length],int begin=0);
void insert_sort_BinarySearch(vector<pNode>& nodeList,pNode node,int score[width][length],int begin=0);
void updateNode(vector<pNode>& nodeList,pNode node,int score[width][length],int index);
void updateNode_BinarySearch(vector<pNode>& nodeList,pNode node,int score[width][length],int index);


#endif