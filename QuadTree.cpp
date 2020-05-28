#include <iostream>
#include <conio.h>
#include <render.h>

using namespace std;

#define size 200

struct vect2
{
	float x, y;
	vect2(int x_, int y_)
	{
		x = x_;
		y = y_;
	}
	
	vect2()
	{
		x = 0;
		y = 0;
	}
};

struct Square
{
	float x, y, w;
	Square(int x_, int y_, int w_)
	{
		x = x_;
		y = y_;
		w = w_;
	}
	
	Square()
	{
		x = 0;
		y = 0;
		w = 0;
	}
};

struct QuadTree
{
	Square boundary;
	float numpoint;
	QuadTree* child[4];		//nw, ne, se, sw
	int level;
	
	QuadTree(int level_, vect2 pos, float s_)
	{
		level = level_;
		boundary.x = pos.x;
		boundary.y = pos.y;
		boundary.w = s_/2;
		if (level > 1)
		{
			vect2 centers[4];
			centers[0] = vect2(pos.x - boundary.w, pos.y + boundary.w);
			centers[1] = vect2(pos.x + boundary.w, pos.y + boundary.w);
			centers[2] = vect2(pos.x + boundary.w, pos.y - boundary.w);
			centers[3] = vect2(pos.x - boundary.w, pos.y - boundary.w);
			for (int i=0; i<4; i++)
			{
				child[i] = new QuadTree(level-1, centers[i], s_/2);
			}
		}
	}
	
	void insert(vect2 point)
	{
		if (!(	point.x > boundary.x - boundary.w &&
				point.x < boundary.x + boundary.w &&
				point.y > boundary.y - boundary.w &&
				point.y < boundary.y + boundary.w
			))
		{
			return;
		}	
	}
};

Screen S(size, size);

void show(QuadTree* qt)
{
	if (qt->level <= 1)
	{
		S.draw_path(qt->boundary.x - qt->boundary.w, qt->boundary.y - qt->boundary.w, qt->boundary.x - qt->boundary.w, qt->boundary.y + qt->boundary.w, 100, 100, 100);
		S.draw_path(qt->boundary.x - qt->boundary.w, qt->boundary.y + qt->boundary.w, qt->boundary.x + qt->boundary.w, qt->boundary.y + qt->boundary.w, 100, 100, 100);
		S.draw_path(qt->boundary.x + qt->boundary.w, qt->boundary.y + qt->boundary.w, qt->boundary.x + qt->boundary.w, qt->boundary.y - qt->boundary.w, 100, 100, 100);
		S.draw_path(qt->boundary.x + qt->boundary.w, qt->boundary.y - qt->boundary.w, qt->boundary.x - qt->boundary.w, qt->boundary.y - qt->boundary.w, 100, 100, 100);
	}
	else
	{
		for (int i=0; i<4; i++)
		{
			show(qt->child[i]);
		}
	}
}

int main()
{
	QuadTree qt(3, vect2(size/2, size/2), size);
	show(&qt);
	return 0;
}
