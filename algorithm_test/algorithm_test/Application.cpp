#include "Application.h"


bool update();
bool render();

bool Application::systemInit()
{
	hge = hgeCreate(HGE_VERSION);

	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, "Algorithm_test.log");
	hge->System_SetState(HGE_FRAMEFUNC, update);
	hge->System_SetState(HGE_RENDERFUNC,render);
	hge->System_SetState(HGE_TITLE, "Algorithm test");
	hge->System_SetState(HGE_HIDEMOUSE,false);
	hge->System_SetState(HGE_INIFILE,"config.ini");

	// Set up video mode
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(hge->System_Initiate())
		return true;
	else
	{
		char* errorMessage = hge->System_GetErrorMessage();
		WCHAR wstr[255];
		MultiByteToWideChar(CP_ACP,0,errorMessage,strlen(errorMessage),wstr,sizeof(wstr));
		MessageBox(NULL, wstr, TEXT("Error"), MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return false;
	}
}

void Application::loadResource()
{
	hFont=new hgeFont("font1.fnt");
	hFont->SetScale(0.7f);

//  	hge->Ini_SetInt("Algorithm","Num",4);
//  	hge->Ini_SetInt("Algorithm","Dijktra",1);
//  	hge->Ini_SetInt("Algorithm","Astar_InsertSort",1);
//  	hge->Ini_SetInt("Algorithm","Astar_InsertSort_BinarySearch",1);
//  	hge->Ini_SetInt("Algorithm","Astar",1);
//  	hge->Ini_SetInt("Algorithm","Astar_BinaryHeap",0);
//  	hge->Ini_SetInt("Algorithm","BFS",0);
//  	hge->Ini_SetInt("Algorithm","DFS",0);
//  	hge->Ini_SetInt("Algorithm","BFS_Priority",0);
//  
//  	hge->Ini_SetInt("Situation","map",1);//0:Non_obstacle 1:Normal_obstacle 2:Different_consumption
//  																			//3:Concave_obstacle 4:Maze
//  
//  	hge->Ini_SetInt("Start","x",0);
//  	hge->Ini_SetInt("Start","y",0);
//  	hge->Ini_SetInt("End","x",40);
//  	hge->Ini_SetInt("End","y",35);
}

void Application::readIni()
{
	int start_x,start_y;
	int end_x,end_y;
	start_x = hge->Ini_GetInt("Start","x",0);
	start_y = hge->Ini_GetInt("Start","y",0);
	end_x = hge->Ini_GetInt("End","x",0);
	end_y = hge->Ini_GetInt("End","y",0);
	setStart(start_x,start_y);
	setEnd(end_x,end_y);

	int map = hge->Ini_GetInt("Situation","map",4);
	setGraphMode(map);

	int Algo[8];
	Algo[0] = hge->Ini_GetInt("Algorithm","Dijktra",1);
	Algo[1] = hge->Ini_GetInt("Algorithm","Astar",1);
	Algo[2] = hge->Ini_GetInt("Algorithm","Astar_BinaryHeap",1);
	Algo[3] = hge->Ini_GetInt("Algorithm","Astar_InsertSort",1);
	Algo[4] = hge->Ini_GetInt("Algorithm","Astar_InsertSort_BinarySearch",0);
	Algo[5] = hge->Ini_GetInt("Algorithm","BFS",0);
	Algo[6] = hge->Ini_GetInt("Algorithm","BFS_Priority",0);
	Algo[7] = hge->Ini_GetInt("Algorithm","DFS",0);
	for (int i=0;i<8;i++)
	{
		if(Algo[i]==1)
			setTestAlgorithm(i);
	}

}

void Application::algorithmInit()
{
	for (int i=0;i<numOfTest;i++)
		algorithms[i]->init();

	timeUsed = new float[numOfTest];
}

void Application::run()
{
	hge->System_Start();
}

void Application::freeResource()
{

	gSafeDelete(hFont);

	for (int i=0;i<numOfTest;i++)
		algorithms[i]->release();

	delete[] timeUsed;
}

void Application::cleanUp()
{
	hge->System_Shutdown();
	hge->Release();
}

bool Application::appRender()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

	for (int i=0;i<numOfTest;i++)
	{
		algorithms[i]->render(100+i*400,100);
		char str[100];
		strcpy_s(str,algorithms[i]->getName());
		strcat_s(str,"\ntime Used: %.3f\nPath cost: %d");
		int cost = algorithms[i]->getCost();
		hFont->printf(100.0f+i*400,400.0f,HGETEXT_LEFT,str,timeUsed[i],algorithms[i]->getCost());
	}
	hge->Gfx_EndScene();
	return false;
}

