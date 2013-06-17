#ifndef UTILY_H
#define UTILY_H

#include <hge.h>
#include <hgesprite.h>
#include <hgefont.h>
#include <list>
#include <vector>
#include <queue>
#include <time.h>
#include "Singleton.h"
using namespace std;

struct Node
{
	int postionX,postionY;
	bool achiveble;
	Node* previous;

	int priority;	//仅供优先队列使用
};
typedef Node *pNode;

struct priorityNode
{
	friend bool operator<(priorityNode n1,priorityNode n2)
	{
		return n1.node->priority < n2.node->priority;
	}
	pNode node;
};
const int width=50, length=50;
const int block_size = 4;
const int MAX_DISTANCE = 100000;
const int weight = 10;


list<pNode> getNeighbor(Node map[width][length],pNode current);
int distance(pNode current,pNode neighbor,int _heightGraph[width][length]);
int getHScore(pNode current,pNode end);
bool findNode(pNode node,list<pNode> nodeList);

typedef void (*insertFunc)(vector<pNode>& nodeList,pNode node,int score[width][length],int begin);
typedef void (*updateFunc)(vector<pNode>& nodeList,pNode node,int score[width][length],int index);

#define gSafeDelete(X)		{	if((X)){delete (X); (X) = NULL;} }

class Algorithm
{
public:
	Algorithm()
	{
		strcpy_s(name,"algorithm");
	}
	void run()
	{
		//do nothing
	}
	void init();
	void initMap(int heightGraph[width][length],int startX,int startY,int endX,int endY);
	void release();
	void render(int _renderX,int _renderY);

	void setPath(int startX,int startY,int endX,int endY,int heightGraph[width][length]);
	void renderHisAndPath();

	inline void setType(int _type){type = _type;}
	inline int getType(){return type;}

	inline char* getName(){return name;}
	inline int getCost(){return cost;}
protected:
	Node map[width][length];
	hgeSprite* block[width][length];
	list<pNode> path;
	list<int> history;
	int type;
	char name[50];
	int cost;
};
#endif