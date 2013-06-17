#include "DFS.h"

list<pNode> DFS::getNewNeighbor(Node map[width][length],pNode current,int direct)
{
	list<pNode> neighbor;
	neighbor.clear();
	if(direct&EAST)
	{
		if(current->postionY+1<=length-1)
		{
			neighbor.push_back(&map[current->postionX][current->postionY+1]);	//right
			if(current->postionX+1<=width-1)
				neighbor.push_back(&map[current->postionX+1][current->postionY+1]);	//right bottom
			if(current->postionX>=1)
				neighbor.push_back(&map[current->postionX-1][current->postionY+1]);	 //right top
		}
		if(current->postionX>=1)
			neighbor.push_back(&map[current->postionX-1][current->postionY]);	//top
		if(current->postionX+1<=width-1)
			neighbor.push_back(&map[current->postionX+1][current->postionY]);	//bottom
		if(current->postionY>=1)
		{
			neighbor.push_back(&map[current->postionX][current->postionY-1]);	//left
			if(current->postionX>=1)
				neighbor.push_back(&map[current->postionX-1][current->postionY-1]); //left top	
			if(current->postionX+1<=width-1)
				neighbor.push_back(&map[current->postionX+1][current->postionY-1]);	//left bottom
		}
	}
	else if(direct&WEST)
	{
		if(current->postionY>=1)
		{
			neighbor.push_back(&map[current->postionX][current->postionY-1]);	//left
			if(current->postionX>=1)
				neighbor.push_back(&map[current->postionX-1][current->postionY-1]); //left top	
			if(current->postionX+1<=width-1)
				neighbor.push_back(&map[current->postionX+1][current->postionY-1]);	//left bottom
		}
		if(current->postionX>=1)
			neighbor.push_back(&map[current->postionX-1][current->postionY]);	//top
		if(current->postionX+1<=width-1)
			neighbor.push_back(&map[current->postionX+1][current->postionY]);	//bottom
		if(current->postionY+1<=length-1)
		{
			neighbor.push_back(&map[current->postionX][current->postionY+1]);	//right
			if(current->postionX+1<=width-1)
				neighbor.push_back(&map[current->postionX+1][current->postionY+1]);	//right bottom
			if(current->postionX>=1)
				neighbor.push_back(&map[current->postionX-1][current->postionY+1]);	 //right top
		}
	}
	else if(direct&NORTH)
	{
		if(current->postionX>=1)
		{
			neighbor.push_back(&map[current->postionX-1][current->postionY]);	//top
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX-1][current->postionY-1]); //left top
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX-1][current->postionY+1]);	 //right top	
		}
		if(current->postionY>=1)
			neighbor.push_back(&map[current->postionX][current->postionY-1]);	//left
		if(current->postionY+1<=length-1)
			neighbor.push_back(&map[current->postionX][current->postionY+1]);	//right
		if(current->postionX+1<=width-1)
		{
			neighbor.push_back(&map[current->postionX+1][current->postionY]);	//bottom
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX+1][current->postionY-1]);	//left bottom
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX+1][current->postionY+1]);	//right bottom
		}
	}
	else if(direct&SOUTH)
	{
		if(current->postionX+1<=width-1)
		{
			neighbor.push_back(&map[current->postionX+1][current->postionY]);	//bottom
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX+1][current->postionY-1]);	//left bottom
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX+1][current->postionY+1]);	//right bottom
		}
		if(current->postionY>=1)
			neighbor.push_back(&map[current->postionX][current->postionY-1]);	//left
		if(current->postionY+1<=length-1)
			neighbor.push_back(&map[current->postionX][current->postionY+1]);	//right
		if(current->postionX>=1)
		{
			neighbor.push_back(&map[current->postionX-1][current->postionY]);	//top
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX-1][current->postionY-1]); //left top
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX-1][current->postionY+1]);	 //right top	
		}
	}
	else if(direct&EASTNORTH)
	{
		if(current->postionX>=1)
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX-1][current->postionY+1]);	 //right top	
		if(current->postionX>=1)
			neighbor.push_back(&map[current->postionX-1][current->postionY]);	//top
		if(current->postionY+1<=length-1)
			neighbor.push_back(&map[current->postionX][current->postionY+1]);	//right
		if(current->postionX>=1)
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX-1][current->postionY-1]); //left top
		if(current->postionX+1<=width-1)
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX+1][current->postionY+1]);	//right bottom
		if(current->postionY>=1)
			neighbor.push_back(&map[current->postionX][current->postionY-1]);	//left
		if(current->postionX+1<=width-1)
			neighbor.push_back(&map[current->postionX+1][current->postionY]);	//bottom	
		if(current->postionX+1<=width-1)
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX+1][current->postionY-1]);	//left bottom
	}
	else if(direct&EASTSOUTH)
	{
		if(current->postionX+1<=width-1)
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX+1][current->postionY+1]);	//right bottom
		if(current->postionX+1<=width-1)
			neighbor.push_back(&map[current->postionX+1][current->postionY]);	//bottom	
		if(current->postionY+1<=length-1)
			neighbor.push_back(&map[current->postionX][current->postionY+1]);	//right
		if(current->postionX>=1)
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX-1][current->postionY+1]);	 //right top	
		if(current->postionX+1<=width-1)
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX+1][current->postionY-1]);	//left bottom
		if(current->postionX>=1)
			neighbor.push_back(&map[current->postionX-1][current->postionY]);	//top
		if(current->postionY>=1)
			neighbor.push_back(&map[current->postionX][current->postionY-1]);	//left
		if(current->postionX>=1)
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX-1][current->postionY-1]); //left top	
	}
	else if(direct&WESTNORTH)
	{
		if(current->postionX>=1)
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX-1][current->postionY-1]); //left top	
		if(current->postionX>=1)
			neighbor.push_back(&map[current->postionX-1][current->postionY]);	//top
		if(current->postionY>=1)
			neighbor.push_back(&map[current->postionX][current->postionY-1]);	//left
		if(current->postionX>=1)
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX-1][current->postionY+1]);	 //right top	
		if(current->postionX+1<=width-1)
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX+1][current->postionY-1]);	//left bottom
		if(current->postionX+1<=width-1)
			neighbor.push_back(&map[current->postionX+1][current->postionY]);	//bottom	
		if(current->postionY+1<=length-1)
			neighbor.push_back(&map[current->postionX][current->postionY+1]);	//right
		if(current->postionX+1<=width-1)
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX+1][current->postionY+1]);	//right bottom
	}
	else if(direct&WESTSOUTH)
	{
		if(current->postionX+1<=width-1)
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX+1][current->postionY-1]);	//left bottom
		if(current->postionY>=1)
			neighbor.push_back(&map[current->postionX][current->postionY-1]);	//left
		if(current->postionX+1<=width-1)
			neighbor.push_back(&map[current->postionX+1][current->postionY]);	//bottom	
		if(current->postionX>=1)
			if(current->postionY>=1)
				neighbor.push_back(&map[current->postionX-1][current->postionY-1]); //left top	
		if(current->postionX+1<=width-1)
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX+1][current->postionY+1]);	//right bottom
		if(current->postionX>=1)
			neighbor.push_back(&map[current->postionX-1][current->postionY]);	//top
		if(current->postionY+1<=length-1)
			neighbor.push_back(&map[current->postionX][current->postionY+1]);	//right
		if(current->postionX>=1)
			if(current->postionY+1<=length-1)
				neighbor.push_back(&map[current->postionX-1][current->postionY+1]);	 //right top	
	}
