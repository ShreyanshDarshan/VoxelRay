#include "SDL.h"
#include<iostream>
#include<conio.h>
#include<stdlib.h>

#define size 500

struct vect2
{
	float x, y;
	vect2(float x_, float y_)
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
	Square(float x_, float y_, float w_)
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
	float numpoints;
	QuadTree* child[4];		//nw, ne, se, sw
	int level;
	bool divided;
	
	QuadTree(int level_, vect2 pos, float s_)
	{
		divided = false;
		level = level_;
		boundary.x = pos.x;
		boundary.y = pos.y;
		boundary.w = s_/2.0;
		numpoints = 0;
	}
	
	void subdivide()
	{
		if (level > 1)
		{
			vect2 centers[4];
			centers[0] = vect2(boundary.x - boundary.w/2.0, boundary.y + boundary.w/2.0);
			centers[1] = vect2(boundary.x + boundary.w/2.0, boundary.y + boundary.w/2.0);
			centers[2] = vect2(boundary.x + boundary.w/2.0, boundary.y - boundary.w/2.0);
			centers[3] = vect2(boundary.x - boundary.w/2.0, boundary.y - boundary.w/2.0);
			for (int i=0; i<4; i++)
			{
				child[i] = new QuadTree(level-1, centers[i], boundary.w);
			}
			divided = true;
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
		
		if (level > 1)
		{
			if (divided == false)
			{
				subdivide();
			}
			
			for (int i=0; i<4; i++)
			{
				child[i]->insert(point);
			}
		}
		numpoints++;
	}
};

//Screen S(size+10, size+10);

void show(QuadTree* qt, SDL_Renderer* renderer)
{
	if (qt->numpoints > 0)
	{
		int X = qt->boundary.x;
		int W = qt->boundary.w;
		int Y = qt->boundary.y;
		SDL_RenderDrawLine(renderer, X - W, Y - W, X - W, Y + W);
		SDL_RenderDrawLine(renderer, X - W, Y + W, X + W, Y + W);
		SDL_RenderDrawLine(renderer, X + W, Y + W, X + W, Y - W);
		SDL_RenderDrawLine(renderer, X + W, Y - W, X - W, Y - W);
	}
	
	if (qt->level > 1 && qt->divided)
	{
		for (int i=0; i<4; i++)
		{
			show(qt->child[i], renderer);
		}
	}
}


int main(int argc, char* argv[])
{
	QuadTree qt(12, vect2(size/2, size/2), size-10);
	
	for (int i=0; i<100; i++)
	{
		qt.insert(vect2(rand()%size, rand()%size));
	}
	
	getch();
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(size, size, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(renderer, 20, 40, 21, 41);
//                SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
//                SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
                show(&qt, renderer);
				SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}
