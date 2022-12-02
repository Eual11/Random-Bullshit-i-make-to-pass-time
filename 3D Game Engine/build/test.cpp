#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 600;
const int SCREEN_HIGHT = 480;


int main(int argc, char **argv)
{
	SDL_Window *window = NULL;
	SDL_Renderer *render =NULL;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("primitve rendering",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HIGHT,SDL_WINDOW_SHOWN);

	render = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


	bool close = false;

	SDL_Event e;

	while(!close)
	{
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				close = true;
			}
		}

		SDL_SetRenderDrawColor(render,0xFF,0xFF,0xFF,0xFF);
		SDL_RenderClear(render);

		SDL_Rect rect = {SCREEN_WIDTH/4,SCREEN_HIGHT/4,SCREEN_WIDTH/2,SCREEN_HIGHT/2};
		SDL_SetRenderDrawColor(render,0xff,0,0,0xff);
		SDL_RenderFillRect(render,&rect);

		rect = {SCREEN_WIDTH/2,SCREEN_HIGHT/6,SCREEN_WIDTH/6,SCREEN_HIGHT/6};
		SDL_SetRenderDrawColor(render,0,0xff,0,0xff);
		SDL_RenderDrawRect(render,&rect);
		for(int i =0; i <SCREEN_HIGHT; i++)
	{
		SDL_SetRenderDrawColor(render,0x00,0x00,0xff,0xff);
		SDL_RenderDrawPoint(render,SCREEN_WIDTH/2,i);
	}

		SDL_RenderPresent(render);
	}
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);

	
	SDL_Quit();

	


}