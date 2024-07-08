#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <time.h>
#define PI 3.141592654

const int WIDTH = 400, HEIGHT = 400;
SDL_Texture *img = NULL;
int w, h; // texture width & height
float dist = 100;
float timer = 0;
float total = 0;
double cpu_time_used;
int Mspf = 0;
timeval t1, t2;
double elapsedTime;
double delta;
double Timer2 = 0;
int main( int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("SDL Practice",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_ALLOW_HIGHDPI);

    if (window == NULL)
    {
        std::cout << "Could now create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    img = IMG_LoadTexture(renderer, "src/Game/Sprites/hahmo.png");
	SDL_QueryTexture(img, NULL, NULL, &w, &h); // get the width and height of the texture
	// put the location where we want the texture to be drawn into a rectangle
	// I'm also scaling the texture 2x simply by setting the width and height
	

    SDL_Event windowEvent;

    mingw_gettimeofday(&t1, NULL);

    while (true)
    {
        
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }

        for(int i = 0; i < 1000*10000; i++){
            int a = i;
            int b = i / 2;
            int c = a * b;
        }

        timer += delta * PI * 2;

        SDL_Rect texr; texr.x = cos(timer) * dist + (WIDTH / 2); texr.y = sin(timer) * dist + (HEIGHT / 2); texr.w = w; texr.h = h; 
        SDL_RenderClear(renderer); 
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderCopy(renderer, img, NULL, &texr);
        SDL_RenderPresent(renderer);

        mingw_gettimeofday(&t2, NULL);

        //compute
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

        //convert to seconds
        delta = elapsedTime /1000;
        Timer2 += delta;
        std::cout << Timer2 << std::endl;

        t1 = t2;
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}