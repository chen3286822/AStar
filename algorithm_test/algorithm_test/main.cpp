#include "Application.h"


// class father
// {
// public:
// 	void operator()(int x)
// 	{
// 		x;
// 	}
// };
// 
// class A : public father
// {
// public:
// 	void operator()(int x,int y)
// 	{
// 		x++;
// 	}
// };
// void func(father _func)
// {
// 	_func(1);
// }

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::sCreate();

	if(Application::sInstance().systemInit())
	{
		Application::sInstance().loadResource();
		
		//对于算法测试系统的设置
		//地图随机度设置
		Application::sInstance().readIni();
// 		Application::sInstance().setGraphMode(Application::Maze);
// 		//起终点设置
// 		Application::sInstance().setStart(0,0);
// 		Application::sInstance().setEnd(9,9);
// 		//设置测试算法
//  		Application::sInstance().setTestAlgorithm(Application::_Astar_InsertSort_BinarySearch);
//  		Application::sInstance().setTestAlgorithm(Application::_Astar_BinaryHeap);
// 		Application::sInstance().setTestAlgorithm(Application::_DFS);
// 		Application::sInstance().setTestAlgorithm(Application::_BFS);

		Application::sInstance().algorithmInit();
		Application::sInstance().run();
		Application::sInstance().freeResource();
	}
	Application::sInstance().cleanUp();

	Application::sDestroy();
	return 0;
}