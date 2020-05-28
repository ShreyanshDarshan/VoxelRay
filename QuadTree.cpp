#include <iostream>
#include <conio>
#include <render.h>

struct vect2
{
	float x, y;
	vect2(int x_, int y_)
	{
		x = x_;
		y = y_;
	}
};

struct Square
{
	float x, y, w, h;
	Square(int x_, int y_, int s_,)
	{
		x = x_;
		y = y_;
		s = s_;
	}
};

struct QuadTree
{
	Square boundary;
	float numpoint;
	QuadTree* child[4];
	vect2 pos;
};

void show(Octree** octree)
{
	return 0;
}

int main()
{
	
	
	return 0;
}
