#ifndef APPLICATION_H
#define APPLICATION_H

#include "utily.h"
#include "Dijkstra.h"
#include "AStar.h"
#include "AStar_BinaryHeap.h"
#include "AStar_InsertSort.h"
#include "AStar_InsertSort_BinarySearch.h"
#include "BFS.h"
#include "BFS_Priority.h"
#include "DFS.h"

class Application : public Singleton<Application>
{
public:
	Application(void)
	{
		graphMode = Non_obstacle;

		startX = 0;
		startY = 0;
		endX = width-1;
		endY = length-1;

		numOfTest = 0;
		algorithms = new Algorithm*[_Algorithm_Count];
	};
	~Application(void)
	{
		for(int i=0;i<numOfTest;i++)
			gSafeDelete(algorithms[i]);
		gSafeDelete(algorithms);
	};

	bool systemInit();
	void loadResource();
	void algorithmInit();
	void run();
	void freeResource();
	void cleanUp();
	void readIni();

	bool appUpdate();
	bool appRender();

	inline void setTestAlgorithm(int algorithm)
	{
		switch(algorithm)
		{
		case _Dijkstra:
			algorithms[numOfTest] = new Dijkstra();
			algorithms[numOfTest]->setType(_Dijkstra);
			numOfTest++;
			break;
		case _Astar:
			algorithms[numOfTest] = new AStar();
			algorithms[numOfTest]->setType(_Astar);
			numOfTest++;
			break;
		case _Astar_BinaryHeap:
			algorithms[numOfTest] = new AStar_BinaryHeap();
			algorithms[numOfTest]->setType(_Astar_BinaryHeap);
			numOfTest++;
			break;
		case _Astar_InsertSort:
			algorithms[numOfTest] = new AStar_InsertSort();
			algorithms[numOfTest]->setType(_Astar_InsertSort);
			numOfTest++;
			break;
		case _Astar_InsertSort_BinarySearch:
			algorithms[numOfTest] = new AStar_InsertSort_BinarySearch();
			algorithms[numOfTest]->setType(_Astar_InsertSort_BinarySearch);
			numOfTest++;
			break;
		case _BFS:
			algorithms[numOfTest] = new BFS();
			algorithms[numOfTest]->setType(_BFS);
			numOfTest++;
			break;
		case _BFS_Priority:
			algorithms[numOfTest] = new BFS_Priority();
			algorithms[numOfTest]->setType(_BFS_Priority);
			numOfTest++;
			break;
		case _DFS:
			algorithms[numOfTest] = new DFS();
			algorithms[numOfTest]->setType(_DFS);
			numOfTest++;
			break;
		default:
			break;
		}
	}

	inline void setGraphMode(int mode)
	{
		graphMode = mode;
	}

	inline HGE* getHGE()
	{
		return hge;
	}

	inline void setStart(int x,int y)
	{
		startX = x;
		startY = y;
	}

	inline void setEnd(int x,int y)
	{
		endX = x;
		endY = y;
	}
	enum
	{
		Non_obstacle,
		Normal_obstacle,
		Different_consumption,
		Concave_obstacle,
		Maze,
	};

	enum
	{
		_Dijkstra,
		_Astar,
		_Astar_BinaryHeap,
		_Astar_InsertSort,
		_Astar_InsertSort_BinarySearch,
		_BFS,
		_BFS_Priority,
		_DFS,


		_Algorithms,
		_Algorithm_Count = _Algorithms
	};
private:
	HGE* hge;
	hgeFont* hFont;

	int heightGraph[width][length];
	int graphMode;

	int startX,startY;
	int endX,endY;

	float* timeUsed;
	int numOfTest;
	Algorithm** algorithms;

	void initHeightGraph(int _graphMode);

};

#endif