// 	if(current->postionX>=1)
// 		neighbor.push_back(&map[current->postionX-1][current->postionY]);	//top
// 	if(current->postionY>=1)
// 		neighbor.push_back(&map[current->postionX][current->postionY-1]);	//left
// 	if(current->postionX+1<=width-1)
// 		neighbor.push_back(&map[current->postionX+1][current->postionY]);	//bottom	
// 	if(current->postionY+1<=length-1)
// 		neighbor.push_back(&map[current->postionX][current->postionY+1]);	//right
// 
// 	if(current->postionX>=1)
// 		if(current->postionY>=1)
// 			neighbor.push_back(&map[current->postionX-1][current->postionY-1]); //left top	
// 	if(current->postionX+1<=width-1)
// 		if(current->postionY>=1)
// 			neighbor.push_back(&map[current->postionX+1][current->postionY-1]);	//left bottom
// 	if(current->postionX+1<=width-1)
// 		if(current->postionY+1<=length-1)
// 			neighbor.push_back(&map[current->postionX+1][current->postionY+1]);	//right bottom
// 	if(current->postionX>=1)
// 		if(current->postionY+1<=length-1)
// 			neighbor.push_back(&map[current->postionX-1][current->postionY+1]);	 //right top	
	return neighbor;
}

int DFS::getDirection(pNode current,pNode target)
{
	//x = true : current �� target ���
	//y = true : current �� target ����
	//xEqual = true : current �� target ��ͬһ��ֱ����
	//yEqual = true : current �� target ��ͬһˮƽ����
	bool x = target->postionY>current->postionY?true:false;
	bool y = target->postionX<current->postionX?true:false;
	bool xEqual = target->postionY==current->postionY?true:false;
	bool yEqual = target->postionX==current->postionX?true:false;
	if(x && y)
		return EASTNORTH;
	else if(!x && y)
	{
		if(xEqual)
			return NORTH;
		else 
			return WESTNORTH;
	}
	else if(x && !y)
	{
		if(yEqual)
			return EAST;
		else 
			return EASTSOUTH;
	}
	else if(!x && !y)
	{
		if(xEqual && !yEqual)
			return SOUTH;
		else if(xEqual && yEqual)
			return EAST;		//�����Ŀ������յ��غϣ�������������������������������㷵��һ������
		else if(!xEqual && yEqual)
			return WEST;
		else 
			return WESTSOUTH;
	}
	return EAST;//����ִ�е�����
}

bool DFS::testNode(HGE* hge,pNode current,int endX,int endY,int _renderX,int _renderY)
{
	history.push_back(current->postionX*length+current->postionY);
	visited[current->postionX][current->postionY] = true;

	if(current->postionX==endX && current->postionY==endY)
		return true;

//	int drect = getDirection(current,&map[endX][endY]);
//	list<pNode> neighbor = getNewNeighbor(map,current,drect);
	list<pNode> neighbor = getNeighbor(map,current);
	for (list<pNode>::iterator it=neighbor.begin();it!=neighbor.end();it++)
	{
		if(!visited[(*it)->postionX][(*it)->postionY] && map[(*it)->postionX][(*it)->postionY].achiveble)
		{
			(*it)->previous = current;

			hge->Gfx_BeginScene();
			block[(*it)->postionX][(*it)->postionY]->Render(_renderX+(*it)->postionY*block_size,_renderY+(*it)->postionX*block_size);
			hge->Gfx_EndScene();

			if(testNode(hge,(*it),endX,endY,_renderX,_renderY))
				return true;
		}
	}
	return false;
}

void DFS::run(HGE* hge,int _renderX,int _renderY,int startX,int startY,int endX,int endY,int heightGraph[width][length])
{
	for (int i=0;i<width;i++)
	{
		for (int j=0;j<length;j++)
		{
			visited[i][j] = false;
		}
	}
	history.clear();

	if(testNode(hge,&map[startX][startY],endX,endY,_renderX,_renderY))
		return;
}