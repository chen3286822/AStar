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
		
		//�����㷨����ϵͳ������
		//��ͼ���������
		Application::sInstance().readIni();
// 		Application::sInstance().setGraphMode(Application::Maze);
// 		//���յ�����
// 		Application::sInstance().setStart(0,0);
// 		Application::sInstance().setEnd(9,9);
// 		//���ò����㷨
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