void Application::initHeightGraph(int _graphMode)
{
	if(_graphMode==Non_obstacle)		//无障碍
	{
		for (int i=0;i<width;i++)
		{
			for (int j=0;j<length;j++)
			{
				heightGraph[i][j] = 0;
			}
		}
	}
	else if(_graphMode == Concave_obstacle)	//内凹型
	{
		for (int i=0;i<width;i++)
		{
			for (int j=0;j<length;j++)
			{
				heightGraph[i][j] = 0;
			}
		}
		for (int i=5;i<width-5;i++)
			heightGraph[16][i] = 200;
		for (int i=16;i<length-5;i++)
			heightGraph[i][5] = 200;
		for(int i=16;i<length-5;i++)
			heightGraph[i][width-5] = 200;
		for(int i=5;i<width-10;i++)
			heightGraph[length-5][i] = 200;
	}
	else if (_graphMode == Normal_obstacle)		//一般障碍物
	{
		for (int i=0;i<width;i++)
		{
			for (int j=0;j<length;j++)
			{
				heightGraph[i][j] = 0;
			}
		}
		for (int i=15;i<35;i++)
		{
			for(int j=20;j<30;j++)
				heightGraph[j][i] = 200;
		}
	}
	else if(_graphMode == Different_consumption)	//不同消耗
	{
		for (int i=0;i<width;i++)
		{
			for(int j=0;j<length/3;j++)
				heightGraph[j][i] = 0;
			for(int j=length/3;j<2*length/3;j++)
				heightGraph[j][i] = 100;
			for(int j=2*length/3;j<length;j++)
				heightGraph[j][i] = 50;
		}

	}
	else if(_graphMode == Maze)		//迷宫
	{
		int values[10][10] = {
			{0,200,200,0,0,0,0,200,0,0},
			{0,0,200,0,200,200,0,0,0,200},
			{200,0,200,0,200,200,200,0,200,200},
			{200,0,200,0,200,200,200,0,200,0},
			{200,0,0,0,0,0,200,0,0,0},
			{200,0,200,200,200,200,200,0,200,200},
			{0,0,200,0,0,0,200,0,0,0},
			{0,200,200,0,200,0,200,200,200,0},
			{0,0,0,0,200,0,0,0,200,0},
			{200,200,200,0,200,0,200,0,200,0}
		};
		for (int i=0;i<10;i++)
		{
			for (int j=0;j<10;j++)
			{
				heightGraph[i][j] = values[i][j];
			}
		}
		for (int i=0;i<11;i++)
		{
			heightGraph[i][10] = 200;
		}
		for (int i=0;i<11;i++)
		{
			heightGraph[10][i] = 200;
		}
	}
}


bool Application::appUpdate()
{
	static bool hasInit = false;
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	if(hge->Input_GetKeyState(HGEK_ENTER))
	{
		hasInit = false;
		hge->Gfx_BeginScene();
		hge->Gfx_Clear(0);
		hge->Gfx_EndScene();
	}
	
	if(!hasInit)
	{
		hasInit = true;
		initHeightGraph(graphMode);

		for (int i=0;i<numOfTest;i++)
			algorithms[i]->initMap(heightGraph,startX,startY,endX,endY);

		for (int i=0;i<numOfTest;i++)
		{
			float timeTick = (float)clock();
			switch(algorithms[i]->getType())
			{
			case _Dijkstra:
				((Dijkstra*)algorithms[i])->run(hge,100+i*400,100,startX,startY,endX,endY,heightGraph);
				break;
			case _Astar:
				((AStar*)algorithms[i])->run(hge,100+i*400,100,startX,startY,endX,endY,heightGraph);
				break;
			case _Astar_BinaryHeap:
				((AStar_BinaryHeap*)algorithms[i])->run(hge,100+i*400,100,startX,startY,endX,endY,heightGraph);
				break;
			case _Astar_InsertSort:
				((AStar_InsertSort*)algorithms[i])->run(hge,100+i*400,100,startX,startY,endX,endY,heightGraph);
				break;
			case _Astar_InsertSort_BinarySearch:
				((AStar_InsertSort_BinarySearch*)algorithms[i])->run(hge,100+i*400,100,startX,startY,endX,endY,heightGraph,insert_sort_BinarySearch,updateNode);
				break;
			case _BFS:
				((BFS*)algorithms[i])->run(hge,100+i*400,100,startX,startY,endX,endY,heightGraph);
				break;
			case _BFS_Priority:
				((BFS_Priority*)algorithms[i])->run(hge,100+i*400,100,startX,startY,endX,endY,heightGraph);
				break;
			case _DFS:
				((DFS*)algorithms[i])->run(hge,100+i*400,100,startX,startY,endX,endY,heightGraph);
				break;
			default:
				break;
			}
			timeTick = clock() - timeTick;
			timeUsed[i] = timeTick/CLOCKS_PER_SEC;
		}

		for (int i=0;i<numOfTest;i++)
			algorithms[i]->setPath(startX,startY,endX,endY,heightGraph);
	}

	for (int i=0;i<numOfTest;i++)
		algorithms[i]->renderHisAndPath();
	return false;
}

bool update()
{
	return Application::sInstance().appUpdate();
}

bool render()
{
	return Application::sInstance().appRender();